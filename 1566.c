/* Flavia Fernandes dos Santos, RA 170563
* Este programa recebe a altura dos habitantes, ordena em ordem crescente e imprime o resultado de cada instância.*/

#include <stdio.h>
#include <stdlib.h>

// Função de comparação para qsort
int comparar(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int NC, N;
    scanf("%d", &NC);
    
    while (NC--) {
        scanf("%d", &N);
        int *alturas = (int*)malloc(N * sizeof(int));
        
        for (int i = 0; i < N; i++) {
            scanf("%d", &alturas[i]);
        }
        
        qsort(alturas, N, sizeof(int), comparar);
        
        for (int i = 0; i < N; i++) {
            printf("%d%s", alturas[i], (i < N - 1) ? " " : "\n");
        }
        
        free(alturas);
    }
    
    return 0;
}