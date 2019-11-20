// Andres Aguirre Gonzalez
// A01039656
// Num factorial

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


int exponente[1000000];



int main() {
	int size;
  int t;
  static const char filename[] = "input.txt";
  FILE *file = fopen(filename, "r");
	char line[256]; /* or other suitable maximum line size */
	fgets(line, sizeof line, file);
  t = atoi(line);
	size = t;

	int results[t];

	int i;
	int z = 0;
	while (t--) {
		int n;
		fgets(line, sizeof line, file);
		n = atoi(line);
		memset(exponente, 0, sizeof exponente);
		while (n--) {
			int a;
			fgets(line, sizeof line, file);
			a = atoi(line);
			int r = sqrt(a);
			for (i=2; i<=r; i++) {
				if(a % i == 0) {
					while (a % i == 0) {
						a /= i;
						exponente[i] ++;
					}
					r = sqrt(a);
				}
			}
			if (a > 1) exponente[a] ++;
		}
		long long res = 1;
		for(i=2; i<1000000; i++){
			res *= (exponente[i] + 1);
		}
		results[z] = res;
		z++;
	}
	fclose(file);
	file = fopen("results.txt", "w");
	for (int r = 0; r < size; r++) {
		sprintf(line, "%d", results[r]);
		fputs(line, file);
		fputs("\n", file);
	}
	return 0;
}
