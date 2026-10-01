#include<stdio.h>
#include<string.h>
#include "encode.h"

/* user give proper file */
Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
  /* check the source extension is .bmp */
  if(strstr(argv[2],".bmp") != NULL)
  {
    encInfo->src_image_fname = argv[2]; 
  }else
  {
    return e_failure;
  }
  
  /* check the Secret data present extension is .txt or .pdf or .csv or .c */
  if(strstr(argv[3],".txt")  || strstr(argv[3],".csv") || strstr(argv[3],".pdf" )|| (strstr(argv[3],".c")))
  {
    encInfo->secret_fname = argv[3];
  }else
  {
    return e_failure;
  }
  
  /* user given output File */
  if(argv[4] != NULL)
  {
    if(strstr(argv[4],".bmp"))
    {
      encInfo->stego_image_fname = argv[4];
    }else
    {
      /* user give invalid file use default*/
      printf("Invalid file name use default file name\n");
      encInfo->stego_image_fname = "default.bmp";  //default file
      }
    }else
    {
      /* user not given use default output file*/
      encInfo->stego_image_fname = "default.bmp"; //default file
      }
      
      return e_success;
    
    }
     /*done✅ */
