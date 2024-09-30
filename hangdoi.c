#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int items[MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

int isFull(Queue *q) {
    return q->rear == MAX - 1;
}

void enqueue(Queue *q, int item) {
    if (isFull(q)) {
        printf("Queue overflow\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->items[++(q->rear)] = item;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue underflow\n");
        return -1;
    }
    int item = q->items[q->front];
    if (q->front >= q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return item;
}

int peek(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    return q->items[q->front];
}

int size(Queue *q) {
    if (isEmpty(q)) {
        return 0;
    }
    return q->rear - q->front + 1;
}

int main() {
    Queue q;
    initQueue(&q);
    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);
    printf("Dequeued: %d\n", dequeue(&q));  // Output: 1
    printf("Peek: %d\n", peek(&q));         // Output: 2
    printf("Size: %d\n", size(&q));         // Output: 2
    return 0;
}
