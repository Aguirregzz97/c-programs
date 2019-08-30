// Andres Aguirre Gonzalez A01039656
// P7 address
// 30 Agosto del 2019

#include <stdio.h>

void replaceVowels(char *string) {
  for (int i = 0; i < 256; i++) {
    if (string[i] == '\0') {
      break;
    }
    switch (string[i]) {
      case 'a':
        string[i] = '4';
        break;
      case 'e':
        string[i] = '3';
        break;
      case 'i':
        string[i] = '1';
        break;
      case '0':
        string[i] = '0';
        break;
      case 'u':
        string[i] = '2';
        break;
    }
  }
}

int main() {
  char str[256];
  printf("Dame un string para hace conversion\n");
  scanf("%s", str);
  replaceVowels(str);
  printf("%s", str);
}
