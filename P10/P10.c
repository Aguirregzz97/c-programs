// Autor: Andres Aguirre
// Matricula: A01039656
// Fecha: 13 de Sep del 2019
// Malloc
#include <stdio.h>
#include <stdlib.h>

int main() {
	char input, eof;
	char *str = (char*) malloc(2);
	int length = 0;
	int size = 2;
	while(input = getchar()){
		eof = getchar();
		str[length++] = input;
		str[length] = '\0';
		if(length == size){
			size *= 2;
			str = (char*) realloc(str, size);
		}
		printf("%s\n",str);
	}
	
	return 0;
}
