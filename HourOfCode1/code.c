#include <stdio.h>
#include <time.h>

int main() {
  int iSeed = time(NULL);
  int iM = 1232;
  int iC = 10;
  int iA = 1514;
  int iLoop;
  int iLow;
  int iHigh;
  printf("Cuantos numeros random quieres?\n");
  scanf("%d", &iLoop);
  printf("Dame tu rango menor\n");
  scanf("%d", &iLow);
  printf("Dame tu rango mayor\n");
  scanf("%d", &iHigh);


  for (int i = 0; i < iLoop; i++) {
    iSeed = ((iA * iSeed) + iC) % iM;
    printf("%d\n", (iSeed % (iHigh - iLow)) + iLow);
  }
}