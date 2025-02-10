/* Flavia Fernandes dos Santos, RA 170563
* Este programa lê dois valores A e B como strings, verifica se B corresponde aos últimos dígitos de A.*/

#include <stdio.h>
#include <string.h>

// Função para verificar se B encaixa em A
int encaixa(const char *A, const char *B) {
    int lenA = strlen(A);
    int lenB = strlen(B);

    // Se B for maior que A, não pode encaixar
    if (lenB > lenA) {
        return 0;
    }

    // Compara os últimos dígitos de A com B
    for (int i = 0; i < lenB; i++) {
        if (A[lenA - lenB + i] != B[i]) {
            return 0;
        }
    }

    return 1;
}

int main() {
    int N;
    scanf("%d", &N); // Lê o número de casos de teste

    for (int i = 0; i < N; i++) {
        char A[1001], B[1001];
        scanf("%s %s", A, B); // Lê os valores A e B como strings

        // Verifica se B encaixa em A
        if (encaixa(A, B)) {
            printf("encaixa\n");
        } else {
            printf("nao encaixa\n");
        }
    }

    return 0;
}