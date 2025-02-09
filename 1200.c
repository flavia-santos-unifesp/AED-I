/* Flavia Fernandes dos Santos, RA 170563
* Este programa implementa uma árvore binária de busca, permite que novos valores sejam inseridos e a realização de buscas.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do nó da árvore
typedef struct Node {
    char data;               // Valor do nó (um caractere)
    struct Node* left;       // Ponteiro para o filho esquerdo
    struct Node* right;      // Ponteiro para o filho direito
} Node;

// Função para criar um novo nó
Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Função para inserir um nó na árvore
Node* insertNode(Node* root, char data) {
    if (root == NULL) {
        return createNode(data); // Se a árvore estiver vazia, cria um novo nó
    }
    if (data < root->data) {
        root->left = insertNode(root->left, data); // Insere à esquerda se o valor for menor
    } else if (data > root->data) {
        root->right = insertNode(root->right, data); // Insere à direita se o valor for maior
    }
    return root;
}

// Função para percurso infixo (em-ordem)
void inOrder(Node* root, int* isFirst) {
    if (root != NULL) {
        inOrder(root->left, isFirst);
        if (*isFirst) {
            printf("%c", root->data); // Primeiro elemento não tem espaço antes
            *isFirst = 0;
        } else {
            printf(" %c", root->data); // Demais elementos têm espaço antes
        }
        inOrder(root->right, isFirst);
    }
}

// Função para percurso prefixo (pré-ordem)
void preOrder(Node* root, int* isFirst) {
    if (root != NULL) {
        if (*isFirst) {
            printf("%c", root->data); // Primeiro elemento não tem espaço antes
            *isFirst = 0;
        } else {
            printf(" %c", root->data); // Demais elementos têm espaço antes
        }
        preOrder(root->left, isFirst);
        preOrder(root->right, isFirst);
    }
}

// Função para percurso posfixo (pós-ordem)
void postOrder(Node* root, int* isFirst) {
    if (root != NULL) {
        postOrder(root->left, isFirst);
        postOrder(root->right, isFirst);
        if (*isFirst) {
            printf("%c", root->data); // Primeiro elemento não tem espaço antes
            *isFirst = 0;
        } else {
            printf(" %c", root->data); // Demais elementos têm espaço antes
        }
    }
}

// Função para pesquisar um elemento na árvore
void searchNode(Node* root, char data) {
    while (root != NULL) {
        if (data < root->data) {
            root = root->left; // Procura à esquerda se o valor for menor
        } else if (data > root->data) {
            root = root->right; // Procura à direita se o valor for maior
        } else {
            printf("%c existe\n", data); // Elemento encontrado
            return;
        }
    }
    printf("%c nao existe\n", data); // Elemento não encontrado
}

// Função principal
int main() {
    Node* root = NULL; // Inicializa a árvore vazia
    char command[10];  // Buffer para armazenar o comando
    char data;         // Valor a ser inserido ou pesquisado

    while (scanf("%s", command) != EOF) { // Lê comandos até o final do arquivo
        if (strcmp(command, "I") == 0) {  // Comando de inserção
            scanf(" %c", &data);          // Lê o valor a ser inserido
            root = insertNode(root, data);
        } else if (strcmp(command, "INFIXA") == 0) { // Comando de percurso infixo
            int isFirst = 1; // Flag para controlar o espaço antes do primeiro elemento
            inOrder(root, &isFirst);
            printf("\n");
        } else if (strcmp(command, "PREFIXA") == 0) { // Comando de percurso prefixo
            int isFirst = 1; // Flag para controlar o espaço antes do primeiro elemento
            preOrder(root, &isFirst);
            printf("\n");
        } else if (strcmp(command, "POSFIXA") == 0) { // Comando de percurso posfixo
            int isFirst = 1; // Flag para controlar o espaço antes do primeiro elemento
            postOrder(root, &isFirst);
            printf("\n");
        } else if (strcmp(command, "P") == 0) { // Comando de pesquisa
            scanf(" %c", &data); // Lê o valor a ser pesquisado
            searchNode(root, data);
        }
    }

    return 0;
}