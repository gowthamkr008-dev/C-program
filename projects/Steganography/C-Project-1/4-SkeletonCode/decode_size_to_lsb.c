#include<stdio.h>
#include"decode.h"


Status decode_size_to_lsb(int * data,char * img_buff)
{
  int i, digit,res =0;
  for(i = 0;i < 32; i++)
  {
    digit = img_buff[i] & 1;
    res = (res * 2) + digit;
    // printf("%d ",digit);
    }
    *data = res;
    return e_success;
  }

    /*done */