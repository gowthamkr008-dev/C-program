/*WAF to find the GCD (Greatest Common Divisor) of two numbers using a function.*/

#include<stdio.h>

int gcd(int n1,int n2){
  if(n1 < 0 || n2 <0){
    return -1;
  }
  while(n2 != 0){
    int temp =n2;
    n2= n1 %n2;
    n1 =temp;
  }
  return n1;
}

int main(){
  int num1,num2;
  scanf("%d",&num1);
  scanf("%d",&num2);
  printf("The GCD of %d and %d is %d",num1,num2,gcd(num1,num2));




  return 0;
}