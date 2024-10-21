#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} node_t;

void Free(node_t* root) {
    if (root == NULL) return;
    Free(root->left);
    Free(root->right);
    free(root);
}

int LeftOf(const int value, const node_t* root) {
    return value < root->data;
}

int RightOf(const int value, const node_t* root) {
    return value > root->data;
}

node_t* Insert(node_t* root, const int value) {
    if (root == NULL) {
        node_t* node = (node_t*)malloc(sizeof(node_t));
        node->left = NULL;
        node->right = NULL;
        node->data = value;
        return node;
    }
    if (LeftOf(value, root))
        root->left = Insert(root->left, value);
    else if (RightOf(value, root))
        root->right = Insert(root->right, value);
    return root;
}

int LeftMostValue(const node_t* root) {
    while (root->left != NULL)
        root = root->left;
    return root->data;
}

node_t* Delete(node_t* root, int value) {
    if (root == NULL) return root;
    if (LeftOf(value, root))
        root->left = Delete(root->left, value);
    else if (RightOf(value, root))
        root->right = Delete(root->right, value);
    else {
        if (root->left == NULL) {
            node_t* newRoot = root->right;
            free(root);
            return newRoot;
        }
        if (root->right == NULL) {
            node_t* newRoot = root->left;
            free(root);
            return newRoot;
        }
        root->data = LeftMostValue(root->right);
        root->right = Delete(root->right, root->data);
    }
    return root;
}

void PreOrder(node_t* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        PreOrder(root->left);
        PreOrder(root->right);
    }
}

void InOrder(node_t* root) {
    if (root != NULL) {
        InOrder(root->left);
        printf("%d ", root->data);
        InOrder(root->right);
    }
}

void PostOrder(node_t* root) {
    if (root != NULL) {
        PostOrder(root->left);
        PostOrder(root->right);
        printf("%d ", root->data);
    }
}

int main() {
    node_t* root = NULL;
    int n, value;

    printf("Nhập số lượng phần tử: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Nhập phần tử thứ %d: ", i + 1);
        scanf("%d", &value);
        root = Insert(root, value);
    }

    printf("\nDuyệt preorder: ");
    PreOrder(root);
    printf("\nDuyệt inorder: ");
    InOrder(root);
    printf("\nDuyệt postorder: ");
    PostOrder(root);

    Free(root);
    root = NULL;
    return 0;
}
