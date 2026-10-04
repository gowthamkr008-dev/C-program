#include<stdio.h>
#include <string.h>
#include <stdlib.h>
char *addstr(char *num1,char *num2){
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int maxLen = (len1 > len2 ? len1 : len2) + 1;  // +1 for possible carry

    char *result = (char *)malloc(maxLen + 1);  // +1 for '\0'
    if (!result) return NULL;

    int i = len1 - 1, j = len2 - 1, k = 0, carry = 0;

    while (i >= 0 || j >= 0 || carry) {
        int d1 = (i >= 0) ? num1[i--] - '0' : 0;
        int d2 = (j >= 0) ? num2[j--] - '0' : 0;

        int sum = d1 + d2 + carry;
        result[k++] = (sum % 10) + '0';
        carry = sum / 10;
    }

    result[k] = '\0';

    // reverse the result
    for (int left = 0, right = k - 1; left < right; left++, right--) {
        char temp = result[left];
        result[left] = result[right];
        result[right] = temp;
    }

    return result;

}
int main(){
  char num1[] ="11";
  char num2[] = "123";
  
  char *res = addstr(num1,num2);

  printf("%s\n",res);


  return 0;
}