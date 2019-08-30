// Andres Aguirre Gonzalez A01039656
// Practica 6 Recursividad
// 30 de Agosto del 2019

#include <stdio.h>

int getFactorial(int n) {
  if (n == 1) {
    return 1;
  }
  return n * getFactorial(n - 1);
}

int getFibonacci(int n) {
  if (n == 1 || n == 0) {
    return n;
  } else {
    return (getFibonacci(n - 1) + getFibonacci(n - 2));
  }
}


int main() {
  int n;
  printf("Give a number to get factorial\n");
  scanf("%d", &n);
  printf("%d\n", getFactorial(n));
  printf("Give a number to get fibonacci sequence\n");
  int m;
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    printf("%d, ", getFibonacci(i));
  }
}
