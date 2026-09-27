#include<stdio.h>
#include <string.h>
#include "encode.h"
#include "types.h"


/* check the operation types */
OperationType check_operation_type(char *argv[])
{
  /* the argument variable is -e do encoding */
  if(strcmp(argv[1],"-e") == 0)
  {
    return e_encode;
  }/* the argument variable is -d do decoding  */
  else if(strcmp(argv[1],"-d")== 0)
  {
    return e_decode;
  }else
  {
    return e_unsupported;
  }

}
/* done */