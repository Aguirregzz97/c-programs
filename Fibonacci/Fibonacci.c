#include <stdio.h>

void printFibonacci(int iIterations) {
  if (iIterations == 0) {
    return;
  }
  if (iIterations == 1) {
    printf("0");
    return;
  }
  if (iIterations == 2) {
    printf("0, 1");
    return;
  }
  int i2 = 0;
  int i1 = 1;
  int iCurrent = 1;
  printf("%d, ", i2);
  printf("%d, ", i1);
  for (int i = 2; i < iIterations; i++) {
    iCurrent = i2 + i1;
    i2 = i1;
    i1 = iCurrent;
    printf("%d, ", iCurrent);
  }
}

int main() {
  int iIteraciones;
  printf("Cuantas iteraciones de fibonacci quieres? \n");
  scanf("%d", &iIteraciones);
  printFibonacci(iIteraciones);
}
