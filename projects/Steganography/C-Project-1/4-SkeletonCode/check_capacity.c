#include<stdio.h>
#include <string.h>
#include "encode.h"
#include "common.h"

typedef unsigned int  uint;

/* check the capacity */
Status check_capacity(EncodeInfo *encInfo){
    /* bmp file image capacity */
    encInfo->image_capacity = get_image_size_for_bmp(encInfo->fptr_src_image);

    /* Length of magic string */
  int mg = strlen(MAGIC_STRING) ;

  /* extract the only extension */
  char *ext = strrchr(encInfo->secret_fname,'.');

  strcpy(encInfo->extn_secret_file,ext);

  /* extension length (.txt) */
  int size_of_ext = sizeof(int);

  /*extension length in chars */
  int ext_char = strlen(  encInfo->extn_secret_file);

  /*Length of secrete data  */
  int size_of_data =sizeof(int);

  /* secret data for characters */
  encInfo->size_secret_file   = get_file_size(encInfo->fptr_secret,encInfo);

  /* total size */
  uint total_sec_size =( mg + size_of_ext + ext_char +size_of_data +encInfo->size_secret_file ) * 8;

  printf("Total size %d\nImage size %d\n",total_sec_size,encInfo->image_capacity);

  /* check the secret data present or not*/
  if(encInfo->size_secret_file  == 0){
    printf("Not present any secret data\n");
    return e_failure;
  }

  /* the image size is more than the secret file size */
  if(encInfo->image_capacity > total_sec_size){
    puts("Enough capacity available✅ ");
  }else{
    return e_failure;
  }

  return e_success;

}