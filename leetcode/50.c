#include<stdio.h>
double power(double x,int n){
  //x = 2
  //y = -2

 long long exp = n;
    long double base = x;
    long double result = 1.0;

    if (exp < 0) {
        base = 1.0 / base; //0.5
        exp = -exp; //  convert - to +
    }

    while (exp > 0) {
        if (exp % 2 == 1) result *= base;
        base *= base;
        exp /= 2;
    }

    return (double)result;
}
int main(){
  int n;
  double x;
  printf("enter n:");
  scanf("%d",&n);
  printf("Enter the x : " );
  scanf("%lf",&x);
  double res = power(x,n);
  printf("%g",res);


  return 0;


}