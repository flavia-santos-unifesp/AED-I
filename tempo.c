#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

int const numero_de_testes = 3; //constante para quantidade de testes por tamanho
int const MAX_TAM = 400000; //constante para tamanho do vetor

void insertionSort (int v[], int TAM) {
    for(int i = 1; i < TAM; i++) {
        for(int j = i; (j > 0) && (v[j - 1] > v[j]); j--) {
            // Troca valores de lugar
            int aux = v[j];
            v[j] = v[j - 1];
            v[j - 1] = aux;
        }
    }
}

void CopyArray(int A[], int iBegin, int iEnd, int B[]) {
    for (int k = iBegin; k < iEnd; k++)
        B[k] = A[k];
}


void TopDownMerge(int B[], int iBegin, int iMiddle, int iEnd, int A[]) {
    int i = iBegin, j = iMiddle;
 
    for (int k = iBegin; k < iEnd; k++) {
        
        if (i < iMiddle && (j >= iEnd || A[i] <= A[j])) {
            B[k] = A[i];
            i = i + 1;
        } else {
            B[k] = A[j];
            j = j + 1;
        }
    }
}


void TopDownSplitMerge(int B[], int iBegin, int iEnd, int A[]) {
    if (iEnd - iBegin <= 1)                     
        return;                                 
    
    int iMiddle = (iEnd + iBegin) / 2;              
    TopDownSplitMerge(A, iBegin, iMiddle, B);  
    TopDownSplitMerge(A, iMiddle, iEnd, B); 
    TopDownMerge(B, iBegin, iMiddle, iEnd, A);
}


void mergeSort(int A[], int TAM) {
    int B[TAM];
    CopyArray(A, 0, TAM, B);           
    TopDownSplitMerge(A, 0, TAM, B);  

}

int partition(int A[], int lo, int hi) { 
  int pivot = A[hi]; 

  int i = lo;

  for (int j = lo; j < hi - 1; j++) {
    
    if (A[j] <= pivot) {
      
      int aux = A[i];
      A[i] = A[j];
      A[j] = aux;
      
      i = i + 1;
    }
  }

  
  int aux = A[i];
  A[i] = A[hi];
  A[hi] = aux;

  return i; 
}


void quickSort(int A[], int lo, int hi) { 
  
  if (lo >= hi || lo < 0)
    return;

  
  int p = partition(A, lo, hi);
      
  
  quickSort(A, lo, p - 1); 
  quickSort(A, p + 1, hi); 
}


int main() {
    clock_t t1[numero_de_testes], t2[numero_de_testes], t3[numero_de_testes]; 
    int insertion_vetor[MAX_TAM];
    int merge_vetor[MAX_TAM];
    int quick_vetor[MAX_TAM];
    int tamanho = 400000;

    //semente de aleatoriedade
    srand((unsigned)time(NULL));
    while (tamanho == MAX_TAM){
        for(int i = 0; i < numero_de_testes; i++) {
            //geração aleatório dos valores do vetor
            for(int a = 0; a < tamanho; a++) {
                int number = rand() % tamanho;
                insertion_vetor[a] = number;
                merge_vetor[a] = number;
                quick_vetor[a] = number;
            }
            //Verificando tempo de execução Insertion Sort
            t1[i] = clock(); //armazena tempo
            insertionSort(insertion_vetor, tamanho);
            t1[i] = clock()-t1[i]; //tempo final-tempo

            //Verificando tempo de execução Merge Sort
            t2[i] = clock(); //armazena tempo
            mergeSort(merge_vetor, tamanho);
            t2[i] = clock()-t2[i]; //tempo final-tempo

            //Verificando tempo de execução Quick Sort
            t3[i] = clock(); //armazena tempo
            quickSort(quick_vetor, 0, tamanho);
            t3[i] = clock()-t3[i]; //tempo final-tempo
        }
        printf("%d\n", tamanho);
        for(int i = 0; i < numero_de_testes; i++) {
            //imprime o tempo na tela
            printf("%lf\n", ((double)t1[i])/((CLOCKS_PER_SEC/1000))); //conversão para double
            printf("%lf\n", ((double)t2[i])/((CLOCKS_PER_SEC/1000))); //conversão para double
            printf("%lf\n", ((double)t3[i])/((CLOCKS_PER_SEC/1000))); //conversão para double
        }
        printf(">>\n");
        fflush(stdout);
        tamanho += 20000;
    }

    return 0;
}