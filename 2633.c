/* Flavia Fernandes dos Santos, RA 170563
* Este programa lê as peças de carne que serão utilizadas no churrasco e suas datas de validade, insere-as em uma lista encadeada 
* ordenada de forma crescente pela data de validade e, em seguida, imprime a lista ordenada.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura para representar uma peça de carne
typedef struct Carne {
    char nome[21]; // Nome da peça de carne (máximo 20 caracteres + '\0')
    int data_validade; // Dias até a data de validade
    struct Carne *prox; // Ponteiro para a próxima peça de carne na lista
} Carne;

// Função para criar um novo nó (peça de carne) na lista
Carne* criarCarne(const char *nome, int data_validade) {
    Carne *novo = (Carne *)malloc(sizeof(Carne));
    strcpy(novo->nome, nome);
    novo->data_validade = data_validade;
    novo->prox = NULL;
    return novo;
}

// Função para inserir uma peça de carne na lista de forma ordenada (crescente pela data de validade)
void inserirOrdenado(Carne **inicio, const char *nome, int data_validade) {
    Carne *novo = criarCarne(nome, data_validade);
    if (*inicio == NULL || (*inicio)->data_validade > data_validade) {
        // Insere no início se a lista estiver vazia ou a data for menor que a do início
        novo->prox = *inicio;
        *inicio = novo;
    } else {
        // Procura a posição correta para inserir
        Carne *atual = *inicio;
        while (atual->prox != NULL && atual->prox->data_validade < data_validade) {
            atual = atual->prox;
        }
        novo->prox = atual->prox;
        atual->prox = novo;
    }
}

// Função para imprimir a lista de carnes
void imprimirCarnes(Carne *inicio) {
    Carne *atual = inicio;
    while (atual != NULL) {
        printf("%s", atual->nome);
        if (atual->prox != NULL) {
            printf(" ");
        }
        atual = atual->prox;
    }
    printf("\n");
}

// Função para liberar a memória alocada para a lista de carnes
void liberarCarnes(Carne *inicio) {
    Carne *atual = inicio;
    while (atual != NULL) {
        Carne *temp = atual;
        atual = atual->prox;
        free(temp);
    }
}

int main() {
    int N;
    while (scanf("%d", &N) != EOF) { // Lê o número de peças de carne até o fim do arquivo
        Carne *inicio = NULL;

        // Leitura das peças de carne e inserção na lista ordenada
        for (int i = 0; i < N; i++) {
            char nome[21];
            int data_validade;
            scanf("%s %d", nome, &data_validade);
            inserirOrdenado(&inicio, nome, data_validade);
        }

        // Imprime a lista de carnes ordenada
        imprimirCarnes(inicio);

        // Libera a memória alocada para a lista
        liberarCarnes(inicio);
    }

    return 0;
}