#include <stdio.h>
#include <stdlib.h>

// Định nghĩa cấu trúc cho một node trong cây
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Hàm tạo một node mới
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Hàm chèn một giá trị vào cây
Node* insert(Node* root, int data) {
    if (root == NULL) {
        root = createNode(data);
    } else if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

// Hàm tìm kiếm một giá trị trong cây
int search(Node* root, int data) {
    if (root == NULL) {
        return 0;
    } else if (root->data == data) {
        return 1;
    } else if (data < root->data) {
        return search(root->left, data);
    } else {
        return search(root->right, data);
    }
}

// Hàm duyệt cây theo thứ tự giữa
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Hàm giải phóng bộ nhớ cho cây
void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    Node* root = NULL;

    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 20);
    root = insert(root, 8);
    root = insert(root, 15);

    printf("Duyệt cây theo thứ tự giữa: ");
    inorderTraversal(root);
    printf("\n");

    int value = 15;
    if (search(root, value)) {
        printf("%d tồn tại trong cây.\n", value);
    } else {
        printf("%d không tồn tại trong cây.\n", value);
    }

    freeTree(root);
    return 0;
}
