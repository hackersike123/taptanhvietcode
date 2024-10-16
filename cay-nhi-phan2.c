#include <stdio.h>
#include <stdlib.h>

// Cấu trúc node của cây
struct TreeNode {
    int info;
    struct TreeNode *left, *right;
};

// Hàm khởi tạo cây
struct TreeNode* Init() {
    return NULL;
}

// Hàm kiểm tra cây có rỗng không
int IsEmpty(struct TreeNode* root) {
    return root == NULL;
}

// Hàm tạo node mới
struct TreeNode* CreateNode(int info) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->info = info;
    node->left = node->right = NULL;
    return node;
}

// Hàm chèn node vào cây
struct TreeNode* Insert(struct TreeNode* node, int info) {
    if (node == NULL)
        return CreateNode(info);

    if (info < node->info)
        node->left = Insert(node->left, info);
    else if (info > node->info)
        node->right = Insert(node->right, info);

    return node;
}

// Hàm tìm giá trị nhỏ nhất trong cây (hỗ trợ hàm Remove)
struct TreeNode* FindMin(struct TreeNode* node) {
    struct TreeNode* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Hàm xóa node khỏi cây
struct TreeNode* Remove(struct TreeNode* root, int info) {
    if (root == NULL)
        return root;

    if (info < root->info)
        root->left = Remove(root->left, info);
    else if (info > root->info)
        root->right = Remove(root->right, info);
    else {
        if (root->left == NULL) {
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        struct TreeNode* temp = FindMin(root->right);
        root->info = temp->info;
        root->right = Remove(root->right, temp->info);
    }

    return root;
}

// Hàm duyệt cây theo thứ tự giữa (LNR)
void InOrder(struct TreeNode* root) {
    if (root != NULL) {
        InOrder(root->left);
        printf("%d ", root->info);
        InOrder(root->right);
    }
}

// Hàm duyệt cây theo thứ tự trước (NLR)
void PreOrder(struct TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->info);
        PreOrder(root->left);
        PreOrder(root->right);
    }
}

// Hàm duyệt cây theo thứ tự sau (LRN)
void PostOrder(struct TreeNode* root) {
    if (root != NULL) {
        PostOrder(root->left);
        PostOrder(root->right);
        printf("%d ", root->info);
    }
}

// Hàm chính với menu chức năng
int main() {
    struct TreeNode* root = Init();
    int choice, value;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Thêm phần tử\n");
        printf("2. Xóa phần tử\n");
        printf("3. Duyệt cây theo thứ tự giữa (LNR)\n");
        printf("4. Duyệt cây theo thứ tự trước (NLR)\n");
        printf("5. Duyệt cây theo thứ tự sau (LRN)\n");
        printf("6. Thoát\n");
        printf("Lựa chọn của bạn: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhập giá trị để thêm: ");
                scanf("%d", &value);
                root = Insert(root, value);
                break;
            case 2:
                printf("Nhập giá trị để xóa: ");
                scanf("%d", &value);
                root = Remove(root, value);
                break;
            case 3:
                printf("Duyệt cây theo thứ tự giữa (LNR): ");
                InOrder(root);
                printf("\n");
                break;
            case 4:
                printf("Duyệt cây theo thứ tự trước (NLR): ");
                PreOrder(root);
                printf("\n");
                break;
            case 5:
                printf("Duyệt cây theo thứ tự sau (LRN): ");
                PostOrder(root);
                printf("\n");
                break;
            case 6:
                exit(0);
            default:
                printf("Lựa chọn không hợp lệ!\n");
        }
    }

    return 0;
}
