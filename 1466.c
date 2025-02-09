/* Flavia Fernandes dos Santos, RA 170563
* Este programa implementa uma árvore binária de busca, realiza a leitura em largura e imprime os nós por nível.*/

#include <stdio.h>
#include <stdlib.h>

// Definição do nó da árvore binária
typedef struct Node {
    int valor;
    struct Node *esquerdo;
    struct Node *direito;
} Node;

// Função para criar um novo nó
Node* criarNo(int valor) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->valor = valor;
    novo->esquerdo = NULL;
    novo->direito = NULL;
    return novo;
}

// Função para inserir um valor na árvore binária de busca
Node* inserir(Node* raiz, int valor) {
    if (raiz == NULL) {
        return criarNo(valor);
    }
    
    if (valor < raiz->valor) {
        raiz->esquerdo = inserir(raiz->esquerdo, valor);
    } else {
        raiz->direito = inserir(raiz->direito, valor);
    }
    
    return raiz;
}

// Estrutura de fila para o percurso BFS
typedef struct Queue {
    Node* nodes[500];  // Fila de nós (máximo de 500 nós)
    int inicio, fim;
} Queue;

// Função para inicializar a fila
void inicializarFila(Queue* fila) {
    fila->inicio = 0;
    fila->fim = 0;
}

// Função para enfileirar um nó
void enfileirar(Queue* fila, Node* node) {
    fila->nodes[fila->fim++] = node;
}

// Função para desenfileirar um nó
Node* desenfileirar(Queue* fila) {
    return fila->nodes[fila->inicio++];
}

// Função para verificar se a fila está vazia
int filaVazia(Queue* fila) {
    return fila->inicio == fila->fim;
}

// Função para percorrer a árvore por nível (BFS)
void percursoBFS(Node* raiz) {
    if (raiz == NULL) {
        return;
    }

    Queue fila;
    inicializarFila(&fila);
    enfileirar(&fila, raiz);

    int primeiro = 1;  // Controla a formatação da saída (evita espaço extra no final)

    while (!filaVazia(&fila)) {
        Node* node = desenfileirar(&fila);
        
        if (!primeiro) {
            printf(" ");
        }
        printf("%d", node->valor);
        primeiro = 0;

        // Enfileirar os filhos esquerdo e direito
        if (node->esquerdo != NULL) {
            enfileirar(&fila, node->esquerdo);
        }
        if (node->direito != NULL) {
            enfileirar(&fila, node->direito);
        }
    }
}

// Função principal
int main() {
    int C; // Número de casos de teste
    scanf("%d", &C);

    for (int caso = 1; caso <= C; caso++) {
        int N; // Número de elementos na árvore
        scanf("%d", &N);
        
        Node* raiz = NULL;

        // Inserir os elementos na árvore binária de busca
        for (int i = 0; i < N; i++) {
            int valor;
            scanf("%d", &valor);
            raiz = inserir(raiz, valor);
        }

        // Imprimir o caso de teste
        printf("Case %d:\n", caso);
        percursoBFS(raiz);
        printf("\n\n"); // Linha em branco após cada caso
    }

    return 0;
}