#include<stdio.h>
#include<string.h>
#include"common.h"
#include "decode.h"

/* start decoding  */
Status do_decoding(DecodeInfo *decInfo)
{
  fseek(decInfo->fptr_src_image,54,SEEK_CUR);
  // printf("file pointer %ld\n ",ftell(decInfo->fptr_src_image));
  
  /*decode magic string*/
  char magicstring[4];
  puts("Decode magic string");
  if(decode_magic_string(magicstring,decInfo)== e_success)
  {
    if(strcmp(magicstring,MAGIC_STRING) == 0)
    {
      printf("Secrat data present\n");
    }else
    {
      printf("No secret data data present\n");
      return e_failure;
    }
  }else
  {
    printf("Fail to decode\n");
    return e_failure;
  }
  
  /* decode size of extension */
  int ext_size;
  if(decode_size_to_ext (&ext_size,decInfo) == e_success)
  {
    printf("size of extension %d\n",ext_size);
    char ext[ext_size];
    printf("ectract file extension\n");
    if(decode_file_extern(ext,decInfo,ext_size)==e_success )
    {
      printf("extracted file extension %s\n",ext);
      printf("%s%s\n",decInfo->data_fname,ext);
      strcat(decInfo->data_fname,ext);
      printf("%s\n",decInfo->data_fname);
      decInfo->fptr_data = fopen(decInfo->data_fname,"w");
      if(decInfo->fptr_data == NULL)
      {
        perror("Error");
        return e_failure;
      }
    }
  }else
  {
    printf("Fail to decode\n");
    return e_failure;
  }
  
  
  int size_data;
  if(decode_size_to_ext (&size_data,decInfo) == e_success)
  {
    // printf("decoded size : %d\n",size_data);
    char data[size_data];
  }else
  {
    return e_failure;
  }
  
  if(decode_secret_data(decInfo,size_data)==e_success)
  {
    printf("Data succesfully decoded\n");
  }else
  {
    return e_failure;
  }
  printf("file name %s\n",decInfo->data_fname);
  return e_success;
}

  /*done */