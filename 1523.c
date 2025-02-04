/* Flavia Fernandes dos Santos, RA 170563
* Este programa lê uma sequência de pares de números que representam a quantidade de carros e quantidades de
* vagas no estacionaamento, bem como seus horários de entrada e saída, e retorna se será possível ou não que todos estacionem.*/

#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó da pilha (representando o estacionamento)
typedef struct Node {
    int exitTime;
    struct Node *next;
} Node;

// Estrutura da pilha
typedef struct {
    Node *top;
    int size;
    int capacity;
} Stack;

// Inicializa a pilha
void initStack(Stack *s, int capacity) {
    s->top = NULL;
    s->size = 0;
    s->capacity = capacity;
}

// Verifica se a pilha está vazia
int isEmpty(Stack *s) {
    return s->size == 0;
}

// Verifica se a pilha está cheia
int isFull(Stack *s) {
    return s->size == s->capacity;
}

// Empilha um novo horário de saída
void push(Stack *s, int exitTime) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        exit(1);
    }
    newNode->exitTime = exitTime;
    newNode->next = s->top;
    s->top = newNode;
    s->size++;
}

// Desempilha um carro
void pop(Stack *s) {
    if (!isEmpty(s)) {
        Node *temp = s->top;
        s->top = s->top->next;
        free(temp);
        s->size--;
    }
}

// Obtém o horário de saída do carro no topo da pilha
int peek(Stack *s) {
    if (!isEmpty(s)) {
        return s->top->exitTime;
    }
    return -1;
}

// Libera a memória da pilha
void clearStack(Stack *s) {
    while (!isEmpty(s)) {
        pop(s);
    }
}

int main() {
    int N, K;
    while (scanf("%d %d", &N, &K), N || K) {
        Stack parking;
        initStack(&parking, K);
        int possible = 1;

        for (int i = 0; i < N; i++) {
            int arrival, departure;
            scanf("%d %d", &arrival, &departure);

            // Remove os carros que já deveriam ter saído
            while (!isEmpty(&parking) && peek(&parking) <= arrival) {
                pop(&parking);
            }

            // Se o estacionamento estiver cheio, não é possível estacionar
            if (isFull(&parking)) {
                possible = 0;
            } else {
                // Garante que os horários de saída estão em ordem não crescente
                if (!isEmpty(&parking) && peek(&parking) < departure) {
                    possible = 0;
                }
                push(&parking, departure);
            }
        }

        printf("%s\n", possible ? "Sim" : "Nao");
        clearStack(&parking);
    }
    return 0;
}
