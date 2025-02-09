/* Flavia Fernandes dos Santos, RA 170563
* Este programa implementa um grafo e retorna o caminho mínimo necessário para percorrer toas as arestas e retornar ao ponto inicial.*/

#include <stdio.h>
#include <stdlib.h>

// Estrutura para um nó na lista de adjacência
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Estrutura para o Grafo
typedef struct {
    int V, E;    // Número de vértices e arestas
    Node** adj;  // Lista de adjacência
    int* visited; // Vetor de visitados para DFS
} Graph;

// Cria um novo nó na lista de adjacência
Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Inicializa o grafo com um número de vértices
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = vertices;
    graph->E = 0;
    graph->adj = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (int*)calloc(vertices, sizeof(int));

    for (int i = 0; i < vertices; i++)
        graph->adj[i] = NULL;

    return graph;
}

// Adiciona uma aresta não-direcionada no grafo
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adj[src];
    graph->adj[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adj[dest];
    graph->adj[dest] = newNode;

    graph->E++;
}

// Função DFS para contar os movimentos necessários
int dfs(Graph* graph, int node, int parent) {
    int moves = 0;
    graph->visited[node] = 1;
    
    // Percorre os vizinhos
    Node* temp = graph->adj[node];
    while (temp) {
        if (!graph->visited[temp->vertex]) {
            moves += 1 + dfs(graph, temp->vertex, node);
        }
        temp = temp->next;
    }
    
    return moves;
}

// Função para calcular os movimentos mínimos para desenhar o labirinto
int calculateMovements(Graph* graph, int startNode) {
    int moves = dfs(graph, startNode, -1);
    return moves * 2; // Cada aresta precisa ser percorrida duas vezes
}

// Libera a memória do grafo
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->V; i++) {
        Node* temp = graph->adj[i];
        while (temp) {
            Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph->adj);
    free(graph->visited);
    free(graph);
}

// Função principal
int main() {
    int T; // Número de casos de teste
    scanf("%d", &T);

    while (T--) {
        int startNode, V, A;
        scanf("%d", &startNode); // Nodo inicial (e final)
        scanf("%d %d", &V, &A);  // Número de vértices e arestas

        Graph* graph = createGraph(V);

        // Lendo as conexões entre os vértices
        for (int i = 0; i < A; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            addEdge(graph, u, v);
        }

        // Calculando e imprimindo a quantidade mínima de movimentos
        printf("%d\n", calculateMovements(graph, startNode));

        // Liberando a memória do grafo
        freeGraph(graph);
    }

    return 0;
}