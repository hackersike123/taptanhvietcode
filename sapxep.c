#include <stdio.h>
#include <stdlib.h>

// Hàm nhập mảng
void nhapMang(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Nhap phan tu thu %d: ", i + 1);
        scanf("%d", &a[i]);
    }
}

// Hàm xuất mảng
void xuatMang(int a[], int n) {
    for (int j = 0; j < n; j++) {
        printf("%d\t", a[j]);
    }
    printf("\n");
}

// Hàm sắp xếp nổi bọt
void sapXepNoiBot(int a[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (a[j] > a[j+1]) {
                int temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}

// Hàm sắp xếp chọn
void sapXepChon(int a[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            if (a[j] < a[min_idx]) {
                min_idx = j;
            }
        }
        int temp = a[min_idx];
        a[min_idx] = a[i];
        a[i] = temp;
    }
}

// Hàm sắp xếp chèn
void sapXepChen(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = key;
    }
}

// Hàm sắp xếp nhanh
void hoanDoi(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int phanHoach(int a[], int low, int high) {
    int pivot = a[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (a[j] < pivot) {
            i++;
            hoanDoi(&a[i], &a[j]);
        }
    }
    hoanDoi(&a[i + 1], &a[high]);
    return (i + 1);
}

void sapXepNhanh(int a[], int low, int high) {
    if (low < high) {
        int pi = phanHoach(a, low, high);
        sapXepNhanh(a, low, pi - 1);
        sapXepNhanh(a, pi + 1, high);
    }
}

int main() {
    int n, luaChon;
    printf("Nhap so luong phan tu cua mang: ");
    scanf("%d", &n);
    int a[n];
    nhapMang(a, n);

    printf("Chon thuat toan sap xep:\n");
    printf("1. Sap xep noi bot\n");
    printf("2. Sap xep chon\n");
    printf("3. Sap xep chen\n");
    printf("4. Sap xep nhanh\n");
    scanf("%d", &luaChon);

    switch (luaChon) {
        case 1:
            sapXepNoiBot(a, n);
            break;
        case 2:
            sapXepChon(a, n);
            break;
        case 3:
            sapXepChen(a, n);
            break;
        case 4:
            sapXepNhanh(a, 0, n - 1);
            break;
        default:
            printf("Lua chon khong hop le!\n");
            return 1;
    }

    printf("Mang sau khi sap xep:\n");
    xuatMang(a, n);

    return 0;
}
