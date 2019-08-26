#include <stdio.h>

struct Person {
  char sName[30];
  char sLastName[30];
  int iAge;
  char sGender[10];
  char sId[12];
};

void printPerson(struct Person person) {
  printf("nombre: %s \n", person.sName);
  printf("apellido: %s \n", person.sLastName);
  printf("edad: %d \n", person.iAge);
  printf("genero: %s \n", person.sGender);
  printf("matricula: %s \n", person.sId);
}

int main() {
  struct Person person;
  printf("Teclea tu nombre: ");
  scanf("%s", person.sName);
  printf("Teclea tu apellido: ");
  scanf("%s", person.sLastName);
  printf("Teclea tu edad: ");
  scanf("%d", &person.iAge);
  printf("Teclea tu genero: ");
  scanf("%s", person.sGender);
  printf("Teclea tu id: ");
  scanf("%s", person.sId);
  printPerson(person);
}
