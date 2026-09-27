#include<stdio.h>
#include"decode.h"
// #include"types.h"

Status open_file_decoding(DecodeInfo *decInfo)
{
  decInfo->fptr_src_image = fopen(decInfo->src_image_fname,"r");
  if(decInfo->fptr_src_image == NULL)
  {
    perror("Error ");
    return e_failure;
  }
  return e_success;
}

/* done */