/*WAP to set, clear, and toggle the nth bit.*/


/*
case 1

29 1

After setting bit 1: 31
After clearing bit 1: 29
After toggling bit 1: 31


*/


#include<stdio.h>

int main(){
  int num,n;
  scanf("%d",&num);
  scanf("%d",&n);

  printf("%d\n",num|(1<<n));
  printf("%d\n",num&(~(1<<n)));
  printf("%d\n",num ^(1<<n));

  return 0;
}