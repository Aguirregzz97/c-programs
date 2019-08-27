#include <stdio.h>
#include <time.h>

int main() {
  int seed = time(NULL);
  int m = 1232;
  int c = 10;
  int a = 1514;
  int loop;
  int low;
  int high;
  printf("Cuantos numeros random quieres?\n");
  scanf("%d", &loop);
  printf("Dame tu rango menor\n");
  scanf("%d", &low);
  printf("Dame tu rango mayor\n");
  scanf("%d", &high);


  for (int i = 0; i < loop; i++) {
    seed = ((a * seed) + c) % m;
    printf("%d\n", (seed % (high - low)) + low);
  }
}