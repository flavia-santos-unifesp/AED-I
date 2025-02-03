/* Flavia Fernandes dos Santos, RA 170563
* Este programa lê uma operação matemática com parentêses e informa se a quantidade de parentêses está correta ou não.*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct Node{
    char data;
    struct Node* next;
};

struct stack{
    int tam;
    struct Node* top;
};

void push(struct stack* p, int data){
    p->tam += 1;
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->next = p->top;
    p->top = newNode;
}

void pop(struct stack* p){
    if(p->tam > 0){
        p->tam -= 1;
        struct Node* oldNode = p->top;
        p->top = p->top->next;
        free(oldNode);
    }
}

char top(struct stack* p){
    return p->top->data;
}

int size(struct stack* p){
    return p->tam;
}

int empty(struct stack* p){
    return p->tam == 0;
}

void init(struct stack* p){
    p->tam = 0;
    p->top = NULL;
}

void release(struct stack* p){
    while(!empty(p)){
        pop(p);
    }
}

int main(){
    int i, tam;
    struct stack p;
    char expression[1001];

    while(scanf("%s\n", &expression) != EOF){
        init(&p);
        tam = strlen(expression);

        for(i = 0; i < tam; ++i){
            if(expression[i] == '('){
                push(&p, '(');
            }else if(expression[i] == ')'){
                if(empty(&p))   break;
                else            pop(&p);
            }
        }

        if(i == tam && empty(&p))   printf("correct\n");
        else                        printf("incorrect\n");

        release(&p);
    }

    return 0;
}