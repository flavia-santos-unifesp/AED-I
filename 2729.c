/* Flavia Fernandes dos Santos, RA 170563
* Este programa lê uma lista de compras, remove os itens duplicados e ordena o restante em rodem alfabética.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 21

// Estrutura para representar um nó da lista encadeada
typedef struct Node {
    char item[MAX_WORD_LEN];
    struct Node *next;
} Node;

// Função para criar um novo nó
Node* createNode(const char *item) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    strcpy(newNode->item, item);
    newNode->next = NULL;
    return newNode;
}

// Função para inserir um item na lista em ordem alfabética e sem duplicatas
void insertSorted(Node **head, const char *item) {
    Node *newNode = createNode(item);
    Node *current = *head, *prev = NULL;

    // Verifica se já existe na lista
    while (current != NULL && strcmp(current->item, item) < 0) {
        prev = current;
        current = current->next;
    }
    if (current != NULL && strcmp(current->item, item) == 0) { // Item já existe
        free(newNode);
        return;
    }
    
    // Insere o novo nó na posição correta
    if (prev == NULL) { // Insere no início
        newNode->next = *head;
        *head = newNode;
    } else { // Insere no meio ou no final
        prev->next = newNode;
        newNode->next = current;
    }
}

// Função para liberar a memória da lista
void freeList(Node *head) {
    Node *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Função para imprimir a lista ordenada
void printList(Node *head) {
    while (head) {
        printf("%s", head->item);
        if (head->next)
            printf(" ");
        head = head->next;
    }
    printf("\n");
}

int main() {
    int N;
    scanf("%d", &N);
    getchar(); // Consumir a quebra de linha após o número

    for (int i = 0; i < N; i++) {
        char line[10000];
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = '\0'; // Remover a quebra de linha

        Node *shoppingList = NULL;
        char *token = strtok(line, " ");
        while (token) {
            insertSorted(&shoppingList, token);
            token = strtok(NULL, " ");
        }

        printList(shoppingList);
        freeList(shoppingList);
    }

    return 0;
}
