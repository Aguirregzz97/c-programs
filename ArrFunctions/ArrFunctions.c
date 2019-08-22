#include <stdio.h>

void printMat(int iMat[2][2]) {
  for (int i = 0; i < 2; i++) {
    for(int j = 0; j < 2; j++) {
      printf("%d ", iMat[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void getMatrix(int iMat[2][2]) {
  int iTmp;
  for (int i = 0; i < 2; i++) {
    for(int j = 0; j < 2; j++) {
      printf("Inserta el entero %d, %d: \n", i, j);
      scanf("%d", &iTmp);
      iMat[i][j] = iTmp;
    }
  }
  printf("\n");
}

void sumMatrix(int iMat1[2][2], int iMat2[2][2], int iMatRes[2][2]) {
  for (int i = 0; i < 2; i++) {
    for(int j = 0; j < 2; j++) {
      iMatRes[i][j] = iMat1[i][j] + iMat2[i][j];
    }
  }
}

void substractMatrix(int iMat1[2][2], int iMat2[2][2], int iMatRes[2][2]) {
  for (int i = 0; i < 2; i++) {
    for(int j = 0; j < 2; j++) {
      iMatRes[i][j] = iMat1[i][j] - iMat2[i][j];
    }
  }
}

void multMatrix(int iMat1[2][2], int iMat2[2][2], int iMatRes[2][2]) {
  iMatRes[0][0] = iMat1[0][0] * iMat2[0][0] + iMat1[0][1] * iMat2[1][0];
  iMatRes[0][1] = iMat1[0][0] * iMat2[0][1] + iMat1[0][1] * iMat2[1][1];
  iMatRes[1][0] = iMat1[1][0] * iMat2[0][0] + iMat1[1][1] * iMat2[1][0];
  iMatRes[1][1] = iMat1[1][0] * iMat2[0][1] + iMat1[1][1] * iMat2[1][1];
}
int main() {
  int iMat1[2][2];
  int iMat2[2][2];
  int iMatRes[2][2];
  getMatrix(iMat1);
  getMatrix(iMat2);
  printf("Matrix 1 is: \n");
  printMat(iMat1);
  printf("Matrix 2 is: \n");
  printMat(iMat2);
  sumMatrix(iMat1, iMat2, iMatRes);
  printf("Sum of matrices is: \n");
  printMat(iMatRes);
  substractMatrix(iMat1, iMat2, iMatRes);
  printf("Substraction of matrices is: \n");
  printMat(iMatRes);
  multMatrix(iMat1, iMat2, iMatRes);
  printf("Multiplication of matrices is: \n");
  printMat(iMatRes);
}
