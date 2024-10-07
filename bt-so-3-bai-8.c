#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int data[100];
    int top;
} Stack;

void init(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, int value) {
    s->data[++(s->top)] = value;
}

int pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[(s->top)--];
    }
    return -1;
}

void moveDisk(char fromPeg, char toPeg, int disk) {
    printf("Move disk %d from %c to %c\n", disk, fromPeg, toPeg);
}

void hanoiIterative(int n, char fromPeg, char toPeg, char auxPeg) {
    Stack s;
    init(&s);
    int totalMoves = (1 << n) - 1; // 2^n - 1
    for (int i = n; i >= 1; i--) {
        push(&s, i);
    }
    for (int i = 1; i <= totalMoves; i++) {
        int disk = pop(&s);
        if (i % 3 == 1) {
            moveDisk(fromPeg, toPeg, disk);
        } else if (i % 3 == 2) {
            moveDisk(fromPeg, auxPeg, disk);
        } else if (i % 3 == 0) {
            moveDisk(auxPeg, toPeg, disk);
        }
        push(&s, disk - 1);
    }
}

int main() {
    int n = 3; // Number of disks
    hanoiIterative(n, 'A', 'C', 'B');
    return 0;
}
