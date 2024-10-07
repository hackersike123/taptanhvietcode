#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int top;
} Stack;

void init(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, int value) {
    if (!isFull(s)) {
        s->data[++(s->top)] = value;
    }
}

int pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[(s->top)--];
    }
    return -1;
}

int evaluatePostfix(char *postfix) {
    Stack s;
    init(&s);
    int i = 0, a, b;
    char c;
    while ((c = postfix[i++]) != '\0') {
        if (isdigit(c)) {
            push(&s, c - '0');
        } else {
            b = pop(&s);
            a = pop(&s);
            switch (c) {
                case '+': push(&s, a + b); break;
                case '-': push(&s, a - b); break;
                case '*': push(&s, a * b); break;
                case '/': push(&s, a / b); break;
            }
        }
    }
    return pop(&s);
}

int main() {
    char postfix[] = "46*2/31-42*+-63/-5+";
    printf("Result: %d\n", evaluatePostfix(postfix));
    return 0;
}
