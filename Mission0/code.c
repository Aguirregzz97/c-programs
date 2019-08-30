// Andres Aguirre Gonzalez A01039656
// 28/08/2019
// Mission 0


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>


struct Person {
  char sName[30];
  char sLastName[30];
  int iActiveSize;
  char sActive[10][14];
  int iAge;
  char sMission[10][13];
  int iMissionSize;
};

struct Node {
  struct Node *next;
  struct Person person;
};

void addToList(struct Node *root, struct Person person) {
  struct Node *new = NULL;
  new = (struct Node *)malloc(sizeof(struct Node));
  new->person = person;
  if (root == NULL) {
    printf("HERE");
    root = new;
  }
  else {
    new->next = root;
  }
}

void deleteNode(struct Node *root) {
  struct Node *tmp = root;
  if (tmp == NULL) {
    return;
  }
  free(root);
}

void initializeStructs(struct Person persons[100]) {
  for (int i = 0; i < 100; i++) {
    strcpy(persons[i].sName, "");
  }
}

void printPerson(struct Person person) {
  if (!strcmp(person.sName, "")) {
    return;
  }
  printf("nombre: %s \n", person.sName);
  printf("apellido: %s \n", person.sLastName);
  printf("edad: %d \n", person.iAge);
  for (int i = 0; i < person.iActiveSize; i++) {
    printf("Activo: %13s\n", person.sActive[i]);
  }
  for (int i = 0; i < person.iMissionSize; i++) {
    printf("Mision: %12s\n", person.sMission[i]);
  }
}


bool validateActive(char sActive[13]) {
  for (int i = 0; i < 4; i++) {
    if (sActive[i] == '\0' || isdigit(sActive[i])) {
      return false;
    }
  }
  for (int i = 4; i < 13; i ++) {
    if (sActive[i] == '\0' || isalpha(sActive[i])) {
      return false;
    }
  }
  return true;
}

bool validateMission(char sActive[12]) {
  for (int i = 0; i < 3; i++) {
    if (sActive[i] == '\0' || isdigit(sActive[i])) {
      return false;
    }
  }
  for (int i = 3; i < 12; i ++) {
    if (sActive[i] == '\0' || isalpha(sActive[i])) {
      return false;
    }
  }
  return true;
}

struct Person newEntry() {
  struct Person person;
  printf("Teclea tu nombre: ");
  scanf("%s", person.sName);
  printf("Teclea tu apellido: ");
  scanf("%s", person.sLastName);
  printf("Teclea tu edad: ");
  scanf("%d", &person.iAge);
  int actSize = 0;
  printf("Cuantos activos deseas registrar?\n");
  scanf("%d", &actSize);
  person.iActiveSize = actSize;
  printf("Teclea tu activo con formato correcto\n");
  for (int i = 0; i < actSize; i++) {
    char sActiveG[13] = "";
    while (true) {
      char sActive[13] = "";
      scanf("%s", sActive);
      if (!validateActive(sActive)) {
        printf("Activo incorrecto, el formato es 4 letras y 9 caracteres, intenta de nuevo\n");
      }
      else {
        strcpy(sActiveG, sActive);
        break;
      }
    }
    strcpy(person.sActive[i], sActiveG);
  }
  int missionSize = 0;
  printf("Cuantas misiones deseas registrar?\n");
  scanf("%d", &missionSize);
  person.iMissionSize = missionSize;
  printf("Teclea tu mision con formato correcto\n");
  for (int i = 0; i < missionSize; i++) {
    char sMissionG[13] = "";
    while (true) {
      char sMission[13] = "";
      scanf("%s", sMission);
      if (!validateMission(sMission)) {
        printf("Activo incorrecto, el formato es 3 letras y 9 caracteres, intenta de nuevo\n");
      }
      else {
        strcpy(sMissionG, sMission);
        break;
      }
    }
    strcpy(person.sMission[i], sMissionG);
  }
end:
  return person;
}

int main() {
  struct Node *root = NULL;
  root = (struct Node *)malloc(sizeof(struct Node));
  int iD = 0;
  int iCount = 0;
  while (true) {
    printf("Para capturar presiona 1\nPara salir presiona 0\nPara borrar un elemento presiona 2\n");
    scanf("%d", &iD);
    if (iD == 1) {
      struct Person person = newEntry();
      addToList(root, person);
      iCount++;
    } else if (iD == 0) {
      struct Node *node = root;
      for (int i = 0; i < iCount; i++) {
        printPerson(node->person);
        node = node->next;
      }
    } else if (iD == 2) {
      deleteNode(root);
    }
  }
}
