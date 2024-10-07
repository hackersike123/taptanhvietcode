#include <stdio.h>
#include <stdlib.h>

void decToBinary(int n) {
    int stack[32];
    int top = -1;
    while (n > 0) {
        stack[++top] = n % 2;
        n /= 2;
    }
    while (top >= 0) {
        printf("%d", stack[top--]);
    }
    printf("\n");
}

void decToAnyBase(int n, int base) {
    char stack[32];
    int top = -1;
    char digits[] = "0123456789ABCDEF";
    while (n > 0) {
        stack[++top] = digits[n % base];
        n /= base;
    }
    while (top >= 0) {
        printf("%c", stack[top--]);
    }
    printf("\n");
}

int main() {
    int num = 29;
    printf("Binary: ");
    decToBinary(num);
    printf("Octal: ");
    decToAnyBase(num, 8);
    printf("Hexadecimal: ");
    decToAnyBase(num, 16);
    return 0;
}
