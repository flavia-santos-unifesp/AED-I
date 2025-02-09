/* Flavia Fernandes dos Santos, RA 170563
* Este programa implementa o algoritmo de Kruskal para encontrar a árvore geradora mínima.*/

#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar uma aresta
typedef struct Edge {
    int v, w, cost;
} Edge;

// Estrutura para representar um subconjunto para Union-Find
typedef struct Subset {
    int parent, rank;
} Subset;

// Função de comparação para ordenar as arestas pelo custo
int compareEdges(const void *a, const void *b) {
    return ((Edge *)a)->cost - ((Edge *)b)->cost;
}

// Função para encontrar o representante do conjunto de um elemento (com compressão de caminho)
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Função para unir dois subconjuntos (usando união por rank)
void unionSets(Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);
    
    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// Função principal para calcular o custo mínimo da árvore geradora mínima (MST)
int kruskalMST(int R, int C, Edge edges[]) {
    qsort(edges, C, sizeof(Edge), compareEdges);
    
    Subset *subsets = (Subset *)malloc(R * sizeof(Subset));
    for (int v = 0; v < R; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    
    int totalCost = 0, edgesUsed = 0;
    for (int i = 0; i < C && edgesUsed < R - 1; i++) {
        int rootV = find(subsets, edges[i].v - 1);
        int rootW = find(subsets, edges[i].w - 1);
        
        if (rootV != rootW) {
            totalCost += edges[i].cost;
            unionSets(subsets, rootV, rootW);
            edgesUsed++;
        }
    }
    
    free(subsets);
    return totalCost;
}

int main() {
    int R, C;
    scanf("%d %d", &R, &C);
    
    Edge *edges = (Edge *)malloc(C * sizeof(Edge));
    for (int i = 0; i < C; i++) {
        scanf("%d %d %d", &edges[i].v, &edges[i].w, &edges[i].cost);
    }
    
    int minCost = kruskalMST(R, C, edges);
    printf("%d\n", minCost);
    
    free(edges);
    return 0;
}