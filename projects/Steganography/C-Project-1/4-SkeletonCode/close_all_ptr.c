#include<stdio.h>
#include <stdlib.h>
#include"encode.h"
#include"decode.h"

void close_all_ptr(EncodeInfo * encInfo,DecodeInfo *decInfo){
  if(encInfo->fptr_secret != NULL){
    fclose(encInfo->fptr_secret);
  }
  if(encInfo->fptr_stego_image != NULL){
    fclose(encInfo->fptr_stego_image);
  }

  if(encInfo->fptr_src_image !=  NULL){
    fclose(encInfo->fptr_src_image);
  }

  if(decInfo->fptr_data != NULL){
    fclose(decInfo->fptr_data);
  }
  if(decInfo->fptr_src_image != NULL){
    fclose(decInfo->fptr_src_image);
  }

  if(decInfo->src_image_fname != NULL){
    free(decInfo->src_image_fname);
    decInfo->src_image_fname = NULL;
  }

  
  if(decInfo->data_fname != NULL){
    free(decInfo->data_fname);
    decInfo->data_fname  = NULL;
  }

  if(encInfo->src_image_fname != NULL){
    encInfo->src_image_fname =NULL;
  }

  if(encInfo->secret_fname != NULL){
    encInfo->secret_fname =NULL;
  }

  if(encInfo->stego_image_fname != NULL){
    encInfo->stego_image_fname = NULL;
  }
}