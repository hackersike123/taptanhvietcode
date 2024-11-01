#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
typedef struct{
    char maSo[11];
    char hoTen[41];
    float diemTB;
}SV;

void nhap(SV &sv){
    getchar();
    gets(sv.maSo);
    gets(sv.hoTen);
    scanf("%f", &sv.diemTB);
}

void xuat(SV sv){
    printf("%s - %s - %.2f\n", sv.maSo, sv.hoTen, sv.diemTB);
}

typedef struct Node{
    SV key;
    struct Node*pNext;
}NODE;

typedef struct List{
    NODE*pHead;
    NODE*pTail;
}LIST;

void Init(LIST &l){
    l.pHead = NULL;
    l.pTail = NULL;
}

void InsertTail(LIST &l, NODE* p){
    if(l.pHead == NULL){
        l.pTail = p;
        l.pHead = p;
    }
    else{
        l.pTail->pNext = p;
        l.pTail = p;
    }
}

NODE* CreateNode(SV x){
    NODE *p = new NODE;
    if(p == NULL){
        printf("Khong cap phat duoc");
        exit(0);
    }
    p->key = x;
    p->pNext = NULL;
    return p;
}

void nhapDS(LIST &l){
    SV sv;
    nhap(sv);
    NODE* p = CreateNode(sv);
    InsertTail(l, p);
}

void xuatDS(LIST l){
    char maSo[11];
    getchar();
    gets(maSo);
    bool check = false;
    for(NODE* i = l.pHead; i != NULL; i = i->pNext){
        if(strcmp(i->key.maSo, maSo) == 0){
            xuat(i->key);
            check = true;
        }
    }
    if(check == false) printf("Not Found");
}

int main() {
    //Tiếp tục hoàn thiện mã nguồn
    int n;
    scanf("%d", &n);
    LIST l;
    Init(l);
    for(int i = 0; i < n; i++){
        nhapDS(l);
    }
    xuatDS(l);
    return 0;
}