#include <stdio.h>
#include <stdlib.h>

// Định nghĩa cấu trúc Node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Khởi tạo danh sách liên kết
typedef struct {
    Node* head;
    Node* tail;
} LinkedList;

// Khởi tạo danh sách rỗng
void initList(LinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
}

// Kiểm tra danh sách có rỗng hay không
int isEmpty(LinkedList* list) {
    return list->head == NULL;
}

// Tạo một nút chứa dữ liệu X
Node* createNode(int x) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Không đủ bộ nhớ để cấp phát.\n");
        exit(1);
    }
    newNode->data = x;
    newNode->next = NULL;
    return newNode;
}

// Thêm phần tử mới vào cuối danh sách
void addTail(LinkedList* list, int x) {
    Node* newNode = createNode(x);
    if (isEmpty(list)) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

// Xuất danh sách ra màn hình
void printList(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Hàm nhập dữ liệu
void inputList(LinkedList* list) {
    int n, x;
    printf("Nhập số lượng phần tử: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Nhập phần tử thứ %d: ", i + 1);
        scanf("%d", &x);
        addTail(list, x);
    }
}

// Hàm main
int main() {
    LinkedList list;
    initList(&list);
    inputList(&list);
    printf("Danh sách các số nguyên: ");
    printList(&list);
    return 0;
}
