#include <stdio.h>
#include <stdlib.h>

// Định nghĩa cấu trúc của một nút trong DSLK
struct Node {
    int data;
    struct Node* next;
};

// Hàm tạo một nút mới
struct Node* taoNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Hàm nhập DSLK
void nhapDSLK(struct Node** head, int n) {
    int data;
    struct Node* temp = *head;
    for (int i = 0; i < n; i++) {
        printf("Nhap phan tu thu %d: ", i + 1);
        scanf("%d", &data);
        struct Node* newNode = taoNode(data);
        if (*head == NULL) {
            *head = newNode;
            temp = *head;
        } else {
            temp->next = newNode;
            temp = temp->next;
        }
    }
}

// Hàm xuất DSLK
void xuatDSLK(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d\t", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Hàm sắp xếp nổi bọt cho DSLK
void sapXepNoiBot(struct Node* head) {
    int swapped;
    struct Node* ptr1;
    struct Node* lptr = NULL;

    if (head == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Hàm sắp xếp chọn cho DSLK
void sapXepChon(struct Node* head) {
    struct Node* temp = head;

    while (temp) {
        struct Node* min = temp;
        struct Node* r = temp->next;

        while (r) {
            if (min->data > r->data)
                min = r;

            r = r->next;
        }

        int x = temp->data;
        temp->data = min->data;
        min->data = x;
        temp = temp->next;
    }
}

// Hàm sắp xếp chèn cho DSLK
void sapXepChen(struct Node** head) {
    struct Node* sorted = NULL;
    struct Node* current = *head;

    while (current != NULL) {
        struct Node* next = current->next;
        if (sorted == NULL || sorted->data >= current->data) {
            current->next = sorted;
            sorted = current;
        } else {
            struct Node* temp = sorted;
            while (temp->next != NULL && temp->next->data < current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    *head = sorted;
}

// Hàm sắp xếp nhanh cho DSLK
struct Node* getTail(struct Node* cur) {
    while (cur != NULL && cur->next != NULL)
        cur = cur->next;
    return cur;
}

struct Node* partition(struct Node* head, struct Node* end, struct Node** newHead, struct Node** newEnd) {
    struct Node* pivot = end;
    struct Node* prev = NULL, *cur = head, *tail = pivot;

    while (cur != pivot) {
        if (cur->data < pivot->data) {
            if ((*newHead) == NULL)
                (*newHead) = cur;

            prev = cur;
            cur = cur->next;
        } else {
            if (prev)
                prev->next = cur->next;
            struct Node* temp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }

    if ((*newHead) == NULL)
        (*newHead) = pivot;

    (*newEnd) = tail;

    return pivot;
}

struct Node* sapXepNhanhRecur(struct Node* head, struct Node* end) {
    if (!head || head == end)
        return head;

    struct Node* newHead = NULL, *newEnd = NULL;

    struct Node* pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        struct Node* temp = newHead;
        while (temp->next != pivot)
            temp = temp->next;
        temp->next = NULL;

        newHead = sapXepNhanhRecur(newHead, temp);

        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = sapXepNhanhRecur(pivot->next, newEnd);

    return newHead;
}

void sapXepNhanh(struct Node** headRef) {
    (*headRef) = sapXepNhanhRecur(*headRef, getTail(*headRef));
}

int main() {
    struct Node* head = NULL;
    int n, luaChon;
    printf("Nhap so luong phan tu cua DSLK: ");
    scanf("%d", &n);
    nhapDSLK(&head, n);

    printf("Chon thuat toan sap xep:\n");
    printf("1. Sap xep noi bot\n");
    printf("2. Sap xep chon\n");
    printf("3. Sap xep chen\n");
    printf("4. Sap xep nhanh\n");
    scanf("%d", &luaChon);

    switch (luaChon) {
        case 1:
            sapXepNoiBot(head);
            break;
        case 2:
            sapXepChon(head);
            break;
        case 3:
            sapXepChen(&head);
            break;
        case 4:
            sapXepNhanh(&head);
            break;
        default:
            printf("Lua chon khong hop le!\n");
            return 1;
    }

    printf("DSLK sau khi sap xep:\n");
    xuatDSLK(head);

    return 0;
}
