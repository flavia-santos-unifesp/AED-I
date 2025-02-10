/* Flavia Fernandes dos Santos, RA 170563
* Este programa simula a roda de mate, onde os participantes recebem a cuia sequencialmente até que a água na garrafa térmica seja
* insuficiente para encher outra cuia. O último participante a receber a cuia é considerado o "rico do mate" e o volume de água que
* ele recebe é impresso. O código utiliza uma lista encadeada circular para representar a roda de participantes.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura para representar cada participante da roda de mate
typedef struct Participante {
    char nome[13]; // Nome do participante (máximo 12 caracteres + '\0')
    struct Participante *prox; // Ponteiro para o próximo participante na roda
} Participante;

int main() {
    int N; // Número de participantes na roda
    float L, Q; // L: litros de água na térmica, Q: litros de água por cuia
    Participante *inicio = NULL, *atual = NULL, *novo = NULL;

    // Leitura do número de participantes
    scanf("%d", &N);

    // Leitura da quantidade de água na térmica e na cuia
    scanf("%f %f", &L, &Q);

    // Leitura dos nomes dos participantes e criação da lista encadeada
    for (int i = 0; i < N; i++) {
        novo = (Participante *)malloc(sizeof(Participante));
        scanf("%s", novo->nome);
        novo->prox = NULL;

        if (inicio == NULL) {
            inicio = novo;
        } else {
            atual->prox = novo;
        }
        atual = novo;
    }

    // Fechar o círculo da roda, conectando o último ao primeiro
    if (atual != NULL) {
        atual->prox = inicio;
    }

    // Simulação do consumo de mate
    atual = inicio;
    while (L > Q) {
        L -= Q;
        atual = atual->prox;
    }

    // O participante atual receberá a última cuia
    printf("%s %.1f\n", atual->nome, L);

    // Liberação da memória alocada para a lista encadeada
    Participante *temp;
    for (int i = 0; i < N; i++) {
        temp = inicio;
        inicio = inicio->prox;
        free(temp);
    }

    return 0;
}