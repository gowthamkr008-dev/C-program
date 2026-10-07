/*Given an array of random numbers, write a program to move all 0's to the end of it while maintaining the relative order of the non-zero elements.*/


#include <stdio.h>

void moveZeros(int arr[], int size);

int main() {
  int size;
  // Input the size of the array from the user
  // printf("Enter the size of the array: ");
  scanf("%d", &size);
  int arr[size];
  // Input the elements of the array from the user
  //printf("Enter the elements of the array: ");
  for (int i = 0; i < size; i++) {
    scanf("%d", &arr[i]);
  }
  
  moveZeros(arr, size);
  printf("Array after moving zeros to the end: ");
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
  return 0;
}

void moveZeros(int arr[], int size) {
  int nonZeroIndex = 0;
  // Traverse the array
  for (int i = 0; i < size; i++) {
    // If the current element is non-zero, move it to the front
    if (arr[i] != 0) {
      arr[nonZeroIndex++] = arr[i];
      // Fill the remaining elements with zeros
    }
  }
      while (nonZeroIndex < size) {
        arr[nonZeroIndex++] = 0;
      }
    }


  /*  
     #include <stdio.h>
void move_zero(int size, int *arr){
int i,j;
for(i =0;i<size;i++){
if(arr[i] == 0){
for(j =i;j<size-1; j++){
arr[j]=arr[j+1];


}
arr[j] = 0;
}
}
}
void print_arr(int size, int *arr){
for(int i =0;i<size;i++){
printf("%d ",arr[i]);
}
}
int main()
{
int size;
scanf("%d",&size);

int arr[size];
int i;
for( i = 0;i < size; i++){
scanf("%d",&arr[i]);
}
move_zero(size,arr);
    
print_arr(size,arr);
return 0; 
}
    
  */