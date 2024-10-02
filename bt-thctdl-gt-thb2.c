#include <stdio.h>
#include <stdlib.h>

// Dinh nghia cau truc Node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Khoi tao danh sach lien ket
typedef struct {
    Node* head;
    Node* tail;
} DanhSachLienKet;

// Khoi tao danh sach rong
void khoiTaoDanhSach(DanhSachLienKet* ds) {
    ds->head = NULL;
    ds->tail = NULL;
}

// Kiem tra danh sach co rong hay khong
int danhSachRong(DanhSachLienKet* ds) {
    return ds->head == NULL;
}

// Tao mot nut chua du lieu X
Node* taoNode(int x) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Khong du bo nho de cap phat.\n");
        exit(1);
    }
    newNode->data = x;
    newNode->next = NULL;
    return newNode;
}

// Them phan tu moi vao cuoi danh sach
void themCuoi(DanhSachLienKet* ds, int x) {
    Node* newNode = taoNode(x);
    if (danhSachRong(ds)) {
        ds->head = newNode;
        ds->tail = newNode;
    } else {
        ds->tail->next = newNode;
        ds->tail = newNode;
    }
}

// Xuat danh sach ra man hinh
void xuatDanhSach(DanhSachLienKet* ds) {
    Node* current = ds->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Ham nhap du lieu
void nhapDanhSach(DanhSachLienKet* ds) {
    int n, x;
    printf("Nhap so luong phan tu: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Nhap phan tu thu %d: ", i + 1);
        scanf("%d", &x);
        themCuoi(ds, x);
    }
}

// Ham main
int main() {
    DanhSachLienKet ds;
    khoiTaoDanhSach(&ds);
    nhapDanhSach(&ds);
    printf("Danh sach cac so nguyen: ");
    xuatDanhSach(&ds);
    return 0;
}
