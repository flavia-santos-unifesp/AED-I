/* Flavia Fernandes dos Santos, RA 170563
* Este programa organiza as camisetas em uma lista encadeada, ordenando-as por cor, tamanho e nome.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para um nó da lista encadeada
typedef struct Node {
    char nome[100];      // Nome do estudante
    char cor[20];        // Cor do logo ("branco" ou "vermelho")
    char tamanho;        // Tamanho da camiseta ('P', 'M' ou 'G')
    struct Node *proximo; // Ponteiro para o próximo nó
} Node;

// Função para criar um novo nó
Node* criarNo(char nome[], char cor[], char tamanho) {
    Node *novo = (Node*) malloc(sizeof(Node));
    strcpy(novo->nome, nome);
    strcpy(novo->cor, cor);
    novo->tamanho = tamanho;
    novo->proximo = NULL;
    return novo;
}

// Função para inserir um nó na lista de forma ordenada
void inserirOrdenado(Node **head, char nome[], char cor[], char tamanho) {
    Node *novo = criarNo(nome, cor, tamanho);
    if (*head == NULL) {
        *head = novo;
        return;
    }

    Node *atual = *head;
    Node *anterior = NULL;

    // Percorre a lista para encontrar a posição correta
    while (atual != NULL) {
        // Ordena por cor (ascendente)
        if (strcmp(cor, atual->cor) < 0) {
            break;
        } else if (strcmp(cor, atual->cor) == 0) {
            // Ordena por tamanho (descendente)
            if (tamanho > atual->tamanho) {
                break;
            } else if (tamanho == atual->tamanho) {
                // Ordena por nome (ascendente)
                if (strcmp(nome, atual->nome) < 0) {
                    break;
                }
            }
        }
        anterior = atual;
        atual = atual->proximo;
    }

    // Insere o novo nó na posição correta
    if (anterior == NULL) {
        novo->proximo = *head;
        *head = novo;
    } else {
        novo->proximo = atual;
        anterior->proximo = novo;
    }
}

// Função para imprimir a lista
void imprimirLista(Node *head) {
    Node *atual = head;
    while (atual != NULL) {
        printf("%s %c %s\n", atual->cor, atual->tamanho, atual->nome);
        atual = atual->proximo;
    }
}

// Função principal
int main() {
    int N;
    int caso = 0; // Contador de casos de teste

    while (1) {
        scanf("%d", &N); // Lê o número de camisetas
        getchar(); // Consome o \n após o número

        if (N == 0) break; // Termina o programa se N = 0

        if (caso > 0) {
            printf("\n"); // Linha em branco entre casos de teste
        }

        Node *head = NULL; // Inicializa a lista como vazia

        // Lê as informações das camisetas
        for (int i = 0; i < N; i++) {
            char nome[100];
            char cor[20];
            char tamanho;

            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = '\0'; // Remove o \n do nome

            scanf("%s %c", cor, &tamanho);
            getchar(); // Consome o \n após o tamanho

            inserirOrdenado(&head, nome, cor, tamanho); // Insere na lista ordenada
        }

        imprimirLista(head); // Imprime a lista ordenada
        caso++;
    }

    return 0;
}