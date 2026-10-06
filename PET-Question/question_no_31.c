/*Write a program to print the multiplication table of  a number*/

int main()
{
  int num;
  scanf("%d",&num);
  for(int i =1;i <= 10;i++){
    printf("%d * %d = %d\n",num,i,num * i );
  }

}