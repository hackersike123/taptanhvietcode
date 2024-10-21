#include <stdio.h>
#include <stdlib.h> // Include this header for memory management functions

typedef struct tnode {
    int key;
    struct tnode* pLeft;
    struct tnode* pRight;
} TNODE;

typedef TNODE* TREE;

// Declaration of Max function before it's used
int Max(int a, int b);

TNODE* FindMin(TNODE* t) { 
    while (t->pLeft != NULL) {
        t = t->pLeft;
    }
    return t;
}

TNODE* FindMax(TNODE* t) {
    while (t->pRight != NULL) {
        t = t->pRight;
    }
    return t;
}

int DeleteNode(TREE *t, int x) {
    if (*t == NULL) return 0;

    if (x < (*t)->key) 
        return DeleteNode(&(*t)->pLeft, x);
    else if (x > (*t)->key)
        return DeleteNode(&(*t)->pRight, x);
    else {
        if ((*t)->pLeft == NULL && (*t)->pRight == NULL) {
            free(*t);
            *t = NULL;
        } else if ((*t)->pLeft == NULL) {
            TNODE* temp = *t;
            *t = (*t)->pRight;
            free(temp);
        } else if ((*t)->pRight == NULL) {
            TNODE* temp = *t;
            *t = (*t)->pLeft;
            free(temp);
        } else {
            TNODE* temp = FindMin((*t)->pRight);
            (*t)->key = temp->key;
            DeleteNode(&(*t)->pRight, temp->key);
        }
    }
    return 1;
}

int AddNode(TREE *t, int x) {
    if (*t != NULL) {
        if (x == (*t)->key) return 0;
        else {
            if (x < (*t)->key) return AddNode(&(*t)->pLeft, x);
            else return AddNode(&(*t)->pRight, x);
        }
    } else {
        *t = (TNODE*)malloc(sizeof(TNODE));
        if (*t == NULL) return -1;
        (*t)->key = x;
        (*t)->pLeft = (*t)->pRight = NULL;
        return 1;
    }
}

void TreeInput(TREE *t) {
    int a[20] = {25, 7, 10, 13, 2, 4, 3, 8, 11, 45, 32, 61, 65, 60, 28, 27, 29, 30};
    int n = 18;
    *t = NULL;
    for (int i = 0; i < n; i++) {
        AddNode(t, a[i]);
    }
}

int SearchBST(TREE t, int x) {
    if (t != NULL) {
        if (t->key == x)
            return 1;
        else {
            if (x < t->key) return SearchBST(t->pLeft, x);
            else return SearchBST(t->pRight, x);
        }
    }
    return 0;
}

void TraverseLNR(TREE t) {
    if (t != NULL) {
        TraverseLNR(t->pLeft);
        printf("%3d", t->key);
        TraverseLNR(t->pRight);
    }
}

void DeleteTree(TREE *t) {
    if (*t != NULL) {
        DeleteTree(&(*t)->pLeft);
        DeleteTree(&(*t)->pRight);
        free(*t);
        *t = NULL;
    }
}

int NodeCounting(TREE t) {
    if (t == NULL) return 0;
    return 1 + NodeCounting(t->pLeft) + NodeCounting(t->pRight);
}

int LeafCounting(TREE t) {
    if (t == NULL) return 0;
    if (t->pLeft == NULL && t->pRight == NULL)
        return 1;
    return LeafCounting(t->pLeft) + LeafCounting(t->pRight);
}

int TwoChildrenCounting(TREE t) {
    if (t == NULL) return 0;
    if (t->pLeft != NULL && t->pRight != NULL)
        return 1 + TwoChildrenCounting(t->pLeft) + TwoChildrenCounting(t->pRight);
    return TwoChildrenCounting(t->pLeft) + TwoChildrenCounting(t->pRight);
}

int OneChildrenCounting(TREE t) {
    if (t == NULL) return 0;
    if ((t->pLeft != NULL && t->pRight == NULL) || (t->pLeft == NULL && t->pRight != NULL))
        return 1 + OneChildrenCounting(t->pLeft) + OneChildrenCounting(t->pRight);
    return OneChildrenCounting(t->pLeft) + OneChildrenCounting(t->pRight);
}

int Sum(TREE t) {
    if (t == NULL) return 0;
    return t->key + Sum(t->pLeft) + Sum(t->pRight);
}

int EvenSum(TREE t) {
    if (t == NULL) return 0;
    if (t->key % 2 == 0)
        return t->key + EvenSum(t->pLeft) + EvenSum(t->pRight);
    return EvenSum(t->pLeft) + EvenSum(t->pRight);
}

int TreeHeight(TREE t) {
    if (t == NULL) return 0;
    return 1 + Max(TreeHeight(t->pLeft), TreeHeight(t->pRight));
}

int Max(int a, int b) {
    return (a > b) ? a : b;
}

void Distance(TREE t, int x, int muc, int *dem) {
    if (t == NULL) {
        printf("\nKhong tim thay x trong cay\n");
        return;
    }
    if (t->key == x) {
        *dem = muc;
        return;
    }
    muc++;
    if (x > t->key) Distance(t->pRight, x, muc, dem);
    else Distance(t->pLeft, x, muc, dem);
}

int main() {
    TREE t;
    TreeInput(&t);
    TraverseLNR(t);
    printf("\nSo Luong nut la = %d", LeafCounting(t));
    printf("\nSo Luong nut = %d", NodeCounting(t));
    printf("\nTong cua cay = %d", Sum(t));
    printf("\nTong so chan = %d", EvenSum(t));
    printf("\nSo nut co 2 con = %d", TwoChildrenCounting(t));
    printf("\nSo nut co 1 con = %d", OneChildrenCounting(t));
    printf("\nChieu cao cay = %d", TreeHeight(t));

    int m = 0, dem = 0, x;
    printf("\nNhap x: ");
    scanf("%d", &x);
    Distance(t, x, m, &dem);
    printf("Do dai duong di den x: %d", dem);
    DeleteTree(&t);
    return 0;
}
