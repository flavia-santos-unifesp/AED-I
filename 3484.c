/* Flavia Fernandes dos Santos, RA 170563
* Este programa organiza as crianças em uma árvore binária por altura e imprime a menor altura em cada nível da árvore.*/

#include <stdio.h>
#include <stdlib.h>

// Estrutura para um nó da árvore binária
typedef struct Node {
    int altura;          // Altura da criança
    struct Node *esquerda; // Ponteiro para o filho da esquerda
    struct Node *direita;  // Ponteiro para o filho da direita
} Node;

// Função para criar um novo nó
Node* criarNo(int altura) {
    Node *novo = (Node*) malloc(sizeof(Node));
    novo->altura = altura;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// Função para inserir uma criança na árvore
Node* inserirNo(Node *raiz, int altura) {
    if (raiz == NULL) {
        return criarNo(altura); // Se a raiz for nula, cria um novo nó
    }
    if (altura < raiz->altura) {
        raiz->esquerda = inserirNo(raiz->esquerda, altura); // Insere na esquerda se for mais baixo
    } else {
        raiz->direita = inserirNo(raiz->direita, altura); // Insere na direita se for mais alto
    }
    return raiz;
}

// Função para encontrar a menor altura em cada nível da árvore
void encontrarMenorPorNivel(Node *raiz, int nivel, int *menores) {
    if (raiz == NULL) return; // Se a raiz for nula, retorna

    // Atualiza a menor altura no nível atual
    if (menores[nivel] == 0 || raiz->altura < menores[nivel]) {
        menores[nivel] = raiz->altura;
    }

    // Recursão para os filhos da esquerda e direita
    encontrarMenorPorNivel(raiz->esquerda, nivel + 1, menores);
    encontrarMenorPorNivel(raiz->direita, nivel + 1, menores);
}

// Função principal
int main() {
    int N;
    scanf("%d", &N); // Lê o número de alunos

    Node *raiz = NULL; // Inicializa a raiz da árvore como nula
    for (int i = 0; i < N; i++) {
        int altura;
        scanf("%d", &altura); // Lê a altura de cada aluno
        raiz = inserirNo(raiz, altura); // Insere o aluno na árvore
    }

    // Array para armazenar a menor altura em cada nível
    int menores[250] = {0}; // Inicializa com 0 (assumindo que alturas são positivas)

    // Encontra a menor altura em cada nível
    encontrarMenorPorNivel(raiz, 0, menores);

    // Imprime a menor altura em cada nível
    for (int i = 0; i < 250; i++) {
        if (menores[i] != 0) {
            printf("%d %d\n", i, menores[i]); // Imprime o nível e a menor altura
        }
    }

    return 0;
}