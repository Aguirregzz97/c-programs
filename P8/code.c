// Andres Aguirre Gonzalez
// A01039656
// 06/09/2019
// Tipos de datos
#include <stdio.h>
#include <float.h>

union Data {
	int i;
	char c;
	double d;
};

int main() {
	union Data data;
	char line;
	printf("Write an integer: ");
	scanf("%d%c", &data.i, &line);

	printf("Your integer %d storage size is %lu bytes.\n", data.i, sizeof data.i);

	printf("Write a char: ");
	scanf("%c", &data.c);

	printf("Your char %c storage size is %lu bytes. And I can read it as %c or as %d.\n",
		data.c, sizeof data.c, data.c, data.c);

	printf("Write a double: ");
	scanf("%lf", &data.d);

	printf("Your double %lf storage size is %lu bytes, I can read any number from %lf to %lf in this data type.\n",
		data.d, sizeof data.d, -DBL_MAX, DBL_MAX);
}
