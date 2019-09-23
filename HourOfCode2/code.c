//
// Andres Aguirre Gonzalez
// A01039656
// 20 de Septiembre 2019
// HOC2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ctype.h>

char *numbers[100];
char storage[20];

int words;

//splits into separate words
//Receives the input
//changes numbers[]
void split(char *digits) {
	words = 0;
	while (*digits != '\0') {
		numbers[words++] = digits;
		while (*digits != '\0' && *digits != ' ') {
			digits++;
		}
		if (*digits == '\0') {
			break;
		}
		*digits = '\0';
		digits++;
	}
}

//convert a word into number
//Return int
//Receive the word
int wordToNumber(char *word) {
	if (strcmp(word, "cero,") == 0 || strcmp(word, "cero") == 0) {
		return 0;
	}
	if (strcmp(word, "uno,") == 0 || strcmp(word, "uno") == 0) {
		return 1;
	}
	if (strcmp(word, "dos,") == 0 || strcmp(word, "dos") == 0) {
		return 2;
	}
	if (strcmp(word, "tres,") == 0 || strcmp(word, "tres") == 0) {
		return 3;
	}
	if (strcmp(word, "cuatro,") == 0 || strcmp(word, "cuatro") == 0) {
		return 4;
	}
	if (strcmp(word, "cinco,") == 0 || strcmp(word, "cinco") == 0) {
		return 5;
	}
	if (strcmp(word, "seis,") == 0 || strcmp(word, "seis") == 0) {
		return 6;
	}
	if (strcmp(word, "siete,") == 0 || strcmp(word, "siete") == 0) {
		return 7;
	}
	if (strcmp(word, "ocho,") == 0 || strcmp(word, "ocho") == 0) {
		return 8;
	}
	if (strcmp(word, "nueve,") == 0 || strcmp(word, "nueve") == 0) {
		return 9;
	}
	if (strcmp(word, "diez,") == 0 || strcmp(word, "diez") == 0) {
		return 10;
	}
	if (strcmp(word, "once,") == 0 || strcmp(word, "once") == 0) {
		return 11;
	}
	if (strcmp(word, "doce,") == 0 || strcmp(word, "doce") == 0) {
		return 12;
	}
	if (strcmp(word, "trece,") == 0 || strcmp(word, "trece") == 0) {
		return 13;
	}
	if (strcmp(word, "catorce,") == 0 || strcmp(word, "catorce") == 0) {
		return 14;
	}
	if (strcmp(word, "quince,") == 0 || strcmp(word, "quince") == 0) {
		return 15;
	}
	if (strcmp(word, "veinte,") == 0 || strcmp(word, "veinte") == 0) {
		return 20;
	}
	if (strcmp(word, "treinta,") == 0 || strcmp(word, "treinta") == 0) {
		return 30;
	}
	if (strcmp(word, "cuarenta,") == 0 || strcmp(word, "cuarenta") == 0) {
		return 40;
	}
	if (strcmp(word, "cincuenta,") == 0 || strcmp(word, "cincuenta") == 0) {
		return 50;
	}
	if (strcmp(word, "sesenta,") == 0 || strcmp(word, "sesenta") == 0) {
		return 60;
	}
	if (strcmp(word, "setenta,") == 0 || strcmp(word, "setenta") == 0) {
		return 70;
	}
	if (strcmp(word, "ochenta,") == 0 || strcmp(word, "ochenta") == 0) {
		return 80;
	}
	if (strcmp(word, "noventa,") == 0 || strcmp(word, "noventa") == 0) {
		return 90;
	}
	return 100;
}

//to lower case
void toLowerCase(char *str) {
	for ( ; *str; ++str) *str = tolower(*str);
}

//Fills from array
void fillStorage() {
	int i = 0;
	int j = 0;
	while(j < 9 && i < words) {
		int num = wordToNumber(numbers[i]);
		if (numbers[i][strlen(numbers[i]) - 1] != ','){
			i += 2;
			if (i < words) {
				num += wordToNumber(numbers[i]);
			}
		}
		if (num == 0) {
			storage[j++] = '0';
		}
		else {
			int k = log10(num) +j;
			j = k + 1;
			while(num > 0) {
				storage[k--] = ('0' + (num % 10));
				num/=10;
			}
		}
		i++;
	}
}

// modify id with digits obtained in other funcs
void modifyId(char *id) {
	int used[9];
	memset(used, 0, sizeof used);
	srand(time(0));
	int i = 0, r;
	while (i < 9) {
		do {
			r = rand()%9;
		} while(used[r] == 1);
		used[r] = 1;
		id[r+3] = storage[i++];
	}
}

int main() {
	char *id = (char *)malloc(15 * sizeof(char));
	printf("Escribe tu ID actual: ");
	fgets(id, 15, stdin);
	printf("Escribe numeros separados por coma:\n");
	char *digits = (char *)malloc(500 * sizeof(char));
	fgets(digits, 500, stdin);
	toLowerCase(digits);
	split(digits);
	int i;
	fillStorage();
	modifyId(id);
	printf("Muchas gracias, el nuevo ID es: %s\n", id);
	return 0;
}
