#include <stdio.h>
#include <stdlib.h>

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

Node* timX(Node* head, int x) {
    Node* current = head;
    while (current != NULL && current->data != x) {
        current = current->next;
    }
    return current;
}

Node* timChanDauTien(Node* head) {
    Node* current = head;
    while (current != NULL && current->data % 2 != 0) {
        current = current->next;
    }
    return current;
}

void chenSauChanDauTien(Node* head, int x) {
    Node* chanDauTien = timChanDauTien(head);
    if (chanDauTien != NULL) {
        Node* newNode = taoNode(x);
        newNode->next = chanDauTien->next;
        chanDauTien->next = newNode;
    }
}

void xoaSauLeDauTien(Node* head) {
    Node* current = head;
    while (current != NULL && current->next != NULL && current->data % 2 == 0) {
        current = current->next;
    }
    if (current != NULL && current->next != NULL) {
        Node* temp = current->next;
        current->next = temp->next;
        free(temp);
    }
}

void chenTang(Node** head, int x) {
    Node* newNode = taoNode(x);
    if (*head == NULL || (*head)->data >= x) {
        newNode->next = *head;
        *head = newNode;
    } else {
        Node* current = *head;
        while (current->next != NULL && current->next->data < x) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void tachChanLe(Node* head, Node** l1, Node** l2) {
    while (head != NULL) {
        if (head->data % 2 == 0) {
            *l1 = taoNode(head->data);
            l1 = &((*l1)->next);
        } else {
            *l2 = taoNode(head->data);
            l2 = &((*l2)->next);
        }
        head = head->next;
    }
}

void inDanhSach(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    Node* head = NULL;
    Node* l1 = NULL;
    Node* l2 = NULL;
    int x;

    // Nhập x từ bàn phím
    printf("Nhap x: ");
    scanf("%d", &x);

    // Tạo node p chứa x
    Node* p = taoNode(x);

    // Thêm các hàm gọi ở đây để kiểm tra
    head = taoNode(1);
    head->next = taoNode(2);
    head->next->next = taoNode(3);
    head->next->next->next = taoNode(4);

    printf("Danh sach ban dau: ");
    inDanhSach(head);

    // 1. Tìm x trong DSLK đơn
    Node* found = timX(head, x);
    if (found != NULL) {
        printf("Tim thay %d trong danh sach.\n", x);
    } else {
        printf("Khong tim thay %d trong danh sach.\n", x);
    }

    // 2. Tìm node có key là chẵn đầu tiên trong DSLK đơn
    Node* chanDauTien = timChanDauTien(head);
    if (chanDauTien != NULL) {
        printf("Node chan dau tien: %d\n", chanDauTien->data);
    } else {
        printf("Khong co node chan trong danh sach.\n");
    }

    // 3. Chèn node p vào sau node có key là chẵn đầu tiên trong DSLK đơn
    chenSauChanDauTien(head, x);
    printf("Danh sach sau khi chen %d sau node chan dau tien: ", x);
    inDanhSach(head);

    // 4. Xóa node ngay sau node lẻ đầu tiên trong DSLK đơn
    xoaSauLeDauTien(head);
    printf("Danh sach sau khi xoa node sau node le dau tien: ");
    inDanhSach(head);

    // 5. Chèn x vào DSLK đơn đã sắp xếp tăng
    chenTang(&head, x);
    printf("Danh sach sau khi chen %d vao danh sach tang: ", x);
    inDanhSach(head);

    // 6. Chép các key chẵn của l vào DSLK l1, các key lẻ vào DSLK l2
    tachChanLe(head, &l1, &l2);
    printf("Danh sach l1 (chan): ");
    inDanhSach(l1);
    printf("Danh sach l2 (le): ");
    inDanhSach(l2);

    return 0;
}