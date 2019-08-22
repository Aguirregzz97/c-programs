#include <stdio.h>
#include <float.h>

int main () {
  int iX;
  char cX;
  double dX;
  printf("give me an integer please\n");
  scanf("%d", &iX);

  printf("give me a character please\n");
  scanf(" %c", &cX);

  printf("give me a double please\n");
  scanf("%lf", &dX);

  printf("your integer storage size is: %zu bytes \n", sizeof(iX));

  printf("your char storage size is %zu bytes ", sizeof(cX));
  printf("and i can read it as a character: %c ", cX);
  printf("or i can read it as an int: %d\n", cX);

  printf("your double storage size is: %zu bytes, ", sizeof(dX));
  printf("i can read any number from %e ", DBL_MIN);
  printf("to %e in this data type", DBL_MAX);
}
