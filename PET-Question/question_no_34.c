/*WAP to print the frequencies of digits in a stringInput : A string containing alphanumeric characters and special symbols Output : */


/*   

Input : A string containing alphanum eric characters and special sym bols
Output :

. The program prints the count of each digit (0-9) in the input string.
. If a digit is not present in the string, its count will be displayed as 0

Example :
input: djbs5383dhh12
output: 0112010010


*/


#include <stdio.h>
#include <string.h>

void count_digit_frequencies(const char *str) {
int freq[10] = {0}; // Array to store frequencies of digits 0-9

// Traverse the string and count digit occurrences
for (int i = 0; str[i] != '\0'; i++) {
if (str[i] >= '0' && str[i] <= '9') {
  freq[str[i] - '0']++;
}
}

// Print the frequencies
for (int i = 0; i < 10; i++) {
printf("%d ", freq[i]);
}

printf("\n");
}
int main() {
char str[100];

// Input string
// printf("Enter a string: ");
scanf("%[^\n]", str);

count_digit_frequencies(str);

return 0;
}