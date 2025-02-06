/* Flavia Fernandes dos Santos, RA 170563
* Este programa lê o mapa de um país com suas cidades, estradas e pedágios, bem como uma rota pré-definida e uma cidade de parada.
*Então calcula qual caminho oferece o menor custo, em termos de pedágio, para chegar ao destino após desviar da rota original.*/

#include <stdio.h>
#include <limits.h>

#define MAXN 250
#define INF INT_MAX


typedef struct {
    int dest, cost;
} Edge;

typedef struct {
    Edge edges[MAXN];
    int size;
} AdjList;

AdjList graph[MAXN];
int dist[MAXN][2]; // 0: fora da rota, 1: dentro da rota

void dijkstra(int N, int C, int K) {
    int visited[MAXN][2] = {0};
    for (int i = 0; i < N; i++) {
        dist[i][0] = dist[i][1] = INF;
    }
    dist[K][0] = 0;

    for (int i = 0; i < 2 * N; i++) {
        int minDist = INF, u = -1, state = -1;

        for (int j = 0; j < N; j++) {
            for (int s = 0; s < 2; s++) {
                if (!visited[j][s] && dist[j][s] < minDist) {
                    minDist = dist[j][s];
                    u = j;
                    state = s;
                }
            }
        }

        if (u == -1) break;
        visited[u][state] = 1;

        for (int k = 0; k < graph[u].size; k++) {
            int v = graph[u].edges[k].dest;
            int cost = graph[u].edges[k].cost;

            if (state == 0) { // Fora da rota
                if (v < C) {
                    if (dist[v][1] > dist[u][0] + cost) {
                        dist[v][1] = dist[u][0] + cost;
                    }
                } else {
                    if (dist[v][0] > dist[u][0] + cost) {
                        dist[v][0] = dist[u][0] + cost;
                    }
                }
            } else { // Dentro da rota
                if (v == u + 1) {
                    if (dist[v][1] > dist[u][1] + cost) {
                        dist[v][1] = dist[u][1] + cost;
                    }
                }
            }
        }
    }
}

int main() {
    int N, M, C, K;

    while (scanf("%d %d %d %d", &N, &M, &C, &K), N || M || C || K) {
        for (int i = 0; i < N; i++) {
            graph[i].size = 0;
        }

        for (int i = 0; i < M; i++) {
            int U, V, P;
            scanf("%d %d %d", &U, &V, &P);
            graph[U].edges[graph[U].size++] = (Edge){V, P};
            graph[V].edges[graph[V].size++] = (Edge){U, P};
        }

        dijkstra(N, C, K);

        printf("%d\n", dist[C-1][1]);
    }

    return 0;
}