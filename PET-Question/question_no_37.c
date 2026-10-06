/*  Create a structure-based program to:
1. Maintain account information: Name, Account number , Balance

2. Store last 5 transactions per account (amount + type: credit/debit)
3. Provide options:

o Create account

Deposit money

o Withdraw money

o Show transaction history

o Show account info

*/

#include<stdio.h>
#include<string.h>

#define MAX 5

struct transaction{
  char type[10] ;//credit or debit
  float amount;
};

struct account{
  char name[50];
  int accnumber;
  float balance;
  struct transaction history[MAX];
  int transactioncount;  
};

int main(){
  struct account acc;
  acc.transactioncount =0;
  int choice;
  float amt;
  
  printf("Create account\n");
  printf("Enter name: ");
  scanf("%[^\n]",acc.name);
  printf("Enter account number: ");
  scanf("%d",&acc.accnumber);
  acc.balance = 0.0;

  while(1){
    /* print menu */
printf("1.Deposite\n2.Withdraw\n3.Show Balance\n4.transaction history\n5.Account Info\n6.Exit\n");
printf("Enter your choice: ");
   scanf("%d",&choice);
   printf("\n");
   switch(choice){
    case 1:
       printf("Enter amount to deposite: ");
       scanf("%f",&amt);
       acc.balance+=amt;
       if(acc.transactioncount <MAX){
        strcpy(acc.history[acc.transactioncount].type,"credit");
        acc.history[acc.transactioncount].amount = amt;
        acc.transactioncount++;
       }else{
        for(int i=1;i<MAX;i++){
          acc.history[i-1].amount=amt;
        }
        strcpy(acc.history[MAX-1].type,"credit");
        acc.history[MAX-1].amount = amt;
       }
       printf("Amount deposited succesfully\n");
       break;
    
       case 2:
       printf("Enter amount to withdraw: ");
       scanf("%f",&amt);
       if(amt >acc.balance){
        puts("Insufficient balance\n");
       }else{
        acc.balance -=amt;
        if(acc.transactioncount<MAX){
          strcpy(acc.history[acc.transactioncount].type,"Debit");
          acc.history[acc.transactioncount].amount =amt;
          acc.transactioncount++;
        }else{
          for(int i=1;i<MAX;i++){
            acc.history[i-1] = acc.history[i];
          }
          strcpy(acc.history[MAX-1].type,"Debit");
          acc.history[MAX-1].amount=amt;
        }
        printf("Amount withdrawn succesfully.\n");
       }
       break;


      case 3:
       
      printf("Current Balance %.2f\n",acc.balance);
       break;
      
       case 4:
        printf("Last %d Transations\n",acc.transactioncount);
        for(int i=0;i<acc.transactioncount;i++){
          printf("%d. %s - %.2f\n",i+1,acc.history[i].type,acc.history[i].amount);
        }
        break;
        case 5:
        printf("Account Holder name %s\n",acc.name);
        printf("Account Number: %d\n",acc.accnumber);
        printf("Balance %.2f\n",acc.balance);
        break;
     
     
        case 6:
        printf("Exiting...\n");
        return 0;
      default :
      printf("Invalid choice.try again\n");

   }
   printf("\n");

  }
return 0;
}