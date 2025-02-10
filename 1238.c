/* Flavia Fernandes dos Santos, RA 170563
* Este programa lê duas strings, combina-as alternando as letras de cada uma e adiciona as letras restantes da string mais longa no final.*/

#include <stdio.h>
#include <string.h>

// Função para combinar duas strings
void combinador(const char *str1, const char *str2, char *resultado) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int i = 0, j = 0, k = 0;

    // Alterna as letras das duas strings
    while (i < len1 && i < len2) {
        resultado[k++] = str1[i];
        resultado[k++] = str2[i];
        i++;
    }

    // Adiciona as letras restantes da string mais longa
    while (i < len1) {
        resultado[k++] = str1[i++];
    }
    while (i < len2) {
        resultado[k++] = str2[i++];
    }

    resultado[k] = '\0'; // Finaliza a string resultante
}

int main() {
    int N;
    scanf("%d", &N); // Lê o número de casos de teste

    for (int i = 0; i < N; i++) {
        char str1[51], str2[51], resultado[101];
        scanf("%s %s", str1, str2); // Lê as duas strings

        // Combina as duas strings
        combinador(str1, str2, resultado);

        // Imprime a string resultante
        printf("%s\n", resultado);
    }

    return 0;
}