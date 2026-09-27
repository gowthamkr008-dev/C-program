#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "types.h"
#include "common.h"

Status encode_size_to_lsb(int data, char *image_buffer)
{
    int get,clear,i,l=0;
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
  for(i =31;i>=0;i--)
  {
    /*clear lsb bit */
    
    clear = image_buffer[l] & ~(1);
    
    /* get lsb bit */
    get = (data>>i) & 1; 

    /* set lsb */
    image_buffer[l] = clear|get;
    l++;
  }
  /*
  printf("\nReaded data after encoded : ");
  for(i = 31 ;i >= 0; i-- ){
    printf("%d ",image_buffer[i]&1);
  }

*/




  return e_success;
}
/* done */
