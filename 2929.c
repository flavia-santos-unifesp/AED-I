/* Flavia Fernandes dos Santos, RA 170563
* Este programa lê a quantidade de operações (Push/Pop/Min) que serão lidas referente à pilha de presentes do Papi Noel.
* Cada função Push vem com um inteiro que representa o grau de diversão do presente, e a cada função Pop um presente é retirado da pilha.
* A cada comando Min o programa lê e retorna o valor presente com o menor grau da pilha no momento da consulta.*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

// Estrutura para um nó da pilha
typedef struct Node {
    int value;         // Valor do presente
    int min_value;     // Menor valor da pilha até este nó
    struct Node* next; // Ponteiro para o próximo nó
} Node;

// Estrutura para a pilha
typedef struct {
    Node* top; // Ponteiro para o topo da pilha
} Stack;

// Inicializa a pilha
void initStack(Stack* stack) {
    stack->top = NULL;
}

// Insere um novo presente na pilha
void push(Stack* stack, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Erro de alocação de memória\n");
        return;
    }
    newNode->value = value;
    newNode->next = stack->top;
    // O menor valor até agora é o mínimo entre o novo valor e o menor valor do nó anterior
    newNode->min_value = (stack->top == NULL) ? value : (value < stack->top->min_value ? value : stack->top->min_value);
    stack->top = newNode;
}

// Remove um presente do topo da pilha
void pop(Stack* stack) {
    if (stack->top == NULL) {
        printf("EMPTY\n");
        return;
    }
    Node* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
}

// Retorna o menor valor da pilha
void getMin(Stack* stack) {
    if (stack->top == NULL) {
        printf("EMPTY\n");
    } else {
        printf("%d\n", stack->top->min_value);
    }
}

int main() {
    int N;
    scanf("%d", &N);
    
    Stack stack;
    initStack(&stack);
    
    char operation[10];
    int value;
    
    for (int i = 0; i < N; i++) {
        scanf("%s", operation);
        if (strcmp(operation, "PUSH") == 0) {
            scanf("%d", &value);
            push(&stack, value);
        } else if (strcmp(operation, "POP") == 0) {
            pop(&stack);
        } else if (strcmp(operation, "MIN") == 0) {
            getMin(&stack);
        }
    }
    
    return 0;
}
