// Andres Aguirre Gonzalez
// A01039656
// 20 de Septiembre del 2019

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//Inserts new element
//Receives the current #, the number of #, the frequencies and the new string
void insert(char **hashtags, int *numberOfhashtags, int frequencies[], char *newString) {
	int i;
	for (i = 0; i < *numberOfhashtags; i++) {
		if (strcmp(hashtags[i], newString) == 0) {
			frequencies[i]++;
			return;
		}
	}
	hashtags[*numberOfhashtags] = newString;
	frequencies[*numberOfhashtags] = 1;
	*numberOfhashtags = *numberOfhashtags + 1;	
}

//Print final list
//Receives the current #, the number of # and the frequencies
void showList(char **hashtags, int numberOfhashtags, int frequencies[]) {
	printf("%30s %20s\n", "Hashtag", "Frecuencia");
	int i;
	for (i = 0; i < numberOfhashtags; i++) {
		printf("%30s %20d\n", hashtags[i], frequencies[i]);
	}
}

int main() {
	char **hashtags = (char**) malloc (1000 * sizeof  (char*));
	int frequencies[1000];
	int numberOfhashtags = 0;
	char c, previous;
	FILE *file;
	file = fopen("marco.txt", "r");
	if (file)  {
		previous = ' ';
		c = getc(file);
	    while (c != EOF) {
	    	if (c == '#' && previous == '>') {
	    		char *newString = (char*) malloc (500* sizeof  (char));
	    		int iterator = 0;
	    		newString[iterator++] = '#';
	    		c = getc(file);
	    		while (c != EOF &&   (isdigit  (c) || isalpha  (c))) {
	    			newString[iterator++] = c;
	    			previous = c = getc  (file);
				}
				newString[iterator] = '\0';
				insert(hashtags, &numberOfhashtags, frequencies, newString);
			}
			else  {
				previous = c;
			}
			if (c != EOF) {
				c = getc(file);
			}
		}
	    fclose(file);
	    showList(hashtags, numberOfhashtags, frequencies);
	}
	return 0;
}