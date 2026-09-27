#include<stdio.h>
#include"decode.h"

/* open file for decoding */
Status open_file_decoding(DecodeInfo *decInfo)
{
  /*Source file*/
  decInfo->fptr_src_image = fopen(decInfo->src_image_fname,"r");

  /* Error handling if file not opened*/
  if(decInfo->fptr_src_image == NULL)
  {
    perror("Error ");
    return e_failure;
  }

  /* file opened properly */
  return e_success;
}

  /*done✅ */