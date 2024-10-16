#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

// Hàm tìm giá trị lớn nhất trong cây
struct TreeNode* FindMax(struct TreeNode* node) {
    struct TreeNode* current = node;
    while (current && current->right != NULL)
        current = current->right;
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

// Hàm kiểm tra cây có phải BST không
int IsBST(struct TreeNode* node, int min, int max) {
    if (node == NULL)
        return 1;

    if (node->info < min || node->info > max)
        return 0;

    return IsBST(node->left, min, node->info - 1) && IsBST(node->right, node->info + 1, max);
}

// Hàm kiểm tra cây có đầy đủ không
int IsFullBinaryTree(struct TreeNode* root) {
    if (root == NULL)
        return 1;

    if ((root->left == NULL && root->right != NULL) || (root->left != NULL && root->right == NULL))
        return 0;

    return IsFullBinaryTree(root->left) && IsFullBinaryTree(root->right);
}

// Hàm tìm nút cha của giá trị khóa x
struct TreeNode* FindParent(struct TreeNode* root, int x) {
    if (root == NULL || root->info == x)
        return NULL;

    if ((root->left != NULL && root->left->info == x) || (root->right != NULL && root->right->info == x))
        return root;

    if (x < root->info)
        return FindParent(root->left, x);
    else
        return FindParent(root->right, x);
}

// Hàm đếm số lượng node của cây
int CountNodes(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    return 1 + CountNodes(root->left) + CountNodes(root->right);
}

// Hàm đếm số node lá
int CountLeafNodes(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;
    return CountLeafNodes(root->left) + CountLeafNodes(root->right);
}

// Hàm đếm số node giữa
int CountInternalNodes(struct TreeNode* root) {
    if (root == NULL || (root->left == NULL && root->right == NULL))
        return 0;
    return 1 + CountInternalNodes(root->left) + CountInternalNodes(root->right);
}

// Hàm tính chiều cao của cây
int Height(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    int leftHeight = Height(root->left);
    int rightHeight = Height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Hàm tính tổng các giá trị trên cây
int Sum(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    return root->info + Sum(root->left) + Sum(root->right);
}

// Hàm chính với menu chức năng
int main() {
    struct TreeNode* root = Init();
    int choice, value, x;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Thêm phần tử\n");
        printf("2. Xóa phần tử\n");
        printf("3. Duyệt cây theo thứ tự giữa (LNR)\n");
        printf("4. Duyệt cây theo thứ tự trước (NLR)\n");
        printf("5. Duyệt cây theo thứ tự sau (LRN)\n");
        printf("6. Kiểm tra cây có phải BST không\n");
        printf("7. Kiểm tra cây có đầy đủ không\n");
        printf("8. Tìm cha của nút có khóa x\n");
        printf("9. Đếm số lượng node\n");
        printf("10. Đếm số node lá\n");
        printf("11. Đếm số node giữa\n");
        printf("12. Tính chiều cao của cây\n");
        printf("13. Tìm giá trị nhỏ nhất\n");
        printf("14. Tìm giá trị lớn nhất\n");
        printf("15. Tính tổng các giá trị trên cây\n");
        printf("16. Thoát\n");
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
                if (IsBST(root, INT_MIN, INT_MAX))
                    printf("Cây là cây nhị phân tìm kiếm.\n");
                else
                    printf("Cây không phải là cây nhị phân tìm kiếm.\n");
                break;
            case 7:
                if (IsFullBinaryTree(root))
                    printf("Cây là cây nhị phân đầy đủ.\n");
                else
                    printf("Cây không phải là cây nhị phân đầy đủ.\n");
                break;
            case 8:
                printf("Nhập khóa x: ");
                scanf("%d", &x);
                struct TreeNode* parent = FindParent(root, x);
                if (parent != NULL)
                    printf("Cha của nút có khóa %d là: %d\n", x, parent->info);
                else
                    printf("Nút có khóa %d không có cha (có thể là nút gốc hoặc không tồn tại).\n", x);
                break;
            case 9:
                printf("Tổng số lượng node: %d\n", CountNodes(root));
                break;
            case 10:
                printf("Số lượng node lá: %d\n", CountLeafNodes(root));
                break;
            case 11:
                printf("Số lượng node giữa: %d\n", CountInternalNodes(root));
                break;
            case 12:
                printf("Chiều cao của cây: %d\n", Height(root));
                break;
            case 13:
                if (root != NULL)
                    printf("Giá trị nhỏ nhất: %d\n", FindMin(root)->info);
                else
                    printf("Cây rỗng.\n");
                break;
            case 14:
                if (root != NULL)
                    printf("Giá trị lớn nhất: %d\n", FindMax(root)->info);
                else
                    printf("Cây rỗng.\n");
                break;
            case 15:
                printf("Tổng các giá trị trên cây: %d\n", Sum(root));
                break;
            case 16:
                exit(0);
            default:
                printf("Lựa chọn không hợp lệ!\n");
        }
    }

    return 0;
}
