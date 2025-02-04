/* Flavia Fernandes dos Santos, RA 170563
* Este programa lê uma fila de alunos, a ordena em função da nota dos alunos e retorna o número de alunos que não
* precisou trocar de lugar na fila.*/

#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um aluno na lista encadeada
typedef struct Node {
    int nota;
    struct Node *next;
} Node;

// Função para inserir um aluno no final da lista
void inserir(Node **head, int nota) {
    Node *novo = (Node *)malloc(sizeof(Node));
    novo->nota = nota;
    novo->next = NULL;
    
    if (*head == NULL) {
        *head = novo;
    } else {
        Node *temp = *head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = novo;
    }
}

// Função para criar uma cópia da lista encadeada
Node *copiarLista(Node *head) {
    if (!head) return NULL;
    Node *novaLista = NULL, *ultimo = NULL;
    while (head) {
        Node *novo = (Node *)malloc(sizeof(Node));
        novo->nota = head->nota;
        novo->next = NULL;
        if (!novaLista) {
            novaLista = novo;
            ultimo = novo;
        } else {
            ultimo->next = novo;
            ultimo = novo;
        }
        head = head->next;
    }
    return novaLista;
}

// Função para ordenar a lista em ordem decrescente
Node *ordenarLista(Node *head) {
    if (!head || !head->next) return head;
    Node *sorted = NULL;
    while (head) {
        Node *current = head;
        head = head->next;
        if (!sorted || current->nota > sorted->nota) {
            current->next = sorted;
            sorted = current;
        } else {
            Node *temp = sorted;
            while (temp->next && temp->next->nota >= current->nota) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }
    return sorted;
}

// Função para contar os alunos que permaneceram na mesma posição
int contarNaoTrocados(Node *original, Node *ordenado) {
    int count = 0;
    while (original && ordenado) {
        if (original->nota == ordenado->nota) {
            count++;
        }
        original = original->next;
        ordenado = ordenado->next;
    }
    return count;
}

// Função para liberar a memória da lista encadeada
void liberarLista(Node *head) {
    Node *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    int N;
    scanf("%d", &N);
    while (N--) {
        int M;
        scanf("%d", &M);
        Node *original = NULL;
        for (int i = 0; i < M; i++) {
            int nota;
            scanf("%d", &nota);
            inserir(&original, nota);
        }
        Node *copia = copiarLista(original);
        Node *ordenado = ordenarLista(copia);
        printf("%d\n", contarNaoTrocados(original, ordenado));
        liberarLista(original);
        liberarLista(ordenado);
    }
    return 0;
}
