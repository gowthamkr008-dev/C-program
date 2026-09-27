#include<stdio.h>

#include "types.h"

typedef unsigned int uint;
#define MAX_SECRET_BUF_SIZE 1
#define MAX_IMAGE_BUF_SIZE (MAX_SECRET_BUF_SIZE * 8)
#define MAX_FILE_SUFFIX 4


typedef struct DecodeInfo
{
    /* Source Image info */
    char *src_image_fname; //✅
    FILE *fptr_src_image;//✅
    char image_data[MAX_IMAGE_BUF_SIZE]; /* use during encoding */

    /* Secret File Info */
    // char filename[50];
    char *data_fname;//✅
    FILE *fptr_data;//✅
    char extn_secret_file[MAX_FILE_SUFFIX];/*   .txt */ //✅
}DecodeInfo;

/*  read and validate args from argv */
Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo);

/*  get file pointers for i/p and o/p files */
Status open_file_decoding(DecodeInfo * decInfo);

/* perform decoding  */
Status do_decoding(DecodeInfo *decInfo);

/* decode the magic string  */
Status decode_magic_string(char *str,DecodeInfo * DecInfo);

/* decode the file size */
Status decode_size_to_ext(int *num, DecodeInfo * decInfo);

/* decode a byte into LSB of image data array */
/* use for all decoding char*/
Status decode_byte_to_lsb(char *ch,char * imgdata);

/* use to decode integer*/
/*use for all decoding size*/
Status decode_size_to_lsb(int * data,char * img_buff);

/* decode the file extension*/
Status decode_file_extern(char * file_extern,DecodeInfo * DecodeInfo,int size_extern);

/* decode the secret data */
Status decode_secret_data(DecodeInfo * DecodeInfo,int size);


Status decode_size_to_data(int *num,DecodeInfo * decInfo);


  // void my_strcat(char *dest, const char *src);
/*


*/
  /*done */