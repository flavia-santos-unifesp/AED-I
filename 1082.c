/* Flavia Fernandes dos Santos, RA 170563
* Este programa lê um grafo, e usando a busca em profundidade, identifica e imprime os vértices em ordem alfabética, além
* de indicar a quantidade de componentes conexos.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 26

// Estrutura para representar um nó da lista encadeada
typedef struct Node {
    char vertex;
    struct Node* next;
} Node;

// Estrutura para representar um grafo
typedef struct {
    Node* adjList[MAX_VERTICES];
    int visited[MAX_VERTICES];
} Graph;

// Função para inicializar o grafo
void initGraph(Graph* graph, int vertices) {
    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }
}

// Função para adicionar uma aresta ao grafo
void addEdge(Graph* graph, char src, char dest) {
    int srcIndex = src - 'a';
    int destIndex = dest - 'a';
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = graph->adjList[srcIndex];
    graph->adjList[srcIndex] = newNode;
    
    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = src;
    newNode->next = graph->adjList[destIndex];
    graph->adjList[destIndex] = newNode;
}

// Função recursiva para realizar busca em profundidade (DFS)
void dfs(Graph* graph, int v, char* component, int* index) {
    graph->visited[v] = 1;
    component[(*index)++] = v + 'a';
    
    Node* temp = graph->adjList[v];
    while (temp) {
        int adjVertex = temp->vertex - 'a';
        if (!graph->visited[adjVertex]) {
            dfs(graph, adjVertex, component, index);
        }
        temp = temp->next;
    }
}

// Função para comparar caracteres (para ordenar os componentes)
int compareChars(const void* a, const void* b) {
    return (*(char*)a - *(char*)b);
}

int main() {
    int testCases;
    scanf("%d", &testCases);
    
    for (int t = 1; t <= testCases; t++) {
        int vertices, edges;
        scanf("%d %d", &vertices, &edges);
        
        Graph graph;
        initGraph(&graph, vertices);
        
        for (int i = 0; i < edges; i++) {
            char v1, v2;
            scanf(" %c %c", &v1, &v2);
            addEdge(&graph, v1, v2);
        }
        
        printf("Case #%d:\n", t);
        int components = 0;
        
        for (int i = 0; i < vertices; i++) {
            if (!graph.visited[i]) {
                char component[MAX_VERTICES];
                int index = 0;
                dfs(&graph, i, component, &index);
                
                // Ordena os vértices do componente
                qsort(component, index, sizeof(char), compareChars);
                
                // Imprime o componente conexo
                for (int j = 0; j < index; j++) {
                    printf("%c%s", component[j], j < index - 1 ? "," : "");
                }
                printf(",\n");
                components++;
            }
        }
        
        printf("%d connected components\n\n", components);
    }
    
    return 0;
}
