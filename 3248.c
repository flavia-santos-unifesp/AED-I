/* Flavia Fernandes dos Santos, RA 170563
* Este programa conta o número de triplas invertidas em uma sequência.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005

// Árvore de Fenwick (BIT) para contagem de inversões
int BIT[MAX_N];

// Atualiza o BIT, incrementando o valor em um índice específico
void update(int index, int value, int n) {
    while (index <= n) {
        BIT[index] += value;
        index += index & -index;
    }
}

// Consulta a soma acumulada no BIT até um determinado índice
int query(int index) {
    int sum = 0;
    while (index > 0) {
        sum += BIT[index];
        index -= index & -index;
    }
    return sum;
}

// Função para contar triplas invertidas usando Fenwick Tree
long long countInvertedTriples(int arr[], int n) {
    long long count = 0;
    int right[MAX_N] = {0};
    int left[MAX_N] = {0};
    
    // Limpa a árvore de Fenwick
    memset(BIT, 0, sizeof(BIT));
    
    // Conta quantos elementos menores existem à direita de cada posição
    for (int i = n - 1; i >= 0; i--) {
        right[i] = query(arr[i] - 1);
        update(arr[i], 1, n);
    }
    
    // Limpa a árvore de Fenwick
    memset(BIT, 0, sizeof(BIT));
    
    // Conta quantos elementos maiores existem à esquerda de cada posição
    for (int i = 0; i < n; i++) {
        left[i] = query(n) - query(arr[i]);
        update(arr[i], 1, n);
    }
    
    // Conta as triplas invertidas
    for (int i = 0; i < n; i++) {
        count += (long long)left[i] * right[i];
    }
    
    return count;
}

int main() {
    int n;
    scanf("%d", &n);
    
    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    long long result = countInvertedTriples(arr, n);
    printf("%lld\n", result);
    
    free(arr);
    return 0;
}