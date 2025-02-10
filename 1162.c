/* Flavia Fernandes dos Santos, RA 170563
* Este programa conta o número de trocas adjacentes necessárias para ordenar os vagões de um trem usando uma lista encadeada.*/

#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>

// Estrutura para um nó da lista encadeada
typedef struct Node {
    int valor;           // Valor do vagão
    struct Node *proximo; // Ponteiro para o próximo nó
} Node;

// Função para criar um novo nó
Node* criarNo(int valor) {
    Node *novo = (Node*) malloc(sizeof(Node));
    novo->valor = valor;
    novo->proximo = NULL;
    return novo;
}

// Função para inserir um nó no final da lista
void inserirNo(Node **head, int valor) {
    Node *novo = criarNo(valor);
    if (*head == NULL) {
        *head = novo;
        return;
    }
    Node *temp = *head;
    while (temp->proximo != NULL) {
        temp = temp->proximo;
    }
    temp->proximo = novo;
}

// Função para contar o número de trocas necessárias para ordenar a lista
int contarTrocas(Node *head) {
    int trocas = 0;
    int trocado;

    do {
        trocado = 0;
        Node *atual = head;
        Node *anterior = NULL;

        while (atual->proximo != NULL) {
            if (atual->valor > atual->proximo->valor) {
                // Troca os valores dos nós adjacentes
                int temp = atual->valor;
                atual->valor = atual->proximo->valor;
                atual->proximo->valor = temp;
                trocado = 1;
                trocas++;
            }
            anterior = atual;
            atual = atual->proximo;
        }
    } while (trocado);

    return trocas;
}

// Função principal
int main() {
    int N;
    scanf("%d", &N); // Lê o número de casos de teste

    while (N--) {
        int L;
        scanf("%d", &L); // Lê o número de vagões

        Node *head = NULL; // Inicializa a lista como vazia

        // Lê a permutação dos vagões e insere na lista
        for (int i = 0; i < L; i++) {
            int valor;
            scanf("%d", &valor);
            inserirNo(&head, valor);
        }

        // Conta o número de trocas necessárias para ordenar a lista
        int trocas = contarTrocas(head);

        // Imprime o resultado
        printf("Optimal train swapping takes %d swaps.\n", trocas);
    }

    return 0;
}