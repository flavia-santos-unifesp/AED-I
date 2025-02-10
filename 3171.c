/* Flavia Fernandes dos Santos, RA 170563
* Este programa utiliza a estrutura Union-Find para gerenciar as conexões entre os segmentos de LED e verificar 
* se todos estão conectados, garantindo que o cordão esteja completo.*/

#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um nó de uma lista encadeada
typedef struct Node {
    int value;
    struct Node* next;
} Node;

// Estrutura para representar um conjunto disjunto (Union-Find)
typedef struct {
    int parent[101]; // Considerando N <= 100
} DisjointSet;

// Função para encontrar o representante do conjunto de um elemento
int find(DisjointSet* ds, int x) {
    if (ds->parent[x] == x) {
        return x;
    }
    return ds->parent[x] = find(ds, ds->parent[x]); // Caminho compressão
}

// Função para unir dois conjuntos
void unionSets(DisjointSet* ds, int x, int y) {
    int rootX = find(ds, x);
    int rootY = find(ds, y);
    if (rootX != rootY) {
        ds->parent[rootY] = rootX;
    }
}

int main() {
    int N, L;
    scanf("%d %d", &N, &L);
    
    DisjointSet ds;
    for (int i = 1; i <= N; i++) {
        ds.parent[i] = i;
    }
    
    // Leitura das ligações e união dos segmentos
    for (int i = 0; i < L; i++) {
        int X, Y;
        scanf("%d %d", &X, &Y);
        unionSets(&ds, X, Y);
    }
    
    // Verifica se todos os segmentos estão conectados
    int root = find(&ds, 1);
    for (int i = 2; i <= N; i++) {
        if (find(&ds, i) != root) {
            printf("INCOMPLETO\n");
            return 0;
        }
    }
    
    printf("COMPLETO\n");
    return 0;
}