#include <stdio.h>

struct SACH
{
    int MaSach;
    char TenSach[1000];
    char TenTG[100];
    int NXB;
};
typedef struct SACH sach;
void nhapSach(sach* a, int n){
    for (int i=0;i<n;i++){
        printf("nhap ma sach:");
        scanf("%d",&a[i].MaSach);
        printf("nhap ten sach:");
        scanf(" %[^\n]",a[i].TenSach);
        printf("nhap ten tac gia:");
        scanf(" %[^\n]",a[i].TenTG);
        printf("nhap nam xuat ban:");
        scanf("%d",&a[i].NXB);
    }
}
void hienthiSach(sach* a,int n){
    for (int j=0;j<n;j++){
        printf("%d\t%s\t%s\t%d\n",a[j].MaSach,a[j].TenSach,a[j].TenTG,a[j].NXB);
    }
}
void sapxepdoicho(sach* a, int n){
    for (int i=0;i<n-1;i++){
        for (int j=i+1;j<n;j++){
            if (a[i].MaSach>a[j].MaSach){
                sach temp = a[i];
                a[i]=a[j];
                a[j]=temp;
            }
        }
    }
}
void sapxepchon(sach* a, int n){
    int i,j,benhat;
    for(i=0;i<n-1;i++){
        benhat=i;
        for(j=i+1;j<n;j++){
            if (a[j].MaSach<a[benhat].MaSach){
                benhat=j;
            }
        }
        if(benhat!=i){
            sach temp = a[i];
            a[i]=a[benhat];
            a[benhat]=temp;
        }
    }
}
void sapxepchen(sach* a, int n){
    int i, j;
    sach key;
    for (i = 1; i < n; i++) {
        key = a[i];
        j = i - 1;
        while (j >= 0 && a[j].MaSach > key.MaSach) {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = key;
    }
}
void sapxepnoibot(sach* a, int n){
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j].MaSach > a[j + 1].MaSach) {
                sach temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}
void sapxepnhanh(sach* a,int thap, int cao) {
    if (thap < cao) {
        int chot = a[cao].MaSach;
        int i = (thap - 1);
        for (int j = thap; j <= cao - 1; j++) {
            if (a[j].MaSach < chot) {
                i++;
                sach temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
        sach temp = a[i + 1];
        a[i + 1] = a[cao];
        a[cao] = temp;
        int pi = i + 1;

        sapxepnhanh(a, thap, pi - 1);
        sapxepnhanh(a, pi + 1, cao);
    }
}
void heapify(sach* a, int n, int i) {
    int lonNhat = i;
    int trai = 2 * i + 1;
    int phai = 2 * i + 2;

    if (trai < n && a[trai].MaSach > a[lonNhat].MaSach)
        lonNhat = trai;

    if (phai < n && a[phai].MaSach > a[lonNhat].MaSach)
        lonNhat = phai;

    if (lonNhat != i) {
        sach temp = a[i];
        a[i] = a[lonNhat];
        a[lonNhat] = temp;

        heapify(a, n, lonNhat);
    }
}

void sapxepheap(sach* a, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    for (int i = n - 1; i > 0; i--) {
        sach temp = a[0];
        a[0] = a[i];
        a[i] = temp;

        heapify(a, i, 0);
    }
}

void sapxepshell(sach* a, int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            sach temp = a[i];
            int j;
            for (j = i; j >= gap && a[j - gap].MaSach > temp.MaSach; j -= gap) {
                a[j] = a[j - gap];
            }
            a[j] = temp;
        }
    }
}

void merge(sach* a, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    sach L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = a[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].MaSach <= R[j].MaSach) {
            a[k] = L[i];
            i++;
        } else {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        a[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        a[k] = R[j];
        j++;
        k++;
    }
}

void sapxeptron(sach* a, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        sapxeptron(a, l, m);
        sapxeptron(a, m + 1, r);

        merge(a, l, m, r);
    }
}

int getMax(sach* a, int n) {
    int max = a[0].MaSach;
    for (int i = 1; i < n; i++)
        if (a[i].MaSach > max)
            max = a[i].MaSach;
    return max;
}

void countSort(sach* a, int n, int exp) {
    sach output[n];
    int i, count[10] = {0};

    for (i = 0; i < n; i++)
        count[(a[i].MaSach / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        output[count[(a[i].MaSach / exp) % 10] - 1] = a[i];
        count[(a[i].MaSach / exp) % 10]--;
    }

    for (i = 0; i < n; i++)
        a[i] = output[i];
}

void sapxeptheocoso(sach* a, int n) {
    int m = getMax(a, n);

    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(a, n, exp);
}

int main() {
    int n;
    printf("Nhap so luong sach: ");
    scanf("%d", &n);
    sach books[n];
    nhapSach(books, n);
    printf("danh sach cac cuon sach da nhap:\n");
    hienthiSach(books, n);
    printf("danh sach cac cuon sach da duoc sap xep theo ma sach kieu doi cho:\n");
    sapxepdoicho(books, n);
    hienthiSach(books,n);
    printf("danh sach cac cuon sach da duoc sap xep theo ma sach kieu chon:\n");
    sapxepchon(books,n);
    hienthiSach(books,n);
    printf("danh sach cac cuon sach da duoc sap xep theo ma sach kieu chen:\n");
    sapxepchen(books,n);
    hienthiSach(books,n);
    printf("danh sach cac cuon sach da duoc sap xep theo ma sach kieu noi bot:\n");
    sapxepnoibot(books,n);
    hienthiSach(books,n);
    printf("danh sach cac cuon sach da duoc sap xep theo ma sach kieu nhanh:\n");
    sapxepnhanh(books,0,n-1);
    hienthiSach(books,n);
    printf("danh sach cac cuon sach da duoc sap xep theo ma sach kieu heap:\n");
    sapxepheap(books,n);
    hienthiSach(books,n);
    printf("danh sach cac cuon sach da duoc sap xep theo ma sach kieu shell:\n");
    sapxepshell(books,n);
    hienthiSach(books,n);
    printf("danh sach cac cuon sach da duoc sap xep theo ma sach kieu tron:\n");
    sapxeptron(books,0,n-1);
    hienthiSach(books,n);
    printf("danh sach cac cuon sach da duoc sap xep theo ma sach kieu co so:\n");
    sapxeptheocoso(books,n);
    hienthiSach(books,n);
    return 0;
}