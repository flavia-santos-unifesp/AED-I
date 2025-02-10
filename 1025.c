/* Flavia Fernandes dos Santos, RA 170563
* Este programa ordena os mármores em um array e utiliza uma busca binária modificada para retornar a primeira ocorrência de 
* um número duplicado.*/

#include <stdio.h>
#include <stdlib.h>

// Função de comparação para qsort
int comparar(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Função de busca binária modificada para retornar a primeira ocorrência
int buscaBinariaPrimeiraOcorrencia(int *array, int tamanho, int chave) {
    int esquerda = 0, direita = tamanho - 1;
    int resultado = -1; // Armazena a posição da primeira ocorrência

    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;

        if (array[meio] == chave) {
            resultado = meio; // Armazena a posição encontrada
            direita = meio - 1; // Continua buscando na metade esquerda
        } else if (array[meio] < chave) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    if (resultado != -1) {
        return resultado + 1; // Retorna a posição (1-based)
    }
    return -1; // Retorna -1 se o número não for encontrado
}

// Função principal
int main() {
    int caso = 1; // Contador de casos de teste
    while (1) {
        int N, Q;
        scanf("%d %d", &N, &Q); // Lê o número de mármores e consultas

        if (N == 0 && Q == 0) break; // Termina o programa se N = 0 e Q = 0

        int *marmores = (int*) malloc(N * sizeof(int)); // Aloca memória para os mármores

        // Lê os números dos mármores
        for (int i = 0; i < N; i++) {
            scanf("%d", &marmores[i]);
        }

        // Ordena os mármores em ordem crescente
        qsort(marmores, N, sizeof(int), comparar);

        printf("CASE# %d:\n", caso); // Imprime o número do caso de teste

        // Processa as consultas
        for (int i = 0; i < Q; i++) {
            int consulta;
            scanf("%d", &consulta);
            int posicao = buscaBinariaPrimeiraOcorrencia(marmores, N, consulta); // Busca a posição do número consultado

            if (posicao != -1) {
                printf("%d found at %d\n", consulta, posicao); // Número encontrado
            } else {
                printf("%d not found\n", consulta); // Número não encontrado
            }
        }

        free(marmores); // Libera a memória alocada
        caso++; // Incrementa o contador de casos de teste
    }

    return 0;
}