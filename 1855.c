/* Flavia Fernandes dos Santos, RA 170563
* Este programa lê uma matriz que representa um mapa do tesouro e verifica se o mapa é válido ou não.*/

#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um nó do mapa
typedef struct Node {
    char symbol;
    int visited;
    struct Node *right;
    struct Node *left;
    struct Node *up;
    struct Node *down;
} Node;

// Função para criar um novo nó
Node* createNode(char symbol) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->symbol = symbol;
    newNode->visited = 0;
    newNode->right = NULL;
    newNode->left = NULL;
    newNode->up = NULL;
    newNode->down = NULL;
    return newNode;
}

// Função para percorrer o mapa
char traverseMap(Node* start) {
    Node* current = start;
    char lastDirection = '>'; // Inicia com a direção padrão para a direita

    while (1) {
        if (current == NULL || current->visited) {
            return '!'; // Mapa inválido (saiu do mapa ou entrou em loop)
        }
        if (current->symbol == '*') {
            return '*'; // Mapa válido (encontrou o baú)
        }

        current->visited = 1; // Marca o nó como visitado

        // Atualiza a última direção se o símbolo atual for uma flecha
        if (current->symbol == '>' || current->symbol == '<' || 
            current->symbol == 'v' || current->symbol == '^') {
            lastDirection = current->symbol;
        }

        // Decide para onde mover com base na última direção ou no símbolo atual
        switch (current->symbol == '.' ? lastDirection : current->symbol) {
            case '>':
                current = current->right;
                break;
            case '<':
                current = current->left;
                break;
            case 'v':
                current = current->down;
                break;
            case '^':
                current = current->up;
                break;
            default:
                return '!'; // Símbolo inválido
        }
    }
}

int main() {
    int x, y;
    scanf("%d", &x); // Lê a largura do mapa
    scanf("%d", &y); // Lê a altura do mapa

    // Cria uma matriz de nós para representar o mapa
    Node* map[y][x];
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            char symbol;
            scanf(" %c", &symbol); // Lê o símbolo do mapa
            map[i][j] = createNode(symbol);
        }
    }

    // Conecta os nós do mapa
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (j < x - 1) map[i][j]->right = map[i][j + 1];
            if (j > 0) map[i][j]->left = map[i][j - 1];
            if (i < y - 1) map[i][j]->down = map[i + 1][j];
            if (i > 0) map[i][j]->up = map[i - 1][j];
        }
    }

    // Percorre o mapa a partir do ponto inicial (0, 0)
    char result = traverseMap(map[0][0]);

    // Imprime o resultado
    printf("%c\n", result);

    // Libera a memória alocada
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            free(map[i][j]);
        }
    }

    return 0;
}