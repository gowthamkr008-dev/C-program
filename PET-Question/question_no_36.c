/*write a c program to sort the each 1d array */

/*
case 1    
intput   44
        3 4 2 1
        5 4 8 6
        8 7 6 5
        1 5 7 3

Original Matrix:
          3 4 2 1
          5 4 8 6
          8 7 6 5
          1 5 7 3

Matrix after sorting each row:
           1 2 3 4
           4 5 6 8
           5 6 7 8
           1 3 5 7
*/

#include <stdio.h>

void bubbleSort(int arr[], int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        // Swap elements if they are in the wro
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

void sortEachRow(int row,int col,int mat[][col]){
  for(int i =0;i<row;i++)
      bubbleSort(mat[i],col);
}

void display(int row,int col,int mat[][col]){
  for(int i=0;i<row;i++){
    for(int j =0;j<col;j++){
      printf("%d ",mat[i][j]);
    }
     printf("\n");
  }
 
}

int main(){
  int r,c;
  scanf("%d",&r);
  scanf("%d",&c);
  int mat[r][c];
  for(int i =0;i<r;i++){
    for(int j =0;j<c;j++){
      scanf("%d",&mat[i][j]);
    }
  }
  printf("Original matrix \n");
  display(r,c,mat);
  sortEachRow(r,c,mat);
  printf("After sorting\n ");
  display(r,c,mat);
}