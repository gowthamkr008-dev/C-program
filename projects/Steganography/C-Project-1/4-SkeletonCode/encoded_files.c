#include<stdio.h>
#include <string.h>
#include "encode.h"



Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
  fseek(fptr_src_image,0,SEEK_SET);
  char data[55];
  fread(data,54,sizeof(char),fptr_src_image);
  fwrite(data,54,sizeof(char),fptr_dest_image);
  return e_success;
}



Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
  // printf("Magic string %s\n",magic_string);
  int len = strlen(magic_string);
  for(int i = 0;i<len;i++)
  {
    fread(encInfo->image_data,8,sizeof(char),encInfo->fptr_src_image);
    if(encode_byte_to_lsb(magic_string[i], encInfo->image_data) ==  e_failure)
    {
      puts("fail to encode❌\n");
      return e_failure;
    }else
    {
      fwrite(encInfo->image_data,8,sizeof(char),encInfo->fptr_stego_image);
    }
  }
  return e_success;
}


/*encode data size*/
Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{
  char image_buffer[33];
  // printf(" %ld\n",file_size);
  fread(image_buffer,32,1,encInfo->fptr_src_image);
  // printf("%s\n",image_buffer);
  if(encode_size_to_lsb(file_size,image_buffer) == e_failure )
  {    return e_failure;
  }
  
  fwrite(image_buffer,32,1,encInfo->fptr_stego_image);
  return e_success;
}




/* encode secret file extension  */
Status encode_secret_file_extn(const char *file_extn,EncodeInfo * encInfo)
{
  int size = strlen(file_extn);
  // printf("%d\n",size);
  for(int i=0;i<size;i++)
  {
    fread(encInfo->image_data,8,sizeof(char),encInfo->fptr_src_image);
    if(encode_byte_to_lsb(file_extn[i],encInfo->image_data)==e_success )
    {
      fwrite(encInfo->image_data,8,sizeof(char),encInfo->fptr_stego_image);
    }else
    {
      printf("Fail to encode❌\n");
      return e_failure;
    }
  }
  return e_success;
}




/*encode data size*/
Status encode_secret_data_size(long file_size, EncodeInfo *encInfo)
{
  char image_buffer[33];
  // printf(" %ld\n",file_size);
  fread(image_buffer,32,1,encInfo->fptr_src_image);
  // printf("%s\n",image_buffer);
  if(encode_size_to_lsb(file_size,image_buffer) == e_failure )
  {
    return e_failure;
  }
  
  fwrite(image_buffer,32,1,encInfo->fptr_stego_image);
  return e_success;
}





/* Encode secret file data*/
Status encode_secret_file_data(EncodeInfo *encInfo,char* data)
{
  // printf("%s",data);
  int size = strlen(data);
  for(int i = 0;i < size;i++)
  {
    fread(encInfo->image_data,8,sizeof(char),encInfo->fptr_src_image);
    if(encode_byte_to_lsb(data[i],encInfo->image_data) == e_success)
    {
      fwrite(encInfo->image_data,8,1,encInfo->fptr_stego_image);
    }else
    {
      return e_failure;
    }
  }
  return e_success;
}

Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
  char ch;
  
  while(fread(&ch,1,1,fptr_src))
  {
    fwrite(&ch,1,1,fptr_dest);
  }

  return e_success;
}

  /*done */