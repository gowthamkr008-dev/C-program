
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"common.h"
#include "decode.h"

/* start decoding  */
Status do_decoding(DecodeInfo *decInfo)
{
  /* move the file pointer to 54th bit*/
  printf("Start decoding");
  fseek(decInfo->fptr_src_image,54,SEEK_CUR);
  
  /*decode magic string*/
  char magicstring[4];
  puts("Decode magic string");
  if(decode_magic_string(magicstring,decInfo)== e_success)
  {
    if(strcmp(magicstring,MAGIC_STRING) == 0)
    {
       puts("Magic string present✅");
       puts("Secrat data present\n");
    }else
    {
      printf("No secret data data present\n");
      return e_failure;
    }
  }else
  {
    printf("Fail to decode❌\n");
    return e_failure;
  }
  
  /* decode size of extension */
  int ext_size;
  if(decode_size_to_ext (&ext_size,decInfo) == e_success)
  {
    char ext[ext_size];
    puts("Extract file extension");
    if(decode_file_extern(ext,decInfo,ext_size)==e_success )
    {
      puts("Extension Decoded✅\n");
      strcat(decInfo->data_fname,ext);
      decInfo->fptr_data = fopen(decInfo->data_fname,"w");
      if(decInfo->fptr_data == NULL)
      {
        perror("Error");
        return e_failure;
      }
    }
  }else
  {
    printf("Fail to decode❌\n");
    return e_failure;
  }
  
  
  /* decode the length of data*/
  int size_data;
  puts("Decode length of data");
  if(decode_size_to_data(&size_data,decInfo) == e_success)
  {
    printf("Decoded length of data✅\n\n");
  }else
  {
    return e_failure;
  }
  
    /* decode the secret data */
  puts("Secret Data Decode");
  if(decode_secret_data(decInfo,size_data) == e_failure)
  {
    return e_failure;
  }

  return e_success;
}

  /*done✅ */