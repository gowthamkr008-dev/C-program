#include<stdio.h>
#include"decode.h"

/* decode the integer */
Status decode_size_to_lsb(int * data,char * img_buff)
{
  int i, digit,res =0;
  for(i = 0;i < 32; i++)
  {
    /* get data*/
    digit = img_buff[i] & 1;

    /*form a integer */
    res = (res * 2) + digit;
    }
    *data = res;  
    return e_success;
  }

    /*done✅ */
    