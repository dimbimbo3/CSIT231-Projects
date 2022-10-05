#include <stdio.h> //io
#include <stdlib.h> //malloc()

//global variables
int rowsM1, colsM1, rowsM2, colsM2;

//function declarations
void setRowColCount();
void setMatrixValues();
void displayMatrix();
void matrixMultiply();
void freeMatrix();

int main() {
  //loops until multiplication between the matrices is possible
  do{
    setRowColCount(&rowsM1, &colsM1, 1);
    setRowColCount(&rowsM2, &colsM2, 2);
    if(colsM1 != rowsM2){
      printf("MULTIPLICATION IS NOT POSSIBLE: Try again...\n");
    }
  }while(colsM1 != rowsM2);

  //Allocates memory for pointer to array of pointers - representing matrix #1
  int **matrix1;
  matrix1=(int**)malloc(rowsM1 * sizeof(int*));
  for(int i=0; i < rowsM1; i++){
    matrix1[i]=(int*)malloc(colsM1 * sizeof(int));
  }

  //Sets the values of matrix #1
  setMatrixValues(matrix1, 1, rowsM1, colsM1);
  displayMatrix(matrix1, 1, rowsM1, colsM1);

  //Allocates memory for pointer to array of pointers - representing matrix #2
  int **matrix2;
  matrix2=(int**)malloc(rowsM2 * sizeof(int*));
  for(int i=0; i < rowsM2; i++){
    matrix2[i]=(int*)malloc(colsM2 * sizeof(int));
  }

  //Sets the values of matrix #2
  setMatrixValues(matrix2, 2, rowsM2, colsM2);
  displayMatrix(matrix2, 2, rowsM2, colsM2);

  //Allocates memory for pointer to array of pointers - representing matrix #3
  int **matrix3;
  matrix3=(int**)malloc(rowsM1 * sizeof(int*));
  for(int i=0; i < rowsM1; i++){
    matrix3[i]=(int*)malloc(colsM2 * sizeof(int));
  }

  //Multiplies matrix 1 & matrix 2
  matrixMultiply(matrix1, matrix2, matrix3, rowsM1, colsM2, rowsM2);
  displayMatrix(matrix3, 3, rowsM1, colsM2);

  //Frees memory used by matrices
  freeMatrix(matrix1, rowsM1);
  freeMatrix(matrix2, rowsM2);
  freeMatrix(matrix3, rowsM1);
  
  return 0;
}

//Sets the number of rows & columns for a matrix
void setRowColCount(int *rows, int *cols, int matrixNum){
  int userInput;

  //Retrieves row count from user
  printf("Please enter the number of rows for Matrix #%d: ", matrixNum);
  scanf("%d",&userInput);
  *rows = userInput;

  //Retrieves column count from user
  printf("Please enter the number of columns for Matrix #%d: ", matrixNum);
  scanf("%d",&userInput);
  *cols = userInput;

  printf("Matrix #%d - Rows: %d, Cols: %d\n", matrixNum, *rows, *cols);
  printf("----------\n"); //formatting for underneath the displayed rows and columns
}

//Sets the values in the given matrix
void setMatrixValues(int **matrix, int matrixNum, int rows, int cols){
  int userInput;

  //loops through the rows of the matrix
  for(int i = 0; i < rows; i++){
    //loops through the columns of the matrix, while setting the value of each entry via user input
    for(int j = 0; j < cols; j++){
      printf("Matrix #%d - Enter [%d][%d]: ", matrixNum, i, j);
      scanf("%d",&userInput);
      matrix[i][j] = userInput;
    }
  }

  printf("----------\n"); //formatting for above the displayed matrix
}

//Displays the values of a given matrix to the console
void displayMatrix(int **matrix, int matrixNum, int rows, int cols){
  printf("Matrix #%d:\n", matrixNum);
  //loops through the rows of the matrix
  for(int i = 0; i < rows; i++){
    //loops through the columns of the matrix, while displaying the value of each entry
    for(int j = 0; j < cols; j++){
      printf("%d ", matrix[i][j]);
    }
    printf("\n"); //formatting for the end of a row
  }
  printf("----------\n"); //formatting for underneath the displayed matrix
}

//Multiplies matrix 1 & 2 and stores the result in matrix 3
void matrixMultiply(int **matrix1, int **matrix2, int **matrix3, int rowsM1, int colsM2, int rowsM2){
  int temp = 0;

  //loops through the rows of matrix 1
  for(int i = 0; i < rowsM1; i++){
    //loops through the columns of matrix 2
    for(int j = 0; j < colsM2; j++){
      //loops through the rows of the column of matrix 2, while calculating the sum of the products for the resulting entry
      for(int k = 0; k < rowsM2; k++){
        temp += matrix1[i][k] * matrix2[k][j];
      }
      matrix3[i][j] = temp;
      temp = 0;
    }
  }
}

//Frees the memory used by the given matrix
void freeMatrix(int **matrix, int rows){
  //Frees individual row pointers
  for(int i=0; i < rows; i++){
    free(matrix[i]);
  }
  //Frees top-level pointer
  free(matrix);
}