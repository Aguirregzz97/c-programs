#include <stdio.h>
#include <stdbool.h>

bool isPrime(int iX) {
  if (iX == 0 || iX == 1) {
    return false;
  }
  for (int i = 2; i <= iX / 2; i++) {
    if (iX % i == 0) {
      return false;
    }
  }
  return true;
}

int main() {
  int iX;
  printf("Dame un numero y te digo si es primo\n");
  scanf("%d", &iX);
  if (isPrime(iX))
    printf("Tu numero si es primo :)");
  else
    printf("Tu numero no es primo :(");
}
