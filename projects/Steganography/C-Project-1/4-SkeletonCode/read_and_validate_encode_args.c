#include<stdio.h>
#include<string.h>
#include "encode.h"
// #include "types.h" 

Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
  puts("File validation ");
  if(strstr(argv[2],".bmp") != NULL)
  {
    encInfo->src_image_fname = argv[2]; 
  }else
  {
    return e_failure;
  }
  
  if(strstr(argv[3],".txt")  || strstr(argv[3],".csv") || strstr(argv[3],".pdf"))
  {
    encInfo->secret_fname = argv[3];
  }else
  {
    return e_failure;
  }
  
  if(argv[4] != NULL)
  {
    if(strstr(argv[4],".bmp"))
    {
      encInfo->stego_image_fname = argv[4];
    }else
    {
      printf("Invalid file name use default file name\n");
      encInfo->stego_image_fname = "default.bmp"; //default file
      }
    }else
    {
      encInfo->stego_image_fname = "default.bmp"; //default file
      }
      
      return e_success;
    
    }
    /* done */