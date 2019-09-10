// Andres Aguirre Gonzalez
// A01039656
// 9/09/2019
// Mission1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <string.h>

struct Activo { // 4 letras + 9 digitos
  char activo[100];
};

struct Mission {  // 3 letras + 9 digitos
  char mission[100];
};

struct Agent {
  char name[100];
  char lastName[100];
  int age;
  char actives[100][100]; // 4 letras + 9 digitos
  char missions[100][100]; // 3 letras + 9 digitos
  int activesSize;

};

struct ActivoNode {
  struct ActivoNode* next;
  struct Activo* activo;
};

struct MissionNode {
  struct MissionNode* next;
  struct Mission* mission;
};

struct AgentNode {
  struct AgentNode* next;
  struct Agent* agent;
};

struct List {
  int size;
  struct AgentNode* agentRoot;
  struct ActivoNode* activoRoot;
  struct MissionNode* missionRoot;
};

// LIST methods
void pushbackAgentNode(struct List *list, struct AgentNode *node);
void pushbackMissionNode(struct List *list, struct MissionNode *node);
void pushbackActivoNode(struct List *list, struct ActivoNode *node);

void deleteNode(struct List *list, int index);
void printList(struct List *list);
void initList(struct List *list);

// NODE methods
void initNode(struct AgentNode *node, struct Agent *agent);

// AGENT methods
int isValid(char activo[100], int maxSize, int charSize);
void printAgent(struct Agent *agent);
void fillAgent(struct Agent *agent);
void addMisiones(struct Agent *agent);
void addActives(struct Agent *agent);
int searchAgenteByLastName(struct List *list, char apellido[100]);
int searchAgentByActivo(struct List *list, char activo[100]);

int main(int argc, char *argv[]) {
  // Validate user entered password
  if (argc != 2 || strcmp(argv[1], "12345") != 0 ) {
    fprintf(stdout, "Password incorrecta (maybe trata 12345)");
    exit(-1);
  }
  char another = 'y';
  int choice;
  int index;
  struct List *list;
  struct Agent *agent;
  struct AgentNode *node;
  list = (struct List*) malloc( sizeof( struct List));
  initList(list);
  do {
    fprintf(stdout, "--------------------------------------------\n");
    fprintf(stdout, "| 1-. Crear un nuevo agente.\n");
    fprintf(stdout, "| 2-. Eliminar agente.\n");
    fprintf(stdout, "| 3-. Buscar por apellido.\n");
    fprintf(stdout, "| 4-. Buscar por activo.\n");
    fprintf(stdout, "|\n| 5-. Salir.\n");
    fprintf(stdout, "|\n| Escoge un numero: ");
    fscanf(stdin, "%d", &choice);
    if( choice == 1 ) {
      // Crea una nueva entrada, usar malloc cada vez
      agent = (struct Agent*) malloc( sizeof( struct Agent ) );
      node = (struct AgentNode*) malloc( sizeof( struct AgentNode ) );
      initNode(node, agent);
      fillAgent(agent);
      printAgent(agent);
      pushbackAgentNode(list, node);
      fprintf(stdout, "   -> Creado correctamente!.\n");
    } else if (choice == 2) {
      // Elimina una entrada
      printList(list);
      fprintf(stdout, "Cual agente desea borrar?, teclea id: ");
      fscanf(stdin, "%d", &index);
      if (index >= 0 && index < list->size) deleteNode(list, index);
      else fprintf(stderr, "Agente no existe.\n");
    } else if (choice == 3) {
      // Buscar por apellido
      char apellido[100];
      fprintf(stdout, "Apellido: ");
      fscanf(stdin, "%s", apellido);
      searchAgenteByLastName(list, apellido);
    } else if (choice == 4) {
      // Buscar por activo
      char activo[100];
      fprintf(stdout, "Activo: ");
      fscanf(stdin, "%s", activo);
      searchAgentByActivo(list, activo);
    } else if( choice == 5 ) {
      another = 'n';
    }
  } while(another == 'y');
  fprintf(stdout, "\nByeee!\n");
  return 0;
}

void initList(struct List *list ) {
  list->agentRoot = NULL;
  list->size = 0;
}

void pushbackAgentNode(struct List *list, struct AgentNode *node) {
  struct AgentNode* n = list->agentRoot;
  if (n == NULL) {
    list->agentRoot = node;
    list->size++;
    return;
  }
  while (n->next != NULL) {
    n = n->next;
  }
  // Append it
  n->next = node;
  list->size++;
}

void pushbackMissionNode(struct List *list, struct MissionNode *node) {
  struct MissionNode* n = list->missionRoot;
  if (n == NULL) {
    list->missionRoot = node;
    list->size++;
    return;
  }

  while (n->next != NULL){
    n = n->next;
  }
  // Add
  n->next = node;
  list->size++;
}



void pushbackActivoNode( struct List *list, struct ActivoNode *node ) {
  struct ActivoNode* n = list->activoRoot;
  if (n == NULL) {
    list->activoRoot = node;
    list->size++;
    return;
  }

  while (n->next != NULL) {
    n = n->next;
  }
  // Add
  n->next = node;
  list->size++;
}

void deleteNode( struct List *list, int index ) {
  int i = 0;
  // Check special cases
  if (index+1 > list->size) {
    fprintf(stderr, "El agenete %d no existe.\n", index);
    return;
  }
  struct AgentNode* n = list->agentRoot;
  struct AgentNode* holder = list->agentRoot;
  if (index == 0) {
    list->agentRoot = n->next;
    fprintf(stdout, "Borrado correctamente! ");
    printAgent(n->agent);
    free(n);
    list->size--;
    return;
  }
  while( i < index - 1 ){
    n = n->next;
    i++;
  }
  holder = n->next;
  n->next = n->next->next;
  fprintf(stdout, "Borrado correctamente: ");
  printAgent(holder->agent);
  free(holder);
  list->size--;
}

void printList( struct List *list ) {
  struct AgentNode* node = list->agentRoot;
  int i = 0;
  if (node == NULL) {
    fprintf(stdout, "Lista vacia :(\n");
    return;
  }
  fprintf(stdout, "--------------------------------------------\n");
  fprintf(stdout, "Tama;o de lista de agentes: %d\n", list->size);
  while( node != NULL ) {
    fprintf(stdout, "ID = %d\n", i);
    printAgent(node->agent);
    node = node->next;
    i++;
  }
}

void initNode( struct AgentNode *node, struct Agent *agent ) {
  node->next = NULL;
  node->agent = agent;
}

void printAgent( struct Agent *agent ) {
  fprintf(stdout, "   (%s, %s, %d)\n", agent->name, agent->lastName, agent->age);
}

int searchAgenteByLastName( struct List *list, char apellido[100] ) {
  int choice = 3;
  int agentIndex = 0;
  struct AgentNode *agentNode = list->agentRoot;
  if (agentNode == NULL) {
    fprintf(stderr, "La lista esta vacia.\n");
    return -1;
  }
  while (agentNode != NULL) {
    struct Agent *agent = agentNode->agent;
    if (strcmp(agent->lastName, apellido) == 0) {
      fprintf(stdout, "Encontrado!\n");
      fprintf(stdout, "Agente con apellido %s encontrado.\n", apellido);
      fprintf(stdout, "------------------------------------------\n");
      printAgent(agent);
      fprintf(stdout, "------------------------------------------\n");
      fprintf(stdout, "| 1-. Editar registro.\n");
      fprintf(stdout, "| 2-. Borrar registro.\n");
      fprintf(stdout, "|\n| 3-. Salir.\n");
      fprintf(stdout, "|\n| Selecciona una opcion: ");
      fscanf(stdin, "%d", &choice);
      if( choice == 1 ) {
        addMisiones(agent);
        addActives(agent);
      } else if ( choice == 2 ) {
        deleteNode(list, agentIndex);
      } else if ( choice == 3 ) {
        return 1;
      }
    }
    agentIndex++;
    agentNode = agentNode->next;
  }
  return 1;
}

// Funcion que busca agente por activo
int searchAgentByActivo( struct List *list, char activo[100] ) {
  int choice = 3;
  int agentIndex = 0;
  struct AgentNode *agentNode = list->agentRoot;
  if (agentNode == NULL) {
    fprintf(stderr, "La lista esta vacia.\n");
    return -1;
  }
  while (agentNode != NULL) {
    struct Agent *agent = agentNode->agent;
    for (int i = 0; i < agent->activesSize; i++) {
      if (strcmp(activo, agent->actives[i]) == 0) {
        fprintf(stdout, "Encontrado!\n");
        fprintf(stdout, "Agente con activo %s encontrado.\n", activo);
        fprintf(stdout, "--------------------------------------------\n");
        printAgent(agent);
        fprintf(stdout, "--------------------------------------------\n");
        fprintf(stdout, "| 1-. Editar agente.\n");
        fprintf(stdout, "| 2-. Borrar agente.\n");
        fprintf(stdout, "|\n| 3-. Salir.\n");
        fprintf(stdout, "|\n| Selecciona opcion: ");
        fscanf(stdin, "%d", &choice);

        if( choice == 1 ) {
          addMisiones(agent);
          addActives(agent);
        } else if ( choice == 2 ) {
          deleteNode(list, agentIndex);
        } else if ( choice == 3 ) {
          return 1;
        }
      }
    }
    agentIndex++;
    agentNode = agentNode->next;
  }
  return 1;
}

void addActives( struct Agent *agent ) {
  int n = 0;
  int i = 0;
  fprintf(stdout, "Cantidad activos: " );
  fscanf(stdin, "%d", &n);
  // Validar que los datos de activos ingresados sean correctos
  while (i < n) {
    char activo[100];
    do {
      fprintf(stdout, "Activo(4letras + 9 digitos) id=%d: ", i);
      fscanf(stdin, "%s", activo);
    } while (!isValid(activo, 13, 4));
    strcpy(agent->actives[i], activo);
    fprintf(stdout, "Activo (%s) se ha agregado correctamente.\n", agent->actives[i]);
    i++;
    agent->activesSize++;
  }
}

void addMisiones(struct Agent *agent) {
  int n = 0;
  int i = 0;
  fprintf(stdout, "Cantidad misiones: " );
  fscanf(stdin, "%d", &n);
  // Validar que los datos ingresados sean correctos
  while (i < n) {
    char mission[100];
    do {
      fprintf(stdout, "Mission(3letters+9digits) id=%d: ", i);
      fscanf(stdin, "%s", mission);
    } while (!isValid(mission, 12, 3));
    strcpy(agent->missions[i], mission);
    fprintf(stdout, "Mission (%s) sucessfuly added.\n", agent->missions[i]);
    i++;
  }
}

void fillAgent(struct Agent *agent) {
  agent->activesSize = 0;
  fprintf(stdout, "Name: " );
  fscanf(stdin, "%s", agent->name);
  fprintf(stdout, "Last Name: " );
  fscanf(stdin, "%s", agent->lastName);
  fprintf(stdout, "Age: " );
  fscanf(stdin, "%d", &agent->age);
  addActives(agent);
  addMisiones(agent);
}

int isValid(char activo[100], int maxSize, int charSize) {
  int counter = 0;
  while (activo[counter] != '\0') {
    counter++;
  }
  if (counter != maxSize) return 0;
  counter = 0;
  while (counter < charSize) { // Valida que sea char [a-zA-Z]
    int c = activo[counter];
    if( !((c >= 97 && c <= 122) || (c >= 65 && c <= 90)) ) return 0;
    counter++;
  }
  while (activo[counter] != '\0') { // Valida que sea digito
    int c = (activo[counter] - '0');
    if( !(c >= 0 && c <= 9) ) return 0;
    counter++;
  }
  // Si llega hasta aquí cumplió con todo
  return 1;
}