#include"decode.h"
#include<string.h>
#include <stdlib.h>

Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo){
  puts("File validation\n");
  if(strstr  (argv[2],".bmp") != NULL){
    decInfo->src_image_fname = argv[2];
  }else{
    return e_failure;
  }
  char *name = malloc(30);
  if(argv[3] != NULL){
    if(strstr (argv[3],".txt") != NULL ){
      // printf("file name without extension %s\n",decInfo->data_fname);
      puts("1");
       strcpy(name, argv[3]);
      }else
      {
        puts("2");
       strcpy(name, "decode.txt");
      }
    }else
    {
      puts("3");
      strcpy(name, "decode.txt");
    }
    printf("%s \n",name);
      name = strtok(name,".");

      decInfo->data_fname = name;

      

      // strcpy(decInfo->data_fname,name);
      printf("%s\n",decInfo->data_fname);
    return e_success;
  }

  /*done */