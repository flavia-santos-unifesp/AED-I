/* Flavia Fernandes dos Santos, RA 170563
* Este programa lê uma sequência de operações e retorna a estrutura de dados utilizada.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

// Estrutura de nó para lista encadeada
typedef struct Node {
    int value;
    struct Node *next;
} Node;

// Estrutura para pilha
typedef struct {
    Node *top;
} Stack;

void initStack(Stack *s) {
    s->top = NULL;
}

void push(Stack *s, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = s->top;
    s->top = newNode;
}

int pop(Stack *s) {
    if (!s->top) return -1;
    Node *temp = s->top;
    int value = temp->value;
    s->top = s->top->next;
    free(temp);
    return value;
}

// Estrutura para fila
typedef struct {
    Node *front, *rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = NULL;
}

void enqueue(Queue *q, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    if (!q->rear) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

int dequeue(Queue *q) {
    if (!q->front) return -1;
    Node *temp = q->front;
    int value = temp->value;
    q->front = q->front->next;
    if (!q->front) q->rear = NULL;
    free(temp);
    return value;
}

// Estrutura para fila de prioridade
typedef struct {
    int data[MAX_SIZE];
    int size;
} PriorityQueue;

void initPriorityQueue(PriorityQueue *pq) {
    pq->size = 0;
}

void pushPriorityQueue(PriorityQueue *pq, int value) {
    pq->data[pq->size++] = value;
}

int popPriorityQueue(PriorityQueue *pq) {
    if (pq->size == 0) return -1;
    int maxIndex = 0;
    for (int i = 1; i < pq->size; i++) {
        if (pq->data[i] > pq->data[maxIndex]) {
            maxIndex = i;
        }
    }
    int value = pq->data[maxIndex];
    pq->data[maxIndex] = pq->data[--pq->size];
    return value;
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        Stack stack;
        Queue queue;
        PriorityQueue pqueue;
        
        initStack(&stack);
        initQueue(&queue);
        initPriorityQueue(&pqueue);
        
        int isStack = 1, isQueue = 1, isPQueue = 1;
        
        for (int i = 0; i < n; i++) {
            int op, x;
            scanf("%d %d", &op, &x);
            
            if (op == 1) {
                push(&stack, x);
                enqueue(&queue, x);
                pushPriorityQueue(&pqueue, x);
            } else {
                if (isStack && pop(&stack) != x) isStack = 0;
                if (isQueue && dequeue(&queue) != x) isQueue = 0;
                if (isPQueue && popPriorityQueue(&pqueue) != x) isPQueue = 0;
            }
        }
        
        if (isStack + isQueue + isPQueue > 1) {
            printf("not sure\n");
        } else if (isStack) {
            printf("stack\n");
        } else if (isQueue) {
            printf("queue\n");
        } else if (isPQueue) {
            printf("priority queue\n");
        } else {
            printf("impossible\n");
        }
    }
    return 0;
}
