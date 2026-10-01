#include"decode.h"
#include<string.h>
#include <stdlib.h>

/* user give valid decode file */
Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo)
{
  puts("File validation\n");
  /* check the source file */
  if(strstr(argv[2],".bmp") != NULL)
  {
    decInfo->src_image_fname = argv[2];
  }else
  {
    return e_failure;
  }
  /* check  */
  decInfo->data_fname = malloc(30);
  if(argv[3] != NULL)
  {
    if(strstr (argv[3],".txt") != NULL )
    {
      // printf("file name without extension %s\n",decInfo->data_fname);
       strcpy(decInfo->data_fname, argv[3]);
      }else
      {
        strcpy(decInfo->data_fname, "decode.txt");
      }
    }else
    {
      strcpy(decInfo->data_fname, "decode.txt");
    }
    
    decInfo->data_fname = strtok(decInfo->data_fname,".");
    

    return e_success;
  }

  /*done✅ */
