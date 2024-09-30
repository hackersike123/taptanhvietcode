#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

// Hàm tìm kiếm tuyến tính
int timKiemTuyenTinh(int a[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (a[i] == x) {
            return i; // Trả về chỉ số của phần tử nếu tìm thấy
        }
    }
    return -1; // Trả về -1 nếu không tìm thấy
}

// Hàm tìm kiếm nhị phân
int timKiemNhiPhan(int a[], int l, int r, int x) {
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (a[m] == x) {
            return m; // Trả về chỉ số của phần tử nếu tìm thấy
        }
        if (a[m] < x) {
            l = m + 1; // Tìm kiếm trong nửa phải
        } else {
            r = m - 1; // Tìm kiếm trong nửa trái
        }
    }
    return -1; // Trả về -1 nếu không tìm thấy
}

// Hàm tìm kiếm nội suy
int timKiemNoiSuy(int a[], int n, int x) {
    int lo = 0, hi = n - 1;
    while (lo <= hi && x >= a[lo] && x <= a[hi]) {
        if (lo == hi) {
            if (a[lo] == x) return lo;
            return -1;
        }
        int pos = lo + (((double)(hi - lo) / (a[hi] - a[lo])) * (x - a[lo]));
        if (a[pos] == x) {
            return pos; // Trả về chỉ số của phần tử nếu tìm thấy
        }
        if (a[pos] < x) {
            lo = pos + 1; // Tìm kiếm trong nửa phải
        } else {
            hi = pos - 1; // Tìm kiếm trong nửa trái
        }
    }
    return -1; // Trả về -1 nếu không tìm thấy
}

// Hàm tìm kiếm nhảy
int timKiemNhay(int a[], int n, int x) {
    int step = sqrt(n);
    int prev = 0;
    while (a[(int)fmin(step, n) - 1] < x) { // Ép kiểu giá trị trả về của fmin thành int
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            return -1; // Trả về -1 nếu không tìm thấy
        }
    }
    for (int i = prev; i < (int)fmin(step, n); i++) { // Ép kiểu giá trị trả về của fmin thành int
        if (a[i] == x) {
            return i; // Trả về chỉ số của phần tử nếu tìm thấy
        }
    }
    return -1; // Trả về -1 nếu không tìm thấy
}

int main() {
    int n, x, luaChon;
    printf("Nhap so luong phan tu cua mang: ");
    scanf("%d", &n);
    int a[n];
    nhapMang(a, n);

    printf("Nhap gia tri can tim: ");
    scanf("%d", &x);

    printf("Chon thuat toan tim kiem:\n");
    printf("1. Tim kiem tuyen tinh\n");
    printf("2. Tim kiem nhi phan\n");
    printf("3. Tim kiem noi suy\n");
    printf("4. Tim kiem nhay\n");
    scanf("%d", &luaChon);

    int ketQua = -1;
    switch (luaChon) {
        case 1:
            ketQua = timKiemTuyenTinh(a, n, x);
            break;
        case 2:
            ketQua = timKiemNhiPhan(a, 0, n - 1, x);
            break;
        case 3:
            ketQua = timKiemNoiSuy(a, n, x);
            break;
        case 4:
            ketQua = timKiemNhay(a, n, x);
            break;
        default:
            printf("Lua chon khong hop le!\n");
            return 1;
    }

    if (ketQua != -1) {
        printf("Phan tu duoc tim thay tai chi so %d\n", ketQua);
    } else {
        printf("Phan tu khong duoc tim thay\n");
    }

    return 0;
}
