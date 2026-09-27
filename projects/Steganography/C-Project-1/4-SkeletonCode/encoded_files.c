#include<stdio.h>
#include <string.h>
#include "encode.h"


/* copy the 54 byte of  header */
Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
  fseek(fptr_src_image,0,SEEK_SET);
  char data[55];

  fread(data,54,sizeof(char),fptr_src_image);

  fwrite(data,54,sizeof(char),fptr_dest_image);

  return e_success;
}



/* encode the magic string */
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
  /* length of magic string */
  int len = strlen(magic_string);

  /* encode char by char*/
  for(int i = 0;i < len; i++)
  {
    /* read the 8 byte of data from the source file */
    fread(encInfo->image_data,8,sizeof(char),encInfo->fptr_src_image);

    if(encode_byte_to_lsb(magic_string[i], encInfo->image_data) ==  e_failure)
    {
      puts("fail to encode❌\n");
      return e_failure;
    }else
    {
      /* character is encoded write to output file */
      fwrite(encInfo->image_data,8,sizeof(char),encInfo->fptr_stego_image);
    }
  }

  /* magic string encoded succesfully */
  return e_success;
}


/*encode data size*/
Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{
  char image_buffer[33];
  /* read the 32 byte of data to store the integer*/
  fread(image_buffer,32,1,encInfo->fptr_src_image);

  /* encode the size */
  if(encode_size_to_lsb(file_size,image_buffer) == e_failure )
  {    return e_failure;
  }
  
  /* succesfully encoded write the output file */
  fwrite(image_buffer,32,1,encInfo->fptr_stego_image);
  return e_success;
}




/* encode secret file extension  */
Status encode_secret_file_extn(const char *file_extn,EncodeInfo * encInfo)
{
  /* length of the extension */
  int size = strlen(file_extn);

  /* encode char by char */
  for(int i = 0;i < size; i++)
  {
    /* read the 8 byte to encode the single character */
    fread(encInfo->image_data,8,sizeof(char),encInfo->fptr_src_image);

    /* encode the character */
    if(encode_byte_to_lsb(file_extn[i],encInfo->image_data)==e_success )
    {
      /* suzzesfully encoded write to output file*/
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

  /* reat the 32 byte of data*/
  fread(image_buffer,32,1,encInfo->fptr_src_image);

  /* encode the length data */
  if(encode_size_to_lsb(file_size,image_buffer) == e_failure )
  {
    return e_failure;
  }
  
  /* succesfully encoded to write the output file*/
  fwrite(image_buffer,32,1,encInfo->fptr_stego_image);

  return e_success;
}





/* Encode secret data*/
Status encode_secret_file_data(EncodeInfo *encInfo,char* data)
{

  /* length of data */
  int size = strlen(data);

  /* encode char by char */
  for(int i = 0;i < size;i++)
  {
    /* read from source file to encode a character */
    fread(encInfo->image_data,8,sizeof(char),encInfo->fptr_src_image);

    /* encode the data*/
    if(encode_byte_to_lsb(data[i],encInfo->image_data) == e_success)
    {
      /* succesfully encoded write to output file*/
      fwrite(encInfo->image_data,8,1,encInfo->fptr_stego_image);
    }else
    {
      return e_failure;
    }
  }
  return e_success;
}



/* copy remaining data*/
Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
  char ch;
  
  while(fread(&ch,1,1,fptr_src))
  {
    fwrite(&ch,1,1,fptr_dest);
  }

  return e_success;
}
  /*done✅ */