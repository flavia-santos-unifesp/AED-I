/* Flavia Fernandes dos Santos, RA 170563
* Este programa lê várias strings, armazena-as em uma lista encadeada, calcula o valor de hash para cada string com base nas regras
* fornecidas e imprime o valor de hash total para cada caso de teste.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura para armazenar uma string
typedef struct StringNode {
    char str[51]; // Armazena a string (máximo 50 caracteres + '\0')
    struct StringNode *prox; // Ponteiro para o próximo nó na lista
} StringNode;

// Função para criar um novo nó na lista encadeada
StringNode* criarStringNode(const char *str) {
    StringNode *novo = (StringNode *)malloc(sizeof(StringNode));
    strcpy(novo->str, str);
    novo->prox = NULL;
    return novo;
}

// Função para calcular o valor de hash de uma string
int calcularHash(const char *str, int elemento) {
    int hash = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        int posicaoNoAlfabeto = str[i] - 'A'; // Posição no alfabeto (A=0, B=1, ..., Z=25)
        int posicaoNoElemento = i; // Posição do caractere na string
        hash += posicaoNoAlfabeto + elemento + posicaoNoElemento;
    }
    return hash;
}

int main() {
    int N;
    scanf("%d", &N); // Lê o número de casos de teste

    for (int caso = 0; caso < N; caso++) {
        int L;
        scanf("%d", &L); // Lê o número de linhas (strings) para o caso de teste atual

        StringNode *inicio = NULL;
        StringNode *ultimo = NULL;

        // Lê as strings e as armazena na lista encadeada
        for (int i = 0; i < L; i++) {
            char str[51];
            scanf("%s", str);
            StringNode *novo = criarStringNode(str);
            if (inicio == NULL) {
                inicio = novo;
            } else {
                ultimo->prox = novo;
            }
            ultimo = novo;
        }

        // Calcula o valor de hash para o caso de teste atual
        int hashTotal = 0;
        int elemento = 0;
        StringNode *atual = inicio;
        while (atual != NULL) {
            hashTotal += calcularHash(atual->str, elemento);
            elemento++;
            atual = atual->prox;
        }

        // Imprime o valor de hash
        printf("%d\n", hashTotal);

        // Libera a memória alocada para a lista encadeada
        atual = inicio;
        while (atual != NULL) {
            StringNode *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }

    return 0;
}