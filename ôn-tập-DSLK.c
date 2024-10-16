#include <stdio.h>
#include <stdlib.h>

// Định nghĩa cấu trúc của một node
struct Node {
    int data;
    struct Node* next;
};

// Thêm một node mới vào đầu danh sách
void themDau(struct Node** head, int data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = *head;
    *head = newNode;
}

// Thêm một node mới vào cuối danh sách
void themCuoi(struct Node** head, int data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Thêm một node mới vào vị trí bất kì do người dùng nhập
void themViTri(struct Node** head, int data, int position) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (position == 0) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    struct Node* temp = *head;
    for (int i = 1; i < position && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp != NULL) {
        newNode->next = temp->next;
        temp->next = newNode;
    } else {
        printf("Vị trí ngoài phạm vi.\n");
    }
}

// Xóa node ở đầu danh sách
void xoaDau(struct Node** head) {
    if (*head == NULL) return;

    struct Node* temp = *head;
    *head = (*head)->next;

    free(temp);
}

// Xóa node ở cuối danh sách
void xoaCuoi(struct Node** head) {
    if (*head == NULL) return;

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }

    struct Node* temp = *head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }

    free(temp->next);
    temp->next = NULL;
}

// Xóa node ở vị trí bất kì do người dùng nhập
void xoaViTri(struct Node** head, int position) {
    if (*head == NULL) return;

    struct Node* temp = *head;

    if (position == 0) {
        *head = temp->next;
        free(temp);
        return;
    }

    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) return;

    struct Node* next = temp->next->next;
    free(temp->next);
    temp->next = next;
}

// Hiển thị danh sách liên kết đơn
void hienThiDanhSach(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    int chon, data, position;

    // Thêm sẵn dãy số bất kì
    int array[] = {5, 15, 25, 35, 45};
    for (int i = 0; i < 5; i++) {
        themCuoi(&head, array[i]);
    }
    hienThiDanhSach(head);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Thêm đầu\n");
        printf("2. Thêm cuối\n");
        printf("3. Thêm vào vị trí bất kì\n");
        printf("4. Xóa đầu\n");
        printf("5. Xóa cuối\n");
        printf("6. Xóa vị trí bất kì\n");
        printf("7. Hiển thị danh sách\n");
        printf("8. Thoát\n");
        printf("Chọn: ");
        scanf("%d", &chon);

        switch (chon) {
            case 1:
                printf("Nhập dữ liệu: ");
                scanf("%d", &data);
                themDau(&head, data);
                break;
            case 2:
                printf("Nhập dữ liệu: ");
                scanf("%d", &data);
                themCuoi(&head, data);
                break;
            case 3:
                printf("Nhập dữ liệu: ");
                scanf("%d", &data);
                printf("Nhập vị trí: ");
                scanf("%d", &position);
                themViTri(&head, data, position);
                break;
            case 4:
                xoaDau(&head);
                break;
            case 5:
                xoaCuoi(&head);
                break;
            case 6:
                printf("Nhập vị trí: ");
                scanf("%d", &position);
                xoaViTri(&head, position);
                break;
            case 7:
                hienThiDanhSach(head);
                break;
            case 8:
                exit(0);
                break;
            default:
                printf("Lựa chọn không hợp lệ.\n");
        }
    }

    return 0;
}
