#include<stdio.h>
#include <string.h>
#include "encode.h"

uint get_file_size(FILE *fptr,EncodeInfo *encInfo)
{
  fseek(fptr,0,SEEK_END);
  int sec_data = ftell(fptr);
  
  rewind(fptr);
  
  // printf("size of secret file %d\n",sec_data);
  return sec_data;

}

/* done */