/* Flavia Fernandes dos Santos, RA 170563
* Este programa recebe o percurso prefixo e infixo de uma árvore, e retorna o percurso posfixo.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do nó da árvore binária
typedef struct Node {
    char data;
    struct Node *left, *right;
} Node;

// Função para criar um novo nó
Node* newNode(char data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Função para encontrar a posição do caractere na string infixa
int findPosition(char in[], int start, int end, char value) {
    for (int i = start; i <= end; i++) {
        if (in[i] == value) return i;
    }
    return -1;
}

// Função recursiva para reconstruir a árvore
Node* buildTree(char pre[], char in[], int inStart, int inEnd, int *preIndex) {
    if (inStart > inEnd) return NULL;

    char current = pre[(*preIndex)++];
    Node* node = newNode(current);

    if (inStart == inEnd) return node; // Nó folha

    int inIndex = findPosition(in, inStart, inEnd, current);

    // Constrói a subárvore esquerda e direita recursivamente
    node->left = buildTree(pre, in, inStart, inIndex - 1, preIndex);
    node->right = buildTree(pre, in, inIndex + 1, inEnd, preIndex);

    return node;
}

// Função para percorrer a árvore em pós-ordem e imprimir o resultado
void printPostOrder(Node* root) {
    if (root == NULL) return;
    printPostOrder(root->left);
    printPostOrder(root->right);
    printf("%c", root->data);
}

// Função principal
int main() {
    int C; // Número de casos de teste
    scanf("%d", &C);

    while (C--) {
        int N; // Número de nós
        char pre[53], in[53]; // Strings de percurso prefixo e infixo

        scanf("%d %s %s", &N, pre, in);

        int preIndex = 0;
        Node* root = buildTree(pre, in, 0, N - 1, &preIndex);

        // Imprime o percurso pós-fixo
        printPostOrder(root);
        printf("\n");
    }

    return 0;
}