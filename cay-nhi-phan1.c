#include <stdio.h>
#include <stdlib.h>

// Dinh nghia cau truc cho node cua cay
struct TreeNode {
    int info;
    struct TreeNode *left, *right;
};

// Ham tao mot node moi
struct TreeNode* taoNodeMoi(int info) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->info = info;
    node->left = node->right = NULL;
    return node;
}

// Ham chen mot node vao cay nhi phan
struct TreeNode* chenNode(struct TreeNode* node, int info) {
    if (node == NULL)
        return taoNodeMoi(info);

    if (info < node->info)
        node->left = chenNode(node->left, info);
    else if (info > node->info)
        node->right = chenNode(node->right, info);

    return node;
}

// Ham duyet cay theo thu tu giua (LNR)
void duyetGiua(struct TreeNode* root) {
    if (root != NULL) {
        duyetGiua(root->left);
        printf("%d ", root->info);
        duyetGiua(root->right);
    }
}

// Ham duyet cay theo thu tu truoc (NLR)
void duyetTruoc(struct TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->info);
        duyetTruoc(root->left);
        duyetTruoc(root->right);
    }
}

// Ham duyet cay theo thu tu sau (LRN)
void duyetSau(struct TreeNode* root) {
    if (root != NULL) {
        duyetSau(root->left);
        duyetSau(root->right);
        printf("%d ", root->info);
    }
}

// Ham dem so luong node cua cay
int demNode(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    return 1 + demNode(root->left) + demNode(root->right);
}

// Ham dem so node co gia tri lon hon x
int demNodeLonHonX(struct TreeNode* root, int x) {
    if (root == NULL)
        return 0;
    int count = 0;
    if (root->info > x)
        count = 1;
    return count + demNodeLonHonX(root->left, x) + demNodeLonHonX(root->right, x);
}

// Ham dem so luong la cay
int demLaCay(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;
    return demLaCay(root->left) + demLaCay(root->right);
}

// Ham dem so luong la cay co gia tri lon hon y
int demLaCayLonHonY(struct TreeNode* root, int y) {
    if (root == NULL)
        return 0;
    int count = 0;
    if (root->left == NULL && root->right == NULL && root->info > y)
        count = 1;
    return count + demLaCayLonHonY(root->left, y) + demLaCayLonHonY(root->right, y);
}

int main() {
    int n, x, y;

    // Nhan so luong phan tu cua mang tu nguoi dung
    printf("Nhap so luong phan tu cua mang: ");
    scanf("%d", &n);

    int array[n];

    // Nhan gia tri cua mang tu nguoi dung
    printf("Nhap cac phan tu cua mang: \n");
    for (int i = 0; i < n; i++) {
        printf("Phan tu thu %d: ", i + 1);
        scanf("%d", &array[i]);
    }

    // Nhan gia tri x va y tu nguoi dung
    printf("Nhap gia tri x: ");
    scanf("%d", &x);
    printf("Nhap gia tri y: ");
    scanf("%d", &y);

    struct TreeNode* root = NULL;

    // Chen cac phan tu cua mang vao cay nhi phan
    for (int i = 0; i < n; i++)
        root = chenNode(root, array[i]);

    printf("Duyet theo thu tu giua (LNR): ");
    duyetGiua(root);
    printf("\n");

    printf("Duyet theo thu tu truoc (NLR): ");
    duyetTruoc(root);
    printf("\n");

    printf("Duyet theo thu tu sau (LRN): ");
    duyetSau(root);
    printf("\n");

    printf("Tong so luong node: %d\n", demNode(root));
    printf("So luong node lon hon %d: %d\n", x, demNodeLonHonX(root, x));
    printf("So luong la cay: %d\n", demLaCay(root));
    printf("So luong la cay co gia tri lon hon %d: %d\n", y, demLaCayLonHonY(root, y));

    return 0;
}
