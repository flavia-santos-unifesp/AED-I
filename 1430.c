/* Flavia Fernandes dos Santos, RA 170563
* Este programa divide uma composição musical em compassos, calcula a duração de cada um e conta quantos têm duração correta.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para um nó da lista encadeada
typedef struct Node {
    char *compasso;       // String representando o compasso
    struct Node *proximo; // Ponteiro para o próximo nó
} Node;

// Função para criar um novo nó
Node* criarNo(char *compasso) {
    Node *novo = (Node*) malloc(sizeof(Node));
    novo->compasso = strdup(compasso); // Copia a string do compasso
    novo->proximo = NULL;
    return novo;
}

// Função para liberar a memória da lista
void liberarLista(Node *head) {
    Node *atual = head;
    while (atual != NULL) {
        Node *temp = atual;
        atual = atual->proximo;
        free(temp->compasso); // Libera a string do compasso
        free(temp);           // Libera o nó
    }
}

// Função para calcular a duração de um compasso
float calcularDuracao(char *compasso) {
    float duracao = 0.0;
    for (int i = 0; compasso[i] != '\0'; i++) {
        switch (compasso[i]) {
            case 'W': duracao += 1.0; break;
            case 'H': duracao += 0.5; break;
            case 'Q': duracao += 0.25; break;
            case 'E': duracao += 0.125; break;
            case 'S': duracao += 0.0625; break;
            case 'T': duracao += 0.03125; break;
            case 'X': duracao += 0.015625; break;
        }
    }
    return duracao;
}

// Função principal
int main() {
    char composicao[201]; // String para armazenar a composição

    while (1) {
        scanf("%s", composicao); // Lê a composição
        if (composicao[0] == '*') break; // Termina o programa se a entrada for '*'

        Node *head = NULL; // Inicializa a lista como vazia
        Node *tail = NULL;

        // Divide a composição em compassos e insere na lista
        char *token = strtok(composicao, "/");
        while (token != NULL) {
            Node *novo = criarNo(token);
            if (head == NULL) {
                head = novo;
                tail = novo;
            } else {
                tail->proximo = novo;
                tail = novo;
            }
            token = strtok(NULL, "/");
        }

        // Conta quantos compassos têm duração correta
        int corretos = 0;
        Node *atual = head;
        while (atual != NULL) {
            float duracao = calcularDuracao(atual->compasso);
            if (duracao == 1.0) {
                corretos++;
            }
            atual = atual->proximo;
        }

        // Imprime o número de compassos corretos
        printf("%d\n", corretos);

        // Libera a memória da lista
        liberarLista(head);
    }

    return 0;
}