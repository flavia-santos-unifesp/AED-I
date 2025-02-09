/* Flavia Fernandes dos Santos, RA 170563
* Este programa implementa uma tabela Hash com tratamento de colisões, armazena e exibe as chaves na ordem em que foram inseridas.*/

#include <stdio.h>
#include <stdlib.h>

// Estrutura para um nó da lista encadeada
typedef struct Node {
    int key;              // Valor da chave
    struct Node* next;    // Ponteiro para o próximo nó
} Node;

// Função para criar um novo nó
Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

// Função para inserir uma chave na tabela hash usando encadeamento exterior (inserção no final)
void insertKey(Node** hashTable, int M, int key) {
    int index = key % M; // Calcula o índice usando a função de dispersão
    Node* newNode = createNode(key);

    if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
    } else {
        // Percorre a lista até o final para inserir no último nó
        Node* current = hashTable[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Função para imprimir a tabela hash
void printHashTable(Node** hashTable, int M) {
    for (int i = 0; i < M; i++) {
        printf("%d ->", i);
        Node* current = hashTable[i];
        while (current != NULL) {
            printf(" %d ->", current->key);
            current = current->next;
        }
        printf(" \\\n"); // Indica o fim da lista
    }
}

int main() {
    int N; // Número de casos de teste
    scanf("%d", &N);

    while (N--) {
        int M, C; // M: número de endereços-base, C: número de chaves
        scanf("%d %d", &M, &C);

        // Aloca a tabela hash (um array de ponteiros para nós)
        Node** hashTable = (Node**)calloc(M, sizeof(Node*));

        // Lê as chaves e insere na tabela hash
        for (int i = 0; i < C; i++) {
            int key;
            scanf("%d", &key);
            insertKey(hashTable, M, key);
        }

        // Imprime a tabela hash
        printHashTable(hashTable, M);

        // Libera a memória alocada para a tabela hash
        for (int i = 0; i < M; i++) {
            Node* current = hashTable[i];
            while (current != NULL) {
                Node* temp = current;
                current = current->next;
                free(temp);
            }
        }
        free(hashTable);

        // Imprime uma linha em branco entre casos de teste, exceto após o último
        if (N > 0) {
            printf("\n");
        }
    }

    return 0;
}