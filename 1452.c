/* Flavia Fernandes dos Santos, RA 170563
* Este programa lê as aplicações fornecidas por cada servidor e as requisitadas por cada cliente, verifica quais servidores atendem a
* pelo menos uma aplicação requisitada por cada cliente e conta o número total de conexões únicas entre clientes e servidores.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura para armazenar uma aplicação
typedef struct Aplicacao {
    char nome[21]; // Nome da aplicação (máximo 20 caracteres + '\0')
    struct Aplicacao *prox; // Ponteiro para a próxima aplicação na lista
} Aplicacao;

// Função para criar um novo nó (aplicação) na lista
Aplicacao* criarAplicacao(const char *nome) {
    Aplicacao *novo = (Aplicacao *)malloc(sizeof(Aplicacao));
    strcpy(novo->nome, nome);
    novo->prox = NULL;
    return novo;
}

// Função para inserir uma aplicação na lista
void inserirAplicacao(Aplicacao **inicio, const char *nome) {
    Aplicacao *novo = criarAplicacao(nome);
    if (*inicio == NULL) {
        *inicio = novo;
    } else {
        Aplicacao *atual = *inicio;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }
}

// Função para verificar se uma aplicação está na lista
int contemAplicacao(Aplicacao *inicio, const char *nome) {
    Aplicacao *atual = inicio;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            return 1; // A aplicação está na lista
        }
        atual = atual->prox;
    }
    return 0; // A aplicação não está na lista
}

// Função para liberar a memória alocada para a lista de aplicações
void liberarAplicacoes(Aplicacao *inicio) {
    Aplicacao *atual = inicio;
    while (atual != NULL) {
        Aplicacao *temp = atual;
        atual = atual->prox;
        free(temp);
    }
}

int main() {
    int N, M;
    while (scanf("%d %d", &N, &M) && (N != 0 || M != 0)) { // Lê N e M até ambos serem 0
        Aplicacao *servidores[N]; // Lista de aplicações fornecidas por cada servidor
        for (int i = 0; i < N; i++) {
            servidores[i] = NULL;
            int Qi;
            scanf("%d", &Qi);
            for (int j = 0; j < Qi; j++) {
                char app[21];
                scanf("%s", app);
                inserirAplicacao(&servidores[i], app);
            }
        }

        int totalConexoes = 0;

        for (int j = 0; j < M; j++) {
            int Pj;
            scanf("%d", &Pj);
            Aplicacao *requisitadas = NULL; // Lista de aplicações requisitadas pelo cliente
            for (int k = 0; k < Pj; k++) {
                char app[21];
                scanf("%s", app);
                inserirAplicacao(&requisitadas, app);
            }

            // Verifica quais servidores atendem às aplicações requisitadas
            for (int i = 0; i < N; i++) {
                Aplicacao *atual = requisitadas;
                int conectado = 0;
                while (atual != NULL) {
                    if (contemAplicacao(servidores[i], atual->nome)) {
                        conectado = 1;
                        break; // O servidor atende a pelo menos uma aplicação requisitada
                    }
                    atual = atual->prox;
                }
                if (conectado) {
                    totalConexoes++;
                }
            }

            liberarAplicacoes(requisitadas); // Libera a lista de aplicações requisitadas
        }

        printf("%d\n", totalConexoes);

        // Libera a memória alocada para as listas de aplicações dos servidores
        for (int i = 0; i < N; i++) {
            liberarAplicacoes(servidores[i]);
        }
    }

    return 0;
}