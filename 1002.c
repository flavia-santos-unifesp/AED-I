// Flavia Fernandes dos Santos, RA 170563

#include <stdio.h>
#include <math.h>

int main () {

    double pi = 3.14159;
    double R, A;

    scanf ("%lf", &R);
    A = pi * (pow(R,2));

    printf ("A=%.4f\n",A);

    return 0;

}