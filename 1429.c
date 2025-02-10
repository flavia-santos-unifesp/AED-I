/* Flavia Fernandes dos Santos, RA 170563
* Este programa lê um número na notação ACM, converte cada dígito em seu valor decimal correspondente multiplicando-o pelo
* fatorial de sua posição.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para calcular o fatorial de um número
int fatorial(int n) {
    int resultado = 1;
    for (int i = 2; i <= n; i++) {
        resultado *= i;
    }
    return resultado;
}

int main() {
    char entrada[6]; // String para armazenar a entrada (máximo 5 dígitos + '\0')
    while (scanf("%s", entrada) && entrada[0] != '0') { // Lê a entrada até encontrar "0"
        int k = strlen(entrada); // Número de dígitos no número ACM
        int decimal = 0;

        // Converte o número ACM para decimal
        for (int i = 0; i < k; i++) {
            int digito = entrada[k - 1 - i] - '0'; // Dígito atual (da direita para a esquerda)
            int posicao = i + 1; // Posição do dígito (contando da direita para a esquerda)
            decimal += digito * fatorial(posicao);
        }

        // Imprime o resultado
        printf("%d\n", decimal);
    }

    return 0;
}