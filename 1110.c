/* Flavia Fernandes dos Santos, RA 170563
* Este programa lê n pilhas de cartas, descarta a carta do topo, move a próxima para a base e retorna quais cartas foram
* descartadas e qual foi a carta remanescente.*/

#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um nó da fila
typedef struct Node {
    int value;
    struct Node *next;
} Node;

// Estrutura para representar a fila
typedef struct Queue {
    Node *front, *rear;
} Queue;

// Inicializa a fila
void initQueue(Queue *q) {
    q->front = q->rear = NULL;
}

// Verifica se a fila está vazia
int isEmpty(Queue *q) {
    return q->front == NULL;
}

// Adiciona um elemento ao final da fila
void enqueue(Queue *q, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    if (isEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Remove um elemento do início da fila e retorna seu valor
int dequeue(Queue *q) {
    if (isEmpty(q)) return -1;
    Node *temp = q->front;
    int value = temp->value;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return value;
}

// Processa as cartas de acordo com o problema
void processCards(int n) {
    if (n == 1) {
        printf("Discarded cards:\nRemaining card: 1\n");
        return;
    }

    Queue q;
    initQueue(&q);

    // Preenche a fila com as cartas de 1 a n
    for (int i = 1; i <= n; i++) {
        enqueue(&q, i);
    }

    printf("Discarded cards: ");
    int first = 1;
    while (q.front != q.rear) {
        if (!first) printf(", ");
        int discarded = dequeue(&q); // Descarta a carta do topo
        printf("%d", discarded);
        int move = dequeue(&q); // Move a próxima carta para a base da fila
        enqueue(&q, move);
        first = 0;
    }
    printf("\nRemaining card: %d\n", q.front->value); // Exibe a carta restante
}

int main() {
    int n;
    // Lê a entrada até encontrar 0
    while (scanf("%d", &n) && n != 0) {
        processCards(n);
    }
    return 0;
}
