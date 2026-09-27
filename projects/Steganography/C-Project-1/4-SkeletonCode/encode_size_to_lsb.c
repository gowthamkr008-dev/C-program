#include <stdio.h>
#include "encode.h"


/* encode the integer */
Status encode_size_to_lsb(int data, char *image_buffer)
{
    int get,clear,i,l=0;
  
  for(i = 31;i >= 0;i--)
  {
    /*clear lsb bit */
    clear = image_buffer[l] & ~(1);
    
    /* get lsb bit */
    get = (data>>i) & 1; 

    /* set lsb */
    image_buffer[l] = clear|get;
    
    l++;
  }





  return e_success;
}

  /*done✅ */




/*
  printf("data given : %d\n",data);
  printf("Data in binary : ");

  
  for(i =31;i>=0;i--)
  {
    printf("%d ",(data>>i) &1);
  }
  
  printf("\n");
  
  printf("Readed data before encode  : ");
  for(i = 31 ;i >= 0; i-- )
  {
    printf("%d ",image_buffer[i]&1);
  }
  
  printf("\n");
  */
