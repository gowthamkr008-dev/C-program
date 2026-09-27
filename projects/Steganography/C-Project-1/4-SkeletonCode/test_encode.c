#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "encode.h"
#include "decode.h"
// #include "types.h"

int main( int arg,char *argv[])
{
    uint img_size;
    if(check_operation_type(argv) == e_encode ){
        if(arg <4){
            printf("Error: Enter the  proper argument\n");
            printf("./a.out -e/-d  <sourcefile> <secretfile> <optional>\n");
            printf("-e => Do encoding\nsourcefile => which file you need to encode\nsecret file =>secret data present file\noptional =>require output file name\n");
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
    switch (check_operation_type(argv) )
    {
        case e_encode: 
        {
            printf("Start Encoding\n");
            EncodeInfo encInfo;
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
        DecodeInfo decInfo;
        if(read_and_validate_decode_args (argv,&decInfo) == e_success )
        {
            puts("Valid file ✅");
            printf("%s\n",decInfo.src_image_fname);
            printf("%s\n ",decInfo.data_fname);
            if(open_file_decoding (&decInfo) == e_success)
            {
                puts("Succesfully file open");
                if(do_decoding(&decInfo) == e_success)
                {
                    puts("Decode complete✅");
                }else
                {
                    puts("Fail to decoding❌");
                }
            }else
            {
                puts("Fail opening file❌");
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
return 0;
}

  /*done */