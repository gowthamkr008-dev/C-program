#define _GNU_SOURCE  
#include<stdio.h>
#include<string.h>
#include"decode.h"

/* decode magic srting*/
Status decode_magic_string(char *str,DecodeInfo * decInfo)
{
  /* decode the char by char */
  for(int i = 0;i < 2;i++)
  {
    /* read the 8 byte of data to decode the character */
    fread(decInfo->image_data,8,sizeof(char),decInfo->fptr_src_image);
    char ch;
    /* decode the char */
    if(decode_byte_to_lsb(&ch,decInfo->image_data) == e_success)
    {
       str[i] = ch;      
    }else
    {
      puts("Fail to decode\n");
      return e_failure;
    }
  }
    return e_success;
  }
  


/*decode the length of ectension*/
Status decode_size_to_ext(int *num,DecodeInfo * decInfo)
{
  char img_buff[33];
  /* read the 32 byte of data to decode the integer */
  fread(img_buff,32,sizeof(char),decInfo->fptr_src_image);
  int data;
  /* decode the integer */
  if(decode_size_to_lsb(&data, img_buff) == e_failure )
  {
    puts("fail to decode the size of extension\n");
    return e_failure;
  }
  *num = data;
  return e_success;
}

/* decode the length of Secret data */
Status decode_size_to_data(int *num,DecodeInfo * decInfo)
{
  char img_buff[33];
   /* read the 32 byte of data to decode the integer */
  fread(img_buff,32,sizeof(char),decInfo->fptr_src_image);
  int data;
  /* decode the integer */
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
  /* Decode the extension */
  for( i = 0;i < size_extern; i++)
  {
    /* read the 8 byte to decode a character */
    fread(DecInfo->image_data,8,sizeof(char),DecInfo->fptr_src_image);

    /* decode the character */
    if( decode_byte_to_lsb(&ext[i],DecInfo->image_data)==e_failure)
    {
      return e_failure;
    }
  }
  ext[i] = '\0';
  strcpy(file_extern,ext);
  return e_success;
}


/* decode the secret data */
Status decode_secret_data(DecodeInfo * decInfo,int size)
{
  int i;
  char ch;
  /* decode the secret data */
  for(i = 0;i < size; i++)
  {
    /* read the 8 byte to decode a character */
    fread(decInfo->image_data,8,sizeof(char),decInfo->fptr_src_image);
    if(decode_byte_to_lsb(&ch,decInfo->image_data) == e_success)
    {
      /* decoded character write to output file */
      fwrite(&ch,1,1,decInfo->fptr_data);
    }else{
      return e_failure;
    }
  }

  return e_success;
}


  /*done✅ */