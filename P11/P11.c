// Andres Aguirre Gonzalez 
// A01039656
// 13 de Sep del 2019
// conversion de bases

#include <stdlib.h>
#include <stdio.h>

//Funcion para convertir de hexadecimal a int
//Recibe string con numero hexadecimal
int hexToInt(char *s) {
	int result = 0;
	while (*s != '\0') {
		if (*s >= '0' && *s <= '9') {
			result = (result << 4) + (*s - '0');
		}
		else if (*s >= 'a' && *s <= 'f') {
			result = (result << 4) + 10 + (*s - 'a');
		}
		else if (*s >= 'A' && *s <= 'F') {
			result = (result << 4) + 10 + (*s - 'A');
		}
		else {
			printf("Caracter Invalido\n");
			return result;
		}
		s++;
	}
	return result;
}

//Funcion para convertir de binario a int
//Recibe string con numero binario
int binToInt(char *s) {
	int result = 0;
	while (*s != '\0') {
		if (*s == '1') {
			result <<= 1;
			result |= 1;
		}
		else if (*s == '0') {
			result <<= 1;
		}
		else {
			printf("Caracter Invalido\n");
			return result;
		}
		s++;
	}
	return result;
}

//Funcion para convertir de octal a int
//Recibe string con numero octaal
int octToInt(char *s) {
	int result = 0;
	while (*s != '\0') {
		if (*s >= '0' && *s <= '7') {
			result = result * 8 + (*s - '0');
		}
		else{
			printf("Caracter Invalido\n");
			return result;
		}
		s++;
	}
	return result;
}

//Funcion para dividir entre dos
//Recibe un entero
int divideByTwo(int *i) {
	return (*i)>>1;
}

//Funcion para multiplicar por dos
//Recibe un entero
int multByTwo(int *i) {
	return (*i)<<1;
}

int main(int argc, char* argv[]) {	
	int i;
	if (argc < 3) {
		printf("Argumentos insuficientes\n");
		return 0;
	}
	//numero de hexadecimales a convertir
	int hexaNumber = atoi(argv[1]);
	printf("Hexadecimales\n");
	for (i = 2; i < hexaNumber + 2 && i < argc; i++) {
		printf("%s hexa = %d\n", argv[i], hexToInt(argv[i]));
	}
	
	if (i >= argc) {
		return 0;
	}
	
	int binaryNumber = atoi(argv[i]);
	printf("Binarios\n");
	for (i = i + 1; i < binaryNumber + hexaNumber + 3 && i < argc; i++) {
		printf("%s binario = %d\n", argv[i], binToInt(argv[i]));
	}
	
	if (i >= argc) {
		return 0;
	}
	
	int octalNumber = atoi(argv[i]);
	printf("Octales\n");
	for (i = i + 1; i < octalNumber + binaryNumber + hexaNumber + 4 && i < argc; i++) {
		printf("%s octal = %d\n", argv[i], octToInt(argv[i]));
	}
	return 0;
}
