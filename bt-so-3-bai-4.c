#include <stdio.h>
int sumRecursive(int n) {
    if (n == 1) return 1;
    return n + sumRecursive(n - 1);
}

int sumIterative(int n) {
    int stack[100];
    int top = -1;
    int sum = 0;
    while (n > 0) {
        stack[++top] = n--;
    }
    while (top >= 0) {
        sum += stack[top--];
    }
    return sum;
}

int main() {
    int n = 10;
    printf("Sum (Recursive): %d\n", sumRecursive(n));
    printf("Sum (Iterative): %d\n", sumIterative(n));
    return 0;
}
