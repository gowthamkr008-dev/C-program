#include<stdio.h>
#include<string.h>
#include "encode.h"

Status encode_byte_to_lsb(char data, char *image_buffer)
{
  int i,j,clear,get;
  /*
  puts("Binary data");
  for(i = 7;i >= 0;i--)
  {
    printf("%d ",(data>>i) &1);
  }
  printf("\n");
  
  
  for(i = 0; i < 8 ; i++)
  {
    for(j = 7;j >= 0; j--)
    {
      printf("%d ",(image_buffer[i]>>j)&1);
    }
    printf("img data %x\n",image_buffer[i]);
  }
  
  printf("\n\n");
*/
  j = 7;
  
  for(i = 0;i < 8; i++)
  {
    /* clear bit*/
    clear = image_buffer[i] & ~(1);
    // printf("%x ",clear);
    /* get bit*/
    get = (data >> j) & 1;
    j--;
    // printf("%d ",get);
    /* set bit*/
    image_buffer[i] = clear | get;
  }
 
 return e_success;
}
/*done */




 /*
  printf("Decoding\n");
  int res =0,digit;
  for(i = 0;i<8;i++){
  digit = image_buffer[i] & 1;
  res = (res * 2) + digit;
  }
  printf("char %c\n",res);
  printf("\n\n");
  */