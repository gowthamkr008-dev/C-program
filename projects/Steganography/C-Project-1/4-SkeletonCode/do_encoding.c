#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "common.h"


/* astart encoding */
Status do_encoding(EncodeInfo *encInfo)
{
  /*check enough space there in image file or not */
  puts("Capacity checking\n");
  if(check_capacity(encInfo) == e_success)
  {
    puts("Enough capacity available✅\n");
  }else
  {
    puts("Capacity not available❌\n");
    return e_failure;
  }

  /* copy the header not change any header */
  puts("Copy the header");
  if(copy_bmp_header(encInfo->fptr_src_image,encInfo->fptr_stego_image)  == e_success)
  {
    puts("Header copied✅\n");
  }else
  {
    puts("Copied failed❌");
    return e_failure;
  }


  /*encode magic string */
  puts("Encode the magic string");
  char magic_string[5];
  strcpy(magic_string,MAGIC_STRING);
  if(encode_magic_string(magic_string, encInfo) == e_success)
  {
    puts("Magic sting encoded✅\n");
  }else
  {
    puts("Failed encoded magic string❌");
    return e_failure;
  }
  
  /* encode the length of extension */
  puts("Encode the length of extension");
  int data = strlen(encInfo->extn_secret_file);
  if(encode_secret_file_size(data, encInfo)== e_success)
  {
    puts ("extension length encoded✅\n") ;
  }else
  {
    return e_failure;
  }
  
  /* encode the extension  */
  puts("Encode the file extension");
  if(encode_secret_file_extn (encInfo->extn_secret_file,encInfo)==e_success)
  {
    puts("extension encoded✅\n");
  }else
  {
    return e_failure;
  }


  /*encode the length of secret data*/
  puts("Encode the length of secret data");
  if(encode_secret_data_size(encInfo->size_secret_file, encInfo)== e_success)
  {
    puts ("data size encoded✅\n") ;
  }else
  {
    return e_failure;
  }


  /*encode the secret data*/
  puts("Encode secret data");
  char secdata[encInfo->size_secret_file+1];
  fread(secdata,encInfo->size_secret_file,sizeof(char),encInfo->fptr_secret);
  secdata[encInfo->size_secret_file] = '\0';
  if(encode_secret_file_data(encInfo,secdata) ==e_success)
  {
    puts("Secred Data encoded✅\n");
  }else{
    return e_failure;
  }
  
  /* Copy the remaining datas */
  puts("Encode the remaining data");
  if(copy_remaining_img_data(encInfo->fptr_src_image,encInfo->fptr_stego_image) == e_success )
  {
   puts("Reamining data copied✅\n");
  }else
  {
    printf("Error in remaining data copy❌\n");
    return e_failure;
  }
  // printf("extension %s\n",encInfo->extn_secret_file);
  puts("Encoded completed✅\n");
  return e_success;
}

  /*done */


  /*
  printf("\n\n%s\n",encInfo->src_image_fname);
  printf("%s\n",encInfo->secret_fname);
  printf("%s\n",encInfo->extn_secret_file);
  printf("image size %d\n",encInfo->image_capacity);
  printf("data size %ld\n\n",encInfo->size_secret_file);

*/
