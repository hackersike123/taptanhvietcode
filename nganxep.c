#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int items[MAX];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, int item) {
    if (isFull(s)) {
        printf("Stack overflow\n");
        return;
    }
    s->items[++(s->top)] = item;
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        return -1;
    }
    return s->items[(s->top)--];
}

int peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return -1;
    }
    return s->items[s->top];
}

int size(Stack *s) {
    return s->top + 1;
}

int main() {
    Stack s;
    initStack(&s);
    push(&s, 1);
    push(&s, 2);
    push(&s, 3);
    printf("Popped: %d\n", pop(&s));  // Output: 3
    printf("Peek: %d\n", peek(&s));   // Output: 2
    printf("Size: %d\n", size(&s));   // Output: 2
    return 0;
}
