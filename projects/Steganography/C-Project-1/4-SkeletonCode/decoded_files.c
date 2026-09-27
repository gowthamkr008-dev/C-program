#include<stdio.h>
#include<string.h>
#include"decode.h"

/* decode magic srting*/
Status decode_magic_string(char *str,DecodeInfo * decInfo)
{
  for(int i=0;i<2;i++)
  {
    fread(decInfo->image_data,8,sizeof(char),decInfo->fptr_src_image);
    char ch;
    if(decode_byte_to_lsb(&ch,decInfo->image_data) == e_failure)
    {
      puts("Fail to decode\n");
      return e_failure;
    }else
    {
      str[i] = ch;
    }
    // printf("%c\n",str[i]);
    }
    return e_success;
  }
  
/*decode the length of ectension*/
Status decode_size_to_ext(int *num,DecodeInfo * decInfo)
{
  char img_buff[33];
  fread(img_buff,32,sizeof(char),decInfo->fptr_src_image);
  int data;
  if(decode_size_to_lsb(&data, img_buff) == e_failure )
  {
    puts("fail to decode the size of extension\n");
    return e_failure;
  }
  *num = data;
  return e_success;
}



/* decode the file extension */
Status decode_file_extern(char * file_extern,DecodeInfo * DecInfo,int size_extern)
{
  char ext[size_extern+1];
  int i;
  for( i = 0;i<size_extern;i++)
  {
    fread(DecInfo->image_data,8,sizeof(char),DecInfo->fptr_src_image);
    if( decode_byte_to_lsb(&ext[i],DecInfo->image_data)== e_success)
    {
      printf("%c",ext[i]);
    }else{
      return e_failure;
    }
  }
  ext[i] = '\0';
  printf("\n\nextension%s\n",ext);
  strcpy(file_extern,ext);
  return e_success;
}


/* decode the secret data */
Status decode_secret_data(DecodeInfo * decInfo,int size)
{
  printf("Merged file in data decode %s %d\n",decInfo->data_fname,size);
  int i;
  char ch;
  for(i = 0;i < size;i++)
  {
    fread(decInfo->image_data,8,sizeof(char),decInfo->fptr_src_image);
    if(decode_byte_to_lsb(&ch,decInfo->image_data) == e_success)
    {
      printf("%c",ch);
      fwrite(&ch,1,sizeof(char),decInfo->fptr_data);
    }
  }
  return e_success;
}



void my_strcat(char *dest, const char *src) {
    // Move dest pointer to the end of the existing string
    while (*dest) {
        dest++;
    }

    // Copy characters from src to dest
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }

    // Add null terminator at the end
    *dest = '\0';
}

  /*done */