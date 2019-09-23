#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  FILE *fptr;
  fptr = fopen(argv[1], "r");
  char ch;

  while (ch != EOF) {
    printf ("%c", ch);
    ch = fgetc(fptr);
  }
}
