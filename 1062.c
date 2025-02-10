/* Flavia Fernandes dos Santos, RA 170563
* Este programa utiliza uma pilha para simular a reorganização dos vagões e verifica se é possível obter a permutação desejada na saída.*/

#include <stdio.h>
#include <stdlib.h>

// Estrutura para um nó da pilha
typedef struct Node {
    int valor;           // Valor do vagão
    struct Node *proximo; // Ponteiro para o próximo nó
} Node;

// Função para criar um novo nó
Node* criarNo(int valor) {
    Node *novo = (Node*) malloc(sizeof(Node));
    novo->valor = valor;
    novo->proximo = NULL;
    return novo;
}

// Função para empilhar (push)
void push(Node **topo, int valor) {
    Node *novo = criarNo(valor);
    novo->proximo = *topo;
    *topo = novo;
}

// Função para desempilhar (pop)
int pop(Node **topo) {
    if (*topo == NULL) return -1; // Pilha vazia
    Node *temp = *topo;
    int valor = temp->valor;
    *topo = (*topo)->proximo;
    free(temp);
    return valor;
}

// Função para verificar se a permutação é possível
int verificarPermutacao(int N, int sequencia[]) {
    Node *pilha = NULL; // Pilha para simular a estação
    int esperado = 1;   // Próximo vagão esperado na saída B

    for (int i = 0; i < N; i++) {
        // Empilha os vagões até encontrar o vagão esperado
        while (esperado <= N && (pilha == NULL || pilha->valor != sequencia[i])) {
            push(&pilha, esperado);
            esperado++;
        }

        // Se o topo da pilha for o vagão esperado, desempilha
        if (pilha != NULL && pilha->valor == sequencia[i]) {
            pop(&pilha);
        } else {
            return 0; // Não é possível obter a permutação
        }
    }

    return 1; // Permutação possível
}

// Função principal
int main() {
    int N;
    while (1) {
        scanf("%d", &N); // Lê o número de vagões
        if (N == 0) break; // Termina o programa se N = 0

        while (1) {
            int sequencia[1000]; // Armazena a permutação desejada
            scanf("%d", &sequencia[0]);
            if (sequencia[0] == 0) break; // Fim do bloco de permutações

            for (int i = 1; i < N; i++) {
                scanf("%d", &sequencia[i]);
            }

            // Verifica se a permutação é possível
            if (verificarPermutacao(N, sequencia)) {
                printf("Yes\n");
            } else {
                printf("No\n");
            }
        }
        printf("\n"); // Linha em branco após cada bloco
    }

    return 0;
}