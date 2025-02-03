/* Flavia Fernandes dos Santos, RA 170563
* Este programa lê uma string com os caracteres < . > e retorna quantos diamantes podem ser formados ao fechar um <>.*/

#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó para a pilha
struct Node {
    char data;
    struct Node* next;
};

// Estrutura da pilha
struct Stack {
    int size;
    struct Node* top;
};

// Função para empilhar um elemento na pilha
void push(struct Stack* stack, char data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

// Função para remover um elemento do topo da pilha
void pop(struct Stack* stack) {
    if (stack->size > 0) {
        struct Node* temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
        stack->size--;
    }
}

// Função para contar a quantidade de diamantes extraídos de uma expressão
int countDiamonds(const char* expression) {
    struct Stack stack = {0, NULL}; // Inicializa a pilha
    int count = 0; // Contador de diamantes
    
    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == '<') {
            push(&stack, '<'); // Empilha '<'
        } else if (expression[i] == '>' && stack.size > 0) {
            pop(&stack); // Remove um '<' correspondente
            count++; // Conta um diamante extraído
        }
    }
    
    // Libera qualquer elemento restante na pilha
    while (stack.size > 0) {
        pop(&stack);
    }
    
    return count;
}

int main() {
    int N;
    scanf("%d", &N); // Lê o número de casos de teste
    
    while (N--) {
        char expression[1001];
        scanf("%s", expression); // Lê a expressão
        
        printf("%d\n", countDiamonds(expression)); // Imprime a quantidade de diamantes extraídos
    }
    
    return 0;
}
