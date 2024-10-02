#include <stdio.h>
#include <stdlib.h>

// Khai bao cau truc danh sach lien ket don
typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* taoNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void themCuoi(Node** head, int data) {
    Node* newNode = taoNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

int xoaNode(Node** head, int key) {
    Node* temp = *head;
    Node* prev = NULL;

    if (temp != NULL && temp->data == key) {
        *head = temp->next;
        free(temp);
        return 1;
    }

    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return 0;

    prev->next = temp->next;
    free(temp);
    return 1;
}

void hienThi(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Node* head = NULL;
    int n, x, i, ketQua;

    // Nhap so luong phan tu
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &x);
        themCuoi(&head, x);
    }

    // Nhap gia tri can xoa
    scanf("%d", &x);
    ketQua = xoaNode(&head, x);

    // Hien thi danh sach sau khi xoa
    hienThi(head);

    // In ket qua xoa
    printf("%d\n", ketQua);

    return 0;
}
