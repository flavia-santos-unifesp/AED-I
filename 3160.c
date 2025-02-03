/* Flavia Fernandes dos Santos, RA 170563
* Este programa lê duas listas de nomes e devolve uma lista atualizada de acordo com os critérios do problema.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 30

typedef struct Node {                   //Estrutura para o nó
    char name[MAX_NAME_LENGTH];
    struct Node *next;
} Node;

typedef struct List {                   //Estrutura para a Lista
    int size;
    Node *head;
} List;

List *createList() {
    List *list = (List *)malloc(sizeof(List));
    if (list != NULL) {
        list->size = 0;
        list->head = NULL;
    }
    return list;
}

void insere_final (List *list, const char *name) {              //insere os nomes no final da lista
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode != NULL) {
        strcpy(newNode->name, name);
        newNode->next = NULL;

        if (list->head == NULL) {                    //Se a lista estiver vazia o novo nó é o primeiro da lista
            list->head = newNode;
        } else {
            Node *current = list->head;             
            while (current->next != NULL) {          //Quando a lista não é vazia, percorre a lista até o ultimo nó
                current = current->next;
            }
            current->next = newNode;
        }

        list->size++;
    }
}

void insere_antes (List *list, const char *name, const char *nomeReferencia) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode != NULL) {
        strcpy(newNode->name, name);

        if (strcmp(list->head->name, nomeReferencia) == 0) {                    //Se o nome procurado for o primeiro da lista, o novo nó é inserido antes da cabeça
            newNode->next = list->head;
            list->head = newNode;
        } else {
            Node *current = list->head;                          
            while (current->next != NULL && strcmp(current->next->name, nomeReferencia) != 0) { //Caso o nome referencia nao seja o primeiro, o código vai percorrer até encontrar o nome ou chegar no final da lista
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }

        list->size++;
    }
}

void printList(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        printf("%s", current->name);
        if (current->next != NULL) {
            printf(" ");
        }
        current = current->next;
    }
}


int main() {
    List *friendsList = createList();

    char currentName[MAX_NAME_LENGTH];
    char newName[MAX_NAME_LENGTH];
    char nomeReferencia[MAX_NAME_LENGTH];

    // Ler a lista atual de amigos
    fgets(currentName, MAX_NAME_LENGTH, stdin);
    currentName[strcspn(currentName, "\n")] = '\0';

    char *token = strtok(currentName, " ");
    while (token != NULL) {
        insere_final (friendsList, token);
        token = strtok(NULL, " ");
    }

    // Ler a nova lista de amigos
    fgets(newName, MAX_NAME_LENGTH, stdin);
    newName[strcspn(newName, "\n")] = '\0';

    // Ler o nome do amigo que receberá a nova lista
    fgets(nomeReferencia, MAX_NAME_LENGTH, stdin);
    nomeReferencia[strcspn(nomeReferencia, "\n")] = '\0';

    // Se o nome do amigo que receberá a nova lista for diferente de "nao", insere antes dele; caso contrário, insere no final
    if (strcmp(nomeReferencia, "nao") != 0) {
        insere_antes (friendsList, newName, nomeReferencia);
    } else {
        insere_final (friendsList, newName);
    }

    // Imprimir a lista atualizada de amigos
    printList(friendsList);
    printf("\n");

    // Liberação de memória
    Node *current = friendsList->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(friendsList);

    return 0;
}