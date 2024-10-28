// Flavia Fernandes dos Santos, RA 170563

#include <stdio.h>

int main () {

    int n;
    double dia, mes, ano;

    scanf ("%d", &n);

    ano = n/365;
    mes = (n % 365)/30;
    dia = (n % 365) % 30;

    printf ("%.0lf ano(s)\n%.0lf mes(es)\n%.0lf dia(s)\n", ano, mes, dia);

    return 0;
}