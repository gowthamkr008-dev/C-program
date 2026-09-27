#include<stdio.h>
#include<string.h>
#include "decode.h"

Status decode_byte_to_lsb(char *ch,char * imgdata)
{
  int digit,res =0;
  for(int i =0;i <8;i++){
    digit = imgdata[i] & 1;
    res = (res * 2)+digit;
    // printf("%d ",digit);
    }
    *ch = res;
    // printf("\n");
    return e_success;
  }

  /*done */