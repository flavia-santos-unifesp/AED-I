/* Flavia Fernandes dos Santos, RA 170563
* Este programa lê uma expressão na forma infixa e retorna a mesma expressão na forma posfixa.*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 1000

// Estrutura da pilha
typedef struct {
    char data[MAX_SIZE];
    int top;
} Stack;

// Função para inicializar a pilha
void initialize(Stack *s) {
    s->top = -1;
}

// Função para verificar se a pilha está vazia
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Função para verificar se a pilha está cheia
int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

// Função para empilhar um elemento
void push(Stack *s, char value) {
    if (isFull(s)) {
        printf("Stack Overflow\n");
        exit(1);
    }
    s->data[++(s->top)] = value;
}

// Função para desempilhar um elemento
char pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return s->data[(s->top)--];
}

// Função para retornar o elemento no topo da pilha
char peek(Stack *s) {
    if (isEmpty(s)) {
        return '\0';
    }
    return s->data[s->top];
}

// Função para verificar a precedência dos operadores
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

// Função para converter expressão infixa para posfixa
void infixToPostfix(char *infix, char *postfix) {
    Stack s;
    initialize(&s);
    int i, j = 0;

    for (i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isalnum(ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            push(&s, ch);
        } else if (ch == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[j++] = pop(&s);
            }
            pop(&s); // Remove '(' da pilha
        } else {
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(ch)) {
                postfix[j++] = pop(&s);
            }
            push(&s, ch);
        }
    }

    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s);
    }

    postfix[j] = '\0';
}

int main() {
    int N;
    scanf("%d", &N);
    getchar(); // Consumir a quebra de linha após o número de casos de teste

    for (int i = 0; i < N; i++) {
        char infix[MAX_SIZE];
        char postfix[MAX_SIZE];

        fgets(infix, MAX_SIZE, stdin);
        infix[strcspn(infix, "\n")] = '\0'; // Remover a quebra de linha da entrada

        infixToPostfix(infix, postfix);
        printf("%s\n", postfix);
    }

    return 0;
}