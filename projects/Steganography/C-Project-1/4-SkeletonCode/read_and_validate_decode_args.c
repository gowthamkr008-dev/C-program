#include"decode.h"
#include<string.h>
#include <stdlib.h>

Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo){
  puts("File validation\n");
  if(strstr  (argv[2],".bmp") != NULL){
     printf("valid img\n");
    decInfo->src_image_fname =argv[2];
  }else{
    return e_failure;
  }
  if(argv[3] != NULL){
    if(strstr (argv[3],".txt") != NULL ){
      char *name = strtok(argv[3],".");
     
      if(name != NULL){
        printf("valid txt\n");
         decInfo->data_fname = name;
      }else{
          decInfo->data_fname = name;
      }
      // printf("file name without extension %s\n",decInfo->data_fname);
      }else
      {
        decInfo->data_fname= "decode";
      }
    }else
    {
        decInfo->data_fname =  "decode";
    }
    return e_success;
  }

  /*done */