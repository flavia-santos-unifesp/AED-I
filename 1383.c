// Flavia Fernandes dos Santos, RA 170563
// Este programa confere se uma dada solução para o jogo Sudoku está correta ou não.

#include <stdio.h>


int checkColumn (int matrix[9][9]) {
    int aux [9] = {0};
    int i, j, k;

    for (i = 0; i < 9; i++) {
        for (k = 0; k < 9; k++) {
            aux[k] = 0;
        }
        for (j = 0; j < 9; j++) {
            if (aux[matrix[j][i]-1] == 0) {
                aux[matrix[j][i]-1] = matrix[j][i];
            } else {
                return 1;
            }
        }
    }
    return 0;
}

int checkRow (int matrix[9][9]) {
    int aux [9] = {0};
    int i, j, k;

    for (i = 0; i < 9; i++) {
        for (k = 0; k < 9; k++) {
            aux[k] = 0;
        }
        for (j = 0; j < 9; j++) {
            if (aux[matrix[i][j]-1] == 0) {
                aux[matrix[i][j]-1] = matrix[i][j];
            } else {
                return 1;
            }
        }
    }
    return 0;
}

int check3x3 (int matrix[9][9]) {
    int aux [9] = {0};
    int i, j, k, l, m;

    for (k = 0; k < 7; k = k+3) {
        for (l = 0; l < 7; l = l+3 ) {
            for (m = 0; m < 9; m++) {
                aux[m] = 0;
            }
            for (i = l; i < l + 3; i++) {
                for (j = k; j < k + 3; j++) {
                    if (aux[matrix[i][j]-1] == 0) {
                        aux[matrix[i][j]-1] = matrix[i][j];
                    } else {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

int main () {
    int n, i, j, l;
    int sudoku[9][9];

    scanf ("%d", &n);
    l = 1;

    do {
        for (i = 0; i < 9; i++) {
            for (j = 0; j < 9; j++) {
                scanf ("%d", &sudoku[i][j]);
            }
        }

        if (checkRow(sudoku) + checkColumn(sudoku) + check3x3(sudoku) == 0) {
            printf ("Instancia %d\nSIM\n\n", l);
        } else {
            printf ("Instancia %d\nNAO\n\n", l);
        }
        n--;
        l++;
    } while (n > 0);

    return 0;

}