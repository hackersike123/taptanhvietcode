#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Định nghĩa cấu trúc ngăn xếp
typedef struct {
    int dinh;
    char phan_tu[MAX];
} NganXep;

// Khởi tạo ngăn xếp
void khoiTaoNganXep(NganXep *s) {
    s->dinh = -1;
}

// Kiểm tra ngăn xếp đầy
int day(NganXep *s) {
    return s->dinh == MAX - 1;
}

// Kiểm tra ngăn xếp rỗng
int rong(NganXep *s) {
    return s->dinh == -1;
}

// Đẩy phần tử vào ngăn xếp
void dayVao(NganXep *s, char gia_tri) {
    if (!day(s)) {
        s->phan_tu[++(s->dinh)] = gia_tri;
    }
}

// Lấy phần tử ra khỏi ngăn xếp
char layRa(NganXep *s) {
    if (!rong(s)) {
        return s->phan_tu[(s->dinh)--];
    }
    return '\0';
}

// Xem phần tử trên đỉnh ngăn xếp
char xemDinh(NganXep *s) {
    if (!rong(s)) {
        return s->phan_tu[s->dinh];
    }
    return '\0';
}

// Xác định độ ưu tiên của toán tử
int doUuTien(char toan_tu) {
    switch (toan_tu) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

// Kiểm tra ký tự có phải là toán tử không
int laToanTu(char ky_tu) {
    return ky_tu == '+' || ky_tu == '-' || ky_tu == '*' || ky_tu == '/' || ky_tu == '^';
}

// Chuyển đổi biểu thức infix sang postfix
void infixSangPostfix(char *infix, char *postfix) {
    NganXep s;
    khoiTaoNganXep(&s);
    int i, k = 0;
    for (i = 0; infix[i]; i++) {
        // Nếu ký tự là toán hạng, thêm vào kết quả
        if (isdigit(infix[i]) || isalpha(infix[i])) {
            postfix[k++] = infix[i];
        } 
        // Nếu ký tự là dấu ngoặc mở, đẩy vào ngăn xếp
        else if (infix[i] == '(') {
            dayVao(&s, infix[i]);
        } 
        // Nếu ký tự là dấu ngoặc đóng, lấy các toán tử ra khỏi ngăn xếp cho đến khi gặp dấu ngoặc mở
        else if (infix[i] == ')') {
            while (!rong(&s) && xemDinh(&s) != '(') {
                postfix[k++] = layRa(&s);
            }
            layRa(&s); // Bỏ dấu ngoặc mở '(' ra khỏi ngăn xếp
        } 
        // Nếu ký tự là toán tử, xử lý dựa trên độ ưu tiên
        else if (laToanTu(infix[i])) {
            while (!rong(&s) && doUuTien(xemDinh(&s)) >= doUuTien(infix[i])) {
                postfix[k++] = layRa(&s);
            }
            dayVao(&s, infix[i]);
        }
    }
    // Lấy tất cả các toán tử còn lại trong ngăn xếp ra kết quả
    while (!rong(&s)) {
        postfix[k++] = layRa(&s);
    }
    postfix[k] = '\0'; // Kết thúc chuỗi postfix
}

int main() {
    char infix[MAX], postfix[MAX];
    printf("Nhap bieu thuc infix: ");
    gets(infix);
    infixSangPostfix(infix, postfix);
    printf("Bieu thuc postfix: %s\n", postfix);
    return 0;
}
