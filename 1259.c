/* Flavia Fernandes dos Santos, RA 170563
* Este programa lê N inteiros não negativos e devolve uma lista com os números ordenados, primeiro os pares em ordem crescente,
* seguidos dos ímpares em ordem decrescente.*/

#include <stdio.h>
#include <stdlib.h>

// Função de comparação para ordenar pares em ordem crescente
int compareEven(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Função de comparação para ordenar ímpares em ordem decrescente
int compareOdd(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    int N;
    scanf("%d", &N); // Lê o número de entradas

    int* values = (int*)malloc(N * sizeof(int)); // Array para armazenar todos os valores
    int* evens = (int*)malloc(N * sizeof(int));  // Array para armazenar os pares
    int* odds = (int*)malloc(N * sizeof(int));   // Array para armazenar os ímpares

    int evenCount = 0, oddCount = 0;

    // Leitura dos valores e separação em pares e ímpares
    for (int i = 0; i < N; i++) {
        scanf("%d", &values[i]);
        if (values[i] % 2 == 0) {
            evens[evenCount++] = values[i]; // Adiciona ao array de pares
        } else {
            odds[oddCount++] = values[i];   // Adiciona ao array de ímpares
        }
    }

    // Ordena os pares em ordem crescente
    qsort(evens, evenCount, sizeof(int), compareEven);

    // Ordena os ímpares em ordem decrescente
    qsort(odds, oddCount, sizeof(int), compareOdd);

    // Imprime os pares em ordem crescente
    for (int i = 0; i < evenCount; i++) {
        printf("%d\n", evens[i]);
    }

    // Imprime os ímpares em ordem decrescente
    for (int i = 0; i < oddCount; i++) {
        printf("%d\n", odds[i]);
    }

    // Libera a memória alocada
    free(values);
    free(evens);
    free(odds);

    return 0;
}