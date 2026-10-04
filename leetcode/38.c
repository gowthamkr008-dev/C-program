#include<stdio.h>
#include<stdlib.h>
#include <string.h>
char * countandsay(int n){
//   int count =0;
//   int digit = 10;
//   char *res = (char *)malloc(3+sizeof(char));
//   int i=0;
//   while(n){
//     digit = n % 10;
//     res[i++] =digit+'0';
//     if(i > 3){
//       res = (char *) realloc(res,1);
//     }
//     n/=10;
//   }
//   int len =strlen(res);
//   printf("result %s\nlength %d\n",res,len);
//   char *str =(char *) malloc( (len *len)*sizeof(char) );
//   int l=0,j;
//   for(i = 0;i < len; i++){
//     count = 1;
//     for( j = 0;j < len;j++){
//       if(res[i] == res[j] &&i!= j){
//         printf("Equal");
//         count++;
//       }
//     }
//     str[l++] = res[i];
//     str[l++] = count +'0';
//     if(count == len){
//       break;
//     }
//     printf("%c %d\n",res[i],count);
//   }
//   return str;
// }

int main(){
  int n = 6;
  char *num= countandsay(n);

  if(num==NULL){
    printf("no number:");
  }else{
    printf("\n%s\n",num);//1211
  }

  return 0;
}