/* Flavia Fernandes dos Santos, RA 170563
* Este programa utiliza o algoritmo de Kruskal para calcular a economia máxima ao desligar a iluminação das estradas.*/

#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar uma aresta do grafo
typedef struct Aresta {
    int origem, destino, custo;
} Aresta;

// Estrutura para representar um subconjunto para o algoritmo de Kruskal
typedef struct Subconjunto {
    int pai, rank;
} Subconjunto;

// Função de comparação para ordenar as arestas por peso
int compararArestas(const void *a, const void *b) {
    return ((Aresta*)a)->custo - ((Aresta*)b)->custo;
}

// Função para encontrar o subconjunto de um elemento "i" (usando caminho comprimido)
int encontrar(Subconjunto subconjuntos[], int i) {
    if (subconjuntos[i].pai != i)
        subconjuntos[i].pai = encontrar(subconjuntos, subconjuntos[i].pai);
    return subconjuntos[i].pai;
}

// Função para unir dois subconjuntos (união por rank)
void unir(Subconjunto subconjuntos[], int x, int y) {
    int raizX = encontrar(subconjuntos, x);
    int raizY = encontrar(subconjuntos, y);
    
    if (subconjuntos[raizX].rank < subconjuntos[raizY].rank)
        subconjuntos[raizX].pai = raizY;
    else if (subconjuntos[raizX].rank > subconjuntos[raizY].rank)
        subconjuntos[raizY].pai = raizX;
    else {
        subconjuntos[raizY].pai = raizX;
        subconjuntos[raizX].rank++;
    }
}

int main() {
    int m, n;
    while (scanf("%d %d", &m, &n) && (m || n)) {
        Aresta *arestas = (Aresta*)malloc(n * sizeof(Aresta));
        int custoTotal = 0;
        
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &arestas[i].origem, &arestas[i].destino, &arestas[i].custo);
            custoTotal += arestas[i].custo;
        }
        
        // Ordenar as arestas pelo menor custo
        qsort(arestas, n, sizeof(Aresta), compararArestas);
        
        // Estruturas para o algoritmo de Kruskal
        Subconjunto *subconjuntos = (Subconjunto*)malloc(m * sizeof(Subconjunto));
        for (int i = 0; i < m; i++) {
            subconjuntos[i].pai = i;
            subconjuntos[i].rank = 0;
        }
        
        int custoMST = 0;
        for (int i = 0, arestasUsadas = 0; arestasUsadas < m - 1 && i < n; i++) {
            int origem = arestas[i].origem;
            int destino = arestas[i].destino;
            
            int raizOrigem = encontrar(subconjuntos, origem);
            int raizDestino = encontrar(subconjuntos, destino);
            
            if (raizOrigem != raizDestino) {
                unir(subconjuntos, raizOrigem, raizDestino);
                custoMST += arestas[i].custo;
                arestasUsadas++;
            }
        }
        
        printf("%d\n", custoTotal - custoMST);
        
        free(arestas);
        free(subconjuntos);
    }
    return 0;
}