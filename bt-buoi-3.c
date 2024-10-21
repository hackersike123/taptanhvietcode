#include <stdio.h>
#include <stdlib.h>

#define MAX 1000 // Kích thước tối đa của ngăn xếp

int top = -1;
int stack[MAX];

// Hàm đẩy phần tử vào ngăn xếp
void push(int bit) {
    if (top == (MAX - 1)) {
        printf("\nStack Overflow");
    } else {
        top = top + 1;
        stack[top] = bit;
    }
}

// Hàm lấy phần tử ra khỏi ngăn xếp
int pop() {
    if (top == -1) {
        printf("\nStack Underflow");
        return -1;
    } else {
        return stack[top--];
    }
}

int main() {
    int n;
    scanf("%d", &n); // Đọc số nguyên đầu vào

    // Kiểm tra nếu số nằm trong khoảng cho phép
    if (n >= 1 && n < pow(10, 6)) {
        while (n > 0) {
            int remainder = n % 2;
            push(remainder);
            n = n / 2;
        }

        // In ra kết quả nhị phân
        while (top != -1) {
            printf("%d", pop());
        }
    } else {
        printf("Number out of range");
    }

    return 0;
}
