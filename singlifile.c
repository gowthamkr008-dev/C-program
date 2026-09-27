#include<stdio.h>

#include "types.h"


  #define _GNU_SOURCE 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
     
#include "encode.h"
#include "decode.h"
// #include "types.h"

void close_all_ptr(EncodeInfo * EncodeInfo,DecodeInfo *decInfo);
int main(int arg,char *argv[])
{
    uint img_size;
      EncodeInfo encInfo;
       DecodeInfo decInfo;
       if(arg <2){
         printf("Error: Enter the  proper argument\n");
            printf("./a.out -e/-d  <sourcefile> <secretfile> <optional>\n");
            printf("-e => Do encoding\nsourcefile => which file you need to encode\nsecret file =>secret data present file\noptional =>require output file name\n");
            printf("-d => do Decoding\nSource file => which file you need to decode\noptional => output data file name\n");
            return -1;
       }


    if(check_operation_type(argv) == e_encode ){
        if(arg <4){
            printf("Error: Enter the  proper argument\n");
            printf("./a.out -e/-d  <sourcefile> <secretfile> <optional>\n");
            printf("-e => Do encoding\nsourcefile => which file you need to encode\nsecret file =>secret data present file\noptional =>require output file name\n\n");
            printf("-d => do Decoding\nSource file => which file you need to decode\noptional => output data file name\n");
            return -1;
        }
    }else if(check_operation_type(argv) == e_decode) {
        if(arg < 3){
            printf("Error: Enter the  proper argument\n");
            printf("./a.out -e/-d  <sourcefile> <secretfile> <optional>\n");
            printf("-e => Do encoding\nsourcefile => which file you need to encode\nsecret file =>secret data present file\noptional =>require output file name\n");
            printf("-d => do Decoding\nSource file => which file you need to decode\noptional => output data file name\n");
            return -1;
        }
    }
    /* check the operation type*/
    switch (check_operation_type(argv))
    {
        case e_encode: 
        {
            printf("Start Encoding\n");
          
            /*user given valid file */
            if(read_and_validate_encode_args(argv,&encInfo) == e_success)
            {
                /*
                printf("source file name %s\n",encInfo.src_image_fname);
                printf("secrate file name %s\n",encInfo.secret_fname);
                printf("output file name %s\n\n",encInfo.stego_image_fname);
                */
               /* file opening */
               if(open_files(&encInfo) == e_success)
               {
                printf("Start Encoding\n");
                /* start encoding */
                if(do_encoding(&encInfo) == e_success)
                {
                   
                    printf("output file name %s\n",encInfo.stego_image_fname);
                }else
                {
                    puts("fail to decode ❌");
                    return -1;
                }
            }else
            {
                printf("Invalid file");
                return -1;
            }
        }else
        {
            printf("Invalid file\n");
            return -1;
        }
    }
    break;
    
    case e_decode:
    {
        printf("Start Decoding\n");
       
        if(read_and_validate_decode_args (argv,&decInfo) == e_success )
        {
            puts("Valid file ✅");
            if(open_file_decoding (&decInfo) == e_success)
            {
                puts("file opened");
                if(do_decoding(&decInfo) == e_success)
                {
                    puts("Decode complete✅");
                    printf("\nfile name %s\n\n",decInfo.data_fname);
                    return 0;
                }else
                {
                    puts("Fail to decode❌");
                }
            }else
            {
                puts("Fail to opening file❌");
            }
        }else
        {
            puts("Invalid file format❌\n");
            return -1;
        }
        } 
    break;
    
    default:
    printf("Invalid argunment\n");
    return -1;
}
close_all_ptr(&encInfo,&decInfo);
return 0;
}

  /*done */


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



  #ifndef ENCODE_H
#define ENCODE_H

#include "types.h" // Contains user defined types

/* 
 * Structure to store information required for
 * encoding secret file to source Image
 * Info about output and intermediate data is
 * also stored
 */

#define MAX_SECRET_BUF_SIZE 1
#define MAX_IMAGE_BUF_SIZE (MAX_SECRET_BUF_SIZE * 8)
#define MAX_FILE_SUFFIX 4

typedef struct _EncodeInfo
{
    /* Source Image info */
    char *src_image_fname; //✅
    FILE *fptr_src_image;//✅
    uint image_capacity;/*✅*/
    uint bits_per_pixel;//✅
    char image_data[MAX_IMAGE_BUF_SIZE]; /* use during encoding */

    /* Secret File Info */
    char *secret_fname;//✅
    FILE *fptr_secret;//✅
    char extn_secret_file[MAX_FILE_SUFFIX];/*   .txt */ //✅
    char secret_data[MAX_SECRET_BUF_SIZE];  /* use during encoding */
    long size_secret_file; /* number of char in sec file  */ //✅

    /* Stego Image Info */
    char *stego_image_fname; //✅
    FILE *fptr_stego_image; //✅

} EncodeInfo;


/* Encoding function prototype */

/* Check operation type  ✅*/
OperationType check_operation_type(char *argv[]);

/* Read and validate Encode args from argv✅ */
Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo);

/* Perform the encoding */
Status do_encoding(EncodeInfo *encInfo);

/* Get File pointers for i/p and o/p files ✅*/
Status open_files(EncodeInfo *encInfo);

/* check capacity ✅ */
Status check_capacity(EncodeInfo *encInfo);

/* Get image size ✅ */
uint get_image_size_for_bmp(FILE *fptr_image);

/* Get file size ✅ */
uint get_file_size(FILE *fptr,EncodeInfo *encInfo);

/* Copy bmp image header ✅ */
Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image);

/* Store Magic String ✅*/
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo);

/* Encode secret file extenstion */
Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo);

/* Encode secret file size */
Status encode_secret_file_size(long file_size, EncodeInfo *encInfo);

/* Encode secret file data*/
Status encode_secret_file_data(EncodeInfo *encInfo,char *data);


/* Encode secret file size */
Status encode_secret_data_size(long file_size, EncodeInfo *encInfo);

/* Encode function, which does the real encoding */
Status encode_data_to_image(char *data, int size, FILE *fptr_src_image, FILE *fptr_stego_image);

/* Encode a byte into LSB of image data array */ 
/* use to encoded char ✅ */
Status encode_byte_to_lsb(char data, char *image_buffer);

/* Encode a size into LSB of image data array */
/* use to encode integer */
Status encode_size_to_lsb(int data, char *image_buffer);

/* Copy remaining image bytes from src to stego image after encoding✅ */
Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest);



#endif


  /*done */



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

/*done */


#ifndef TYPES_H
#define TYPES_H

/* User defined types */
typedef unsigned int uint;

/* Status will be used in fn. return type */
typedef enum
{
    e_success,
    e_failure
} Status;

typedef enum
{
    e_encode,
    e_decode,
    e_unsupported
} OperationType;

#endif

/* done */


#include<stdio.h>
#include<string.h>
#include "encode.h"
// #include "types.h" 

Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
  puts("File validation ");
  if(strstr(argv[2],".bmp") != NULL)
  {
    encInfo->src_image_fname = argv[2]; 
  }else
  {
    return e_failure;
  }
  
  if(strstr(argv[3],".txt")  || strstr(argv[3],".csv") || strstr(argv[3],".pdf"))
  {
    encInfo->secret_fname = argv[3];
  }else
  {
    return e_failure;
  }
  
  if(argv[4] != NULL)
  {
    if(strstr(argv[4],".bmp"))
    {
      encInfo->stego_image_fname = argv[4];
    }else
    {
      printf("Invalid file name use default file name\n");
      encInfo->stego_image_fname = "default.bmp"; //default file
      }
    }else
    {
      encInfo->stego_image_fname = "default.bmp"; //default file
      }
      
      return e_success;
    
    }
    /* done */


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
  char *name;
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

  #include <stdio.h>
#include "encode.h"
#include "types.h"



Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);
    	return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

    	return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

    	return e_failure;
    }

    // No failure return e_success
    return e_success;
}


/* done */


#include<stdio.h>
#include"decode.h"
// #include"types.h"

Status open_file_decoding(DecodeInfo *decInfo)
{
  decInfo->fptr_src_image = fopen(decInfo->src_image_fname,"r");
  if(decInfo->fptr_src_image == NULL)
  {
    perror("Error ");
    return e_failure;
  }
  return e_success;
}

/* done */

#include<stdio.h>
#include <string.h>
#include "encode.h"

uint get_file_size(FILE *fptr,EncodeInfo *encInfo)
{
  fseek(fptr,0,SEEK_END);
  int sec_data = ftell(fptr);
  
  rewind(fptr);
  
  // printf("size of secret file %d\n",sec_data);
  return sec_data;

}

/* done */


#include<stdio.h>
#include <string.h>
#include "encode.h"



Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
  fseek(fptr_src_image,0,SEEK_SET);
  char data[55];
  fread(data,54,sizeof(char),fptr_src_image);
  fwrite(data,54,sizeof(char),fptr_dest_image);
  return e_success;
}



Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
  // printf("Magic string %s\n",magic_string);
  int len = strlen(magic_string);
  for(int i = 0;i<len;i++)
  {
    fread(encInfo->image_data,8,sizeof(char),encInfo->fptr_src_image);
    if(encode_byte_to_lsb(magic_string[i], encInfo->image_data) ==  e_failure)
    {
      puts("fail to encode❌\n");
      return e_failure;
    }else
    {
      fwrite(encInfo->image_data,8,sizeof(char),encInfo->fptr_stego_image);
    }
  }
  return e_success;
}


/*encode data size*/
Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{
  char image_buffer[33];
  // printf(" %ld\n",file_size);
  fread(image_buffer,32,1,encInfo->fptr_src_image);
  // printf("%s\n",image_buffer);
  if(encode_size_to_lsb(file_size,image_buffer) == e_failure )
  {    return e_failure;
  }
  
  fwrite(image_buffer,32,1,encInfo->fptr_stego_image);
  return e_success;
}




/* encode secret file extension  */
Status encode_secret_file_extn(const char *file_extn,EncodeInfo * encInfo)
{
  int size = strlen(file_extn);
  // printf("%d\n",size);
  for(int i=0;i<size;i++)
  {
    fread(encInfo->image_data,8,sizeof(char),encInfo->fptr_src_image);
    if(encode_byte_to_lsb(file_extn[i],encInfo->image_data)==e_success )
    {
      fwrite(encInfo->image_data,8,sizeof(char),encInfo->fptr_stego_image);
    }else
    {
      printf("Fail to encode❌\n");
      return e_failure;
    }
  }
  return e_success;
}




/*encode data size*/
Status encode_secret_data_size(long file_size, EncodeInfo *encInfo)
{
  char image_buffer[33];
  // printf(" %ld\n",file_size);
  fread(image_buffer,32,1,encInfo->fptr_src_image);
  // printf("%s\n",image_buffer);
  if(encode_size_to_lsb(file_size,image_buffer) == e_failure )
  {
    return e_failure;
  }
  
  fwrite(image_buffer,32,1,encInfo->fptr_stego_image);
  return e_success;
}





/* Encode secret file data*/
Status encode_secret_file_data(EncodeInfo *encInfo,char* data)
{
  // printf("%s",data);
  int size = strlen(data);
  for(int i = 0;i < size;i++)
  {
    fread(encInfo->image_data,8,sizeof(char),encInfo->fptr_src_image);
    if(encode_byte_to_lsb(data[i],encInfo->image_data) == e_success)
    {
      fwrite(encInfo->image_data,8,1,encInfo->fptr_stego_image);
    }else
    {
      return e_failure;
    }
  }
  return e_success;
}

Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
  char ch;
  
  while(fread(&ch,1,1,fptr_src))
  {
    fwrite(&ch,1,1,fptr_dest);
  }

  return e_success;
}

  /*done */

  #include <stdio.h>
#include "encode.h"
#include "types.h"

/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    //printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    //printf("height = %u\n", height);

    // printf("\n");
    // Return image capacity
    return width * height * 3;
       
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */


 /* done */

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


#include<stdio.h>
#include<string.h>
#include "encode.h"

Status encode_byte_to_lsb(char data, char *image_buffer)
{
  int i,j,clear,get;
  /*
  puts("Binary data");
  for(i = 7;i >= 0;i--)
  {
    printf("%d ",(data>>i) &1);
  }
  printf("\n");
  
  
  for(i = 0; i < 8 ; i++)
  {
    for(j = 7;j >= 0; j--)
    {
      printf("%d ",(image_buffer[i]>>j)&1);
    }
    printf("img data %x\n",image_buffer[i]);
  }
  
  printf("\n\n");
*/
  j = 7;
  
  for(i = 0;i < 8; i++)
  {
    /* clear bit*/
    clear = image_buffer[i] & ~(1);
    // printf("%x ",clear);
    /* get bit*/
    get = (data >> j) & 1;
    j--;
    // printf("%d ",get);
    /* set bit*/
    image_buffer[i] = clear | get;
  }
 
 return e_success;
}
/*done */




 /*
  printf("Decoding\n");
  int res =0,digit;
  for(i = 0;i<8;i++){
  digit = image_buffer[i] & 1;
  res = (res * 2) + digit;
  }
  printf("char %c\n",res);
  printf("\n\n");
  */

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
  if(encode_secret_file_extn(encInfo->extn_secret_file,encInfo)==e_success)
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


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"common.h"
#include "decode.h"

/* start decoding  */
Status do_decoding(DecodeInfo *decInfo)
{
  printf("Start decoding");
  fseek(decInfo->fptr_src_image,54,SEEK_CUR);
  
  /*decode magic string*/
  char magicstring[4];
  puts("Decode magic string");
  if(decode_magic_string(magicstring,decInfo)== e_success)
  {
    if(strcmp(magicstring,MAGIC_STRING) == 0)
    {
       puts("Magic string present✅");
       puts("Secrat data present\n");
    }else
    {
      printf("No secret data data present❌\n");
      return e_failure;
    }
  }else
  {
    printf("Fail to decode\n");
    return e_failure;
  }
  
  /* decode size of extension */
  int ext_size;
  if(decode_size_to_ext (&ext_size,decInfo) == e_success)
  {
    char ext[ext_size];
    puts("Extract file extension");
    if(decode_file_extern(ext,decInfo,ext_size)==e_success )
    {
      puts("Extension Decoded✅\n");
      printf("%s\n",ext);
      char *fname;
      strcpy(fname, decInfo->data_fname);
      decInfo->data_fname = fname;

      decInfo->fptr_data = fopen(decInfo->data_fname,"w");
      if(decInfo->fptr_data == NULL)
      {
        perror("Error");
        return e_failure;
      }
    }
  }else
  {
    printf("Fail to decode❌\n");
    return e_failure;
  }
  
  
  int size_data;
  puts("Decode length of data");
  if(decode_size_to_data(&size_data,decInfo) == e_success)
  {
    printf("Decoded length of data✅\n\n");
  }else
  {
    return e_failure;
  }
  
  puts("Secret Data Decode");
  if(decode_secret_data(decInfo,size_data) == e_failure)
  {
    return e_failure;
  }
 
  return e_success;
}

  /*done */

  #define _GNU_SOURCE  
#include<stdio.h>
#include<string.h>
#include"decode.h"

/* decode magic srting*/
Status decode_magic_string(char *str,DecodeInfo * decInfo)
{
  for(int i=0;i<2;i++)
  {
    fread(decInfo->image_data,8,sizeof(char),decInfo->fptr_src_image);
    char ch;
    if(decode_byte_to_lsb(&ch,decInfo->image_data) == e_failure)
    {
      puts("Fail to decode\n");
      return e_failure;
    }else
    {
      str[i] = ch;
    }
    // printf("%c\n",str[i]);
    }
    return e_success;
  }
  
/*decode the length of ectension*/
Status decode_size_to_ext(int *num,DecodeInfo * decInfo)
{
  char img_buff[33];
  fread(img_buff,32,sizeof(char),decInfo->fptr_src_image);
  int data;
  if(decode_size_to_lsb(&data, img_buff) == e_failure )
  {
    puts("fail to decode the size of extension\n");
    return e_failure;
  }
  *num = data;
  return e_success;
}

Status decode_size_to_data(int *num,DecodeInfo * decInfo)
{
  char img_buff[33];
  fread(img_buff,32,sizeof(char),decInfo->fptr_src_image);
  int data;
  if(decode_size_to_lsb(&data, img_buff) == e_failure )
  {
    puts("fail to decode the size of extension\n");
    return e_failure;
  }
  *num = data;
  return e_success;
}


/* decode the file extension */
Status decode_file_extern(char * file_extern,DecodeInfo * DecInfo,int size_extern)
{
  char ext[size_extern+1];
  int i;
  for( i = 0;i<size_extern;i++)
  {
    fread(DecInfo->image_data,8,sizeof(char),DecInfo->fptr_src_image);
    if( decode_byte_to_lsb(&ext[i],DecInfo->image_data)==e_failure)
    {
      return e_failure;
    }
  }
  ext[i] = '\0';
  strcpy(file_extern,ext);
  return e_success;
}


/* decode the secret data */
Status decode_secret_data(DecodeInfo * decInfo,int size)
{
  int i;
  char ch;
  for(i = 0;i < size; i++)
  {
    fread(decInfo->image_data,8,sizeof(char),decInfo->fptr_src_image);
    if(decode_byte_to_lsb(&ch,decInfo->image_data) == e_success)
    {
      //printf("%c",ch);
      fwrite(&ch,1,1,decInfo->fptr_data);
    }
  }


  return e_success;
}


/* done */
#include<stdio.h>
#include"decode.h"


Status decode_size_to_lsb(int * data,char * img_buff)
{
  int i, digit,res =0;
  for(i = 0;i < 32; i++)
  {
    digit = img_buff[i] & 1;
    res = (res * 2) + digit;
    // printf("%d ",digit);
    }
    *data = res;  
    return e_success;
  }

    /*done */
    
#include<stdio.h>
#include<string.h>
#include "decode.h"

Status decode_byte_to_lsb(char *ch,char * imgdata)
{
  int digit,res =0;
  for(int i =0;i <8;i++){
    digit = imgdata[i] & 1;
    res = (res * 2)+digit;
    // printf("%d ",digit);
    }
    *ch = res;
    // printf("\n");
    return e_success;
  }

  /*done */

  #ifndef COMMON_H
#define COMMON_H

/* Magic string to identify whether stegged or not */
#define MAGIC_STRING "#*"

#endif


#include<stdio.h>
#include <string.h>
#include "encode.h"
#include "types.h"


/* check the operation types */
OperationType check_operation_type(char *argv[])
{
  if(strcmp(argv[1],"-e") == 0)
  {
    return e_encode;
  }else if(strcmp(argv[1],"-d")== 0)
  {
    return e_decode;
  }else
  {
    return e_unsupported;
  }

}
/* done */


#include<stdio.h>
#include <string.h>
#include "encode.h"
#include "common.h"

typedef unsigned int  uint;

Status check_capacity(EncodeInfo *encInfo){
  /* bmp file image capacity */
    encInfo->image_capacity = get_image_size_for_bmp(encInfo->fptr_src_image);



    /* magi string size*/
  int mg = strlen(MAGIC_STRING) ;

  char *ext = strrchr(encInfo->secret_fname,'.');

  strcpy(encInfo->extn_secret_file,ext);
  /* extension length (.txt) */
  int size_of_ext = sizeof(int);
  /*extension length in chars */
  int ext_char = strlen(  encInfo->extn_secret_file);

  /* secrete data size */
  int size_of_data =sizeof(int);

  /* secret data length */
  encInfo->size_secret_file   = get_file_size(encInfo->fptr_secret,encInfo);

  uint total_sec_size =( mg + size_of_ext + ext_char +size_of_data +encInfo->size_secret_file ) * 8;
  printf("Total size %d\nImage size %d\n",total_sec_size,encInfo->image_capacity);

  if(encInfo->size_secret_file  == 0){
    printf("Not present any secret data\n");
    return e_failure;
  }

  if(encInfo->image_capacity > total_sec_size){

  }else{
    return e_failure;
  }

  return e_success;

}