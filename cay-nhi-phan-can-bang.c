#include <stdio.h>
#include <stdlib.h>

// Cấu trúc của một node trong AVL tree
struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

// Hàm trả về chiều cao của một node
int height(struct Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Hàm trả về giá trị lớn hơn trong hai số a và b
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Hàm tạo một node mới
struct Node* newNode(int key) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // ban đầu node mới có chiều cao là 1
    return node;
}

// Hàm xoay phải subtree với root là y
struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Thực hiện xoay
    x->right = y;
    y->left = T2;

    // Cập nhật chiều cao
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Trả về root mới
    return x;
}

// Hàm xoay trái subtree với root là x
struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Thực hiện xoay
    y->left = x;
    x->right = T2;

    // Cập nhật chiều cao
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Trả về root mới
    return y;
}

// Hàm lấy hệ số cân bằng của node N
int getBalance(struct Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Hàm chèn một key vào AVL tree và trả về root mới của subtree đã sửa đổi
struct Node* insert(struct Node* node, int key) {
    // 1. Thực hiện chèn bình thường như BST
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Các key giống nhau không được phép trong BST
        return node;

    // 2. Cập nhật chiều cao của node tổ tiên này
    node->height = 1 + max(height(node->left), height(node->right));

    // 3. Lấy hệ số cân bằng của node tổ tiên này để kiểm tra xem node này có mất cân bằng hay không
    int balance = getBalance(node);

    // Nếu node này mất cân bằng, thì có 4 trường hợp

    // Trường hợp Left Left
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Trường hợp Right Right
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Trường hợp Left Right
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Trường hợp Right Left
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Trả về con trỏ node (không thay đổi)
    return node;
}

// Hàm inorder traversal của AVL tree
void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

int main() {
    struct Node *root = NULL;

    // Chèn các giá trị vào cây AVL
    root = insert(root, 25);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 18);
    root = insert(root, 6);
    //root = insert(root, 25);

    // Inorder traversal của cây AVL
    printf("\nInorder traversal của cây AVL là:\n");
    inorder(root);

    return 0;
}
