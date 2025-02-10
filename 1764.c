/* Flavia Fernandes dos Santos, RA 170563
* Este programa lê as rotas entre as cidades, utiliza o algoritmo de Kruskal para encontrar a MST que conecta todas as cidades com
* o menor custo total e imprime a soma das distâncias */

#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura para representar uma aresta
typedef struct Aresta {
    int origem, destino, peso;
} Aresta;

// Definição da estrutura para representar um nó na lista encadeada
typedef struct No {
    Aresta aresta;
    struct No *prox;
} No;

// Função para criar um novo nó na lista encadeada
No* criarNo(Aresta aresta) {
    No *novo = (No *)malloc(sizeof(No));
    novo->aresta = aresta;
    novo->prox = NULL;
    return novo;
}

// Função para adicionar uma aresta à lista encadeada
void adicionarAresta(No **inicio, Aresta aresta) {
    No *novo = criarNo(aresta);
    novo->prox = *inicio;
    *inicio = novo;
}

// Função para encontrar o conjunto de um elemento (Union-Find)
int encontrar(int *parent, int i) {
    if (parent[i] == i)
        return i;
    return encontrar(parent, parent[i]);
}

// Função para unir dois conjuntos (Union-Find)
void unir(int *parent, int *rank, int x, int y) {
    int xroot = encontrar(parent, x);
    int yroot = encontrar(parent, y);

    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

// Função para comparar duas arestas pelo peso (usada no qsort)
int compararArestas(const void *a, const void *b) {
    Aresta *arestaA = (Aresta *)a;
    Aresta *arestaB = (Aresta *)b;
    return arestaA->peso - arestaB->peso;
}

// Função principal para calcular a Árvore Geradora Mínima (MST)
int kruskal(No *inicio, int M, int N) {
    Aresta *arestas = (Aresta *)malloc(N * sizeof(Aresta));
    int *parent = (int *)malloc(M * sizeof(int));
    int *rank = (int *)malloc(M * sizeof(int));

    // Inicializa as arestas
    No *atual = inicio;
    for (int i = 0; i < N; i++) {
        arestas[i] = atual->aresta;
        atual = atual->prox;
    }

    // Ordena as arestas pelo peso
    qsort(arestas, N, sizeof(Aresta), compararArestas);

    // Inicializa os conjuntos disjuntos
    for (int i = 0; i < M; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int soma = 0;
    int arestasSelecionadas = 0;

    // Itera sobre as arestas ordenadas
    for (int i = 0; i < N && arestasSelecionadas < M - 1; i++) {
        int x = encontrar(parent, arestas[i].origem);
        int y = encontrar(parent, arestas[i].destino);

        // Se não formar ciclo, adiciona a aresta à MST
        if (x != y) {
            soma += arestas[i].peso;
            unir(parent, rank, x, y);
            arestasSelecionadas++;
        }
    }

    // Libera a memória alocada
    free(arestas);
    free(parent);
    free(rank);

    return soma;
}

int main() {
    int M, N;
    while (scanf("%d %d", &M, &N) && (M != 0 || N != 0)) {
        No *inicio = NULL;

        // Lê as arestas e adiciona à lista encadeada
        for (int i = 0; i < N; i++) {
            Aresta aresta;
            scanf("%d %d %d", &aresta.origem, &aresta.destino, &aresta.peso);
            adicionarAresta(&inicio, aresta);
        }

        // Calcula a soma das distâncias da MST
        int soma = kruskal(inicio, M, N);

        // Imprime o resultado
        printf("%d\n", soma);

        // Libera a memória alocada para a lista encadeada
        No *atual = inicio;
        while (atual != NULL) {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }

    return 0;
}