#include <stdio.h>
#include <stdlib.h>

// Cấu trúc của một node trong BST
struct Node
{
    int data;
    struct Node *left, *right;
    int height;
};

// Hàm trả về chiều cao của node
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// Hàm tạo node mới
struct Node *newNode(int item)
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->data = item;
    temp->left = temp->right = NULL;
    temp->height = 1; // New node is initially added at leaf
    return temp;
}

// Hàm xoay phải
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Thực hiện xoay
    x->right = y;
    y->left = T2;

    // Cập nhật chiều cao
    y->height = 1 + height(y->left) + height(y->right);
    x->height = 1 + height(x->left) + height(x->right);

    return x;
}

// Hàm xoay trái
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Thực hiện xoay
    y->left = x;
    x->right = T2;

    // Cập nhật chiều cao
    x->height = 1 + height(x->left) + height(x->right);
    y->height = 1 + height(y->left) + height(y->right);

    return y;
}

// Hàm lấy giá trị cân bằng của node
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Hàm chèn một node mới vào cây AVL
struct Node *insertAVL(struct Node *node, int data)
{
    if (node == NULL)
        return newNode(data);

    if (data < node->data)
        node->left = insertAVL(node->left, data);
    else if (data > node->data)
        node->right = insertAVL(node->right, data);
    else
        return node;

    // Cập nhật chiều cao của node tổ tiên
    node->height = 1 + height(node->left) + height(node->right);

    // Lấy giá trị cân bằng của node tổ tiên để kiểm tra xem node đó có mất cân bằng không
    int balance = getBalance(node);

    // Nếu node này mất cân bằng, thì có 4 trường hợp
    // Trường hợp Left Left
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // Trường hợp Right Right
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // Trường hợp Left Right
    if (balance > 1 && data > node->left->data)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Trường hợp Right Left
    if (balance < -1 && data < node->right->data)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Hàm chèn một node mới vào BST
struct Node *insertBST(struct Node *node, int data)
{
    if (node == NULL)
        return newNode(data);

    if (data < node->data)
        node->left = insertBST(node->left, data);
    else if (data > node->data)
        node->right = insertBST(node->right, data);

    return node;
}

// Duyệt trước (Preorder traversal)
void preorder(struct Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Duyệt giữa (Inorder traversal)
void inorder(struct Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Duyệt sau (Postorder traversal)
void postorder(struct Node *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// Hàm in cây theo cấp độ sử dụng queue
void printTreeByLevels(struct Node *root)
{
    if (root == NULL)
        return;

    struct Node **queue = malloc(sizeof(struct Node *) * 100);
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear)
    {
        int nodeCount = rear - front;

        // Xử lý từng cấp độ của cây
        while (nodeCount > 0)
        {
            struct Node *node = queue[front++];
            printf("%d ", node->data);

            if (node->left != NULL)
                queue[rear++] = node->left;
            if (node->right != NULL)
                queue[rear++] = node->right;

            nodeCount--;
        }
        printf("\n");
    }

    free(queue);
}

// Hàm tìm node nhỏ nhất trong cây con bên phải
struct Node *minValueNode(struct Node *node)
{
    struct Node *current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Hàm xóa một node trong BST
struct Node *deleteNode(struct Node *root, int key)
{
    if (root == NULL)
        return root;

    // Nếu key nhỏ hơn giá trị root, đi sang cây con bên trái
    if (key < root->data)
        root->left = deleteNode(root->left, key);

    // Nếu key lớn hơn giá trị root, đi sang cây con bên phải
    else if (key > root->data)
        root->right = deleteNode(root->right, key);

    // Nếu key bằng giá trị root, đây là node cần xóa
    else
    {
        // Node có ít hơn hoặc bằng một con
        if (root->left == NULL)
        {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }

        // Node có hai con, tìm node nhỏ nhất trong cây con bên phải
        struct Node *temp = minValueNode(root->right);

        // Sao chép giá trị của node nhỏ nhất vào node cần xóa
        root->data = temp->data;

        // Xóa node nhỏ nhất trong cây con bên phải
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

int main()
{
    struct Node *rootBST = NULL;
    struct Node *rootAVL = NULL;
    int values[] = {37, 27, 33, 46, 18, 61, 43, 39, 45, 29, 35, 32, 70, 28, 40, 41, 55, 57, 52, 59};
    int n = sizeof(values) / sizeof(values[0]);
    for (int i = 0; i < n; i++)
    {
        rootBST = insertBST(rootBST, values[i]);
        rootAVL = insertAVL(rootAVL, values[i]);
    }

    printf("Cây BST theo cấp độ:\n");
    printTreeByLevels(rootBST);

    printf("Duyệt trước (Preorder):\n");
    preorder(rootBST);
    printf("\n");

    printf("Duyệt giữa (Inorder):\n");
    inorder(rootBST);
    printf("\n");

    printf("Duyệt sau (Postorder):\n");
    postorder(rootBST);
    printf("\n");

    // Xóa node có giá trị 46
    rootBST = deleteNode(rootBST, 46);
    printf("Cây BST sau khi xóa 46:\n");
    printTreeByLevels(rootBST);

    printf("Cây AVL theo cấp độ:\n");
    printTreeByLevels(rootAVL);

    return 0;
}
