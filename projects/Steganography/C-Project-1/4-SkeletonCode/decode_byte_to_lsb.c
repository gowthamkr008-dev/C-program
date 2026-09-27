#include<stdio.h>
#include<string.h>
#include "decode.h"

/* decode the character */
Status decode_byte_to_lsb(char *ch,char * imgdata)
{
  int digit,res =0;
  for(int i = 0;i < 8;i++){

    /*get lsb bit*/
    digit = imgdata[i] & 1;
    
    /* form a character */
    res = (res * 2)+digit;
    
    }
    *ch = res;
    // printf("\n");
    return e_success;
  }

  /*done✅ */