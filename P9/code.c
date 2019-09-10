// Andres Aguirre Gonzalez A01039656
// 06/09/2019
// Practica 9

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

int binaryToInt(char *s) {
  int total = 0;
  int i = 0;
  while (s[i] != '\0') {
    if (s[i] == '1') {
      total += pow(2, i);
    }
    i++;
  }
  return total;
}

int hexToInt(char *s) {
  int size = strlen(s);
  int base = 1;
  int decVal = 0;
  for (int i = size - 1; i >= 0; i--) {
    if (s[i] >= '0' && s[i] <= '9') {
      decVal += (s[i] - 48) * base;
      base = base * 16;
    }
    else if (s[i] >= 'A' && s[i] <= 'F') {
      decVal += (s[i] - 55) * base;
      base = base * 16;
    }
    else if (s[i] >= 'a' && s[i] <= 'f') {
      decVal += (s[i] - 87) * base;
      base = base * 16;
    }
  }
  return decVal;
}

double stringToDouble(char * s) {
  int i = 0;
  int dot = 0;
  int len = strlen(s);
  double acum = 0;
  bool negative = false;
  if (s[0] == '-') {
    negative = true;
    i++;
  }
  for (i; i < len; i++) {
    if (s[i] == '.') {
      dot = i;
      i++;
    }
    acum = (acum * 10) + (s[i] - '0');
  }
  if (negative) {
    acum = acum * -1;
  }
  if (dot != 0) {
    acum = acum / pow(10, dot);
  }
  return acum;
}

// argc es numero de argumentos (arg count), argv es el arreglo de argumentos
int main(int argc, char *argv[]) {
  int i;
  for (i = 1; i < argc; i++) {
    if ((*argv[i] < '0' || *argv[i] > '9') && (*argv[i] < 'a' || *argv[i] > 'f') && (*argv[i] < 'A' || *argv[i] > 'F')) {
      printf("Numero invalido\n");
    }
    else {
      printf("%d\n", hexToInt(argv[i]));
    }
  }
  return 0;
}
