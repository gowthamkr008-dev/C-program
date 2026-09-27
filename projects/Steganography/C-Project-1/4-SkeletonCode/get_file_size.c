#include<stdio.h>
#include <string.h>
#include "encode.h"

/* geth size of file to encode */
uint get_file_size(FILE *fptr,EncodeInfo *encInfo)
{
  /* get file pointer to end */
  fseek(fptr,0,SEEK_END);

  int sec_data = ftell(fptr);
  
  rewind(fptr);

  /* return the size of file*/
  return sec_data;
}

/* done */