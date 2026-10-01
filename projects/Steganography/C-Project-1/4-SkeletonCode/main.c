/*
Name K.R. Gowtham
Project title : LSB Image Steganography

project work with command line arguments

For Encoding
    ./a.out -e <source file> <Secret data file> <optional output file name>

For Decoding
    ./a.out -d <Secret data present image file> <optional output file>

    1 character need a 8 byte of data to  encode 

   character    binary            image data before encode             image data after encoded

     #       0 0 1 0 0 0 1 1         0 0 0 0 0 0 0 1                       0 0 0 0 0 0 0 0                   
                                     0 0 0 0 0 0 0 1                       0 0 0 0 0 0 0 0 
                                     0 0 0 0 0 0 0 1                       0 0 0 0 0 0 0 1 
                                     0 0 0 0 0 0 1 1                       0 0 0 0 0 0 1 0 
                                     0 0 0 0 0 0 1 1                       0 0 0 0 0 0 1 0 
                                     0 0 0 0 0 0 1 1                       0 0 0 0 0 0 1 0
                                     0 0 0 0 0 0 1 1                       0 0 0 0 0 0 1 1 
                                     0 0 0 0 0 1 0 1                       0 0 0 0 0 1 0 1   
                                     
                                     
 1 integer need 32 byte of data to encode                           
    Integer                         4
    Binary                         0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 
    Image data LSB before encoded  1 1 0 0 0 0 0 1 0 0 1 0 0 1 0 1 0 0 1 0 0 1 0 1 1 0 1 1 0 1 1 1 
    Image data LSB After encoded   0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
*/

#define _GNU_SOURCE 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
     
#include "encode.h"
#include "decode.h"


int main(int arg,char *argv[])
{
    uint img_size;
    EncodeInfo encInfo;
    DecodeInfo decInfo;
    if(arg <2)
    {
        printf("Error: Enter the  proper argument\n");
        printf("./a.out -e/-d  <sourcefile> <secretfile> <optional>\n");
        printf("-e => Do encoding\nsourcefile => which file you need to encode\nsecret file =>secret data present file\noptional =>require output file name\n");
        printf("-d => do Decoding\nSource file => which file you need to decode\noptional => output data file name\n");
        return -1;
    }
    
    if(check_operation_type(argv) == e_encode )
    {
        if(arg <4)
        {
            printf("Error: Enter the  proper argument\n");
            printf("./a.out -e/-d  <sourcefile> <secretfile> <optional>\n");
            printf("-e => Do encoding\nsourcefile => which file you need to encode\nsecret file =>secret data present file\noptional =>require output file name\n\n");
            printf("-d => do Decoding\nSource file => which file you need to decode\noptional => output data file name\n");
            return -1;
        }
    }else if(check_operation_type(argv) == e_decode) 
    {
        if(arg < 3)
        {
            printf("Error: Enter the  proper argument\n");
            printf("./a.out -e/-d  <sourcefile> <secretfile> <optional>\n");
            printf("-e => Do encoding\nsourcefile => which file you need to encode\nsecret file =>secret data present file\noptional =>require output file name\n");
            printf("-d => do Decoding\nSource file => which file you need to decode\noptional => output data file name\n");
            return -1;
        }
    }

    for(int i =0;i<80;i++)
	    printf("=");

    printf("\n");

    printf("%25s %s\n" ," ", "LSB Image Steganography");

    for(int i =0;i<80;i++){
	    printf("=");
   
    }
    printf("\n\n");
    
    
    /* check the operation type*/
    switch (check_operation_type(argv))
    {
        case e_encode:
        {
	            /*user given valid file */
            if(read_and_validate_encode_args(argv,&encInfo) == e_success)
            {
                
               /* file opening */
               if(open_files(&encInfo) == e_success)
               {
                for(int i =0;i<80;i++)
			printf("=");
		
		printf("\n");
		
		printf("%27s %s\n" ," ", "Start Encoding");
		
		for(int i =0;i<80;i++)
			printf("=");
	       
		printf("\n");

          
                 /* start encoding */
                if(do_encoding(&encInfo) == e_success)
                {
		 for(int i =0i;i<80;i++)
                        printf("=");

                printf("\n");

                 printf("%23s Secret Image file name %s\n"," ",encInfo.stego_image_fname);

                for(int i =0;i<80;i++)
                        printf("=");

                printf("\n");
                      
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
         for(int i =0;i<80;i++)
                        printf("=");

                printf("\n");

                printf("%27s %s\n" ," ", "Start Decoding");

                for(int i =0;i<80;i++)
                        printf("=");

                printf("\n");
       
         /*user given valid file */
        if(read_and_validate_decode_args (argv,&decInfo) == e_success )
        {
            puts("Valid file ✅");
            /* File Opening */
            if(open_file_decoding (&decInfo) == e_success)
            {
                puts("file opened\n");
                /* Start decoding */
                if(do_decoding(&decInfo) == e_success)
               {
                    puts("Decode complete✅");
		     for(int i =0;i<80;i++)
                        printf("=");

                printf("\n");

                 printf("%23s Secret Data file name %s\n"," ",decInfo.data_fname);
                 if(decInfo.data_fname != NULL){
                    free(decInfo.data_fname);
                 }

                for(int i =0;i<80;i++)
                        printf("=");

                printf("\n");
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
fcloseall();

return 0;
}

  /*done✅ */
