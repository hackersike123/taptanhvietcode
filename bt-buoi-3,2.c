#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // Thêm thư viện này để sử dụng INT_MIN

// Định nghĩa cấu trúc Node
struct Node {
    int soThuTu;
    char hoTen[50];
    int tuoi;
    struct Node* next;
};

// Định nghĩa cấu trúc Queue
struct Queue {
    struct Node *front, *rear;
};

// Khởi tạo Queue
void Init(struct Queue* q) {
    q->front = q->rear = NULL;
}

// Kiểm tra Queue rỗng
int isEmpty(struct Queue* q) {
    return (q->rear == NULL);
}

// Thêm bệnh nhân vào Queue
void enqueue(struct Queue* q, int soThuTu, char* hoTen, int tuoi) {
    struct Node* temp = malloc(sizeof(struct Node));
    temp->soThuTu = soThuTu;
    strcpy(temp->hoTen, hoTen);
    temp->tuoi = tuoi;
    temp->next = NULL;
    
    if (q->front == NULL)
        q->front = q->rear = temp;
    else {
        q->rear->next = temp;
        q->rear = temp;
    }
}

// Lấy bệnh nhân khỏi Queue
struct Node dequeue(struct Queue* q) {
    struct Node empty = {-1, "", -1, NULL}; // Giá trị mặc định nếu Queue rỗng
    if (isEmpty(q)) {
        return empty;
    } else {
        struct Node* temp = q->front;
        struct Node item = *temp;

        q->front = q->front->next;

        if (q->front == NULL)
            q->rear = NULL;

        free(temp);
        
        return item; // Trả về bệnh nhân đã lấy
    }
}

// Xuất danh sách bệnh nhân trong Queue
void display(struct Queue* q) {
    if (isEmpty(q)) {
        printf("Không có bệnh nhân nào trong hàng đợi.\n");
        return;
    }
    struct Node* temp = q->front;
    printf("Danh sách bệnh nhân đang chờ khám:\n");
    while (temp != NULL) {
        printf("Số thứ tự: %d, Họ tên: %s, Tuổi: %d\n", temp->soThuTu, temp->hoTen, temp->tuoi);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct Queue queue;
    Init(&queue);

    int choice;
    int sothutu = 1;
    int dakham = 0; // Biến đếm số người đã khám

    while (1) {
        printf("\nMenu:\n");
        printf("1. Thêm bệnh nhân vào hàng đợi\n");
        printf("2. Lấy bệnh nhân tiếp theo để khám\n");
        printf("3. Số lượng người đã khám\n");
        printf("4. Xuất danh sách bệnh nhân chờ khám\n");
        printf("5. Thoát\n");
        printf("Chọn chức năng: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char hoTen[50];
                int tuoi;
                printf("Nhập họ tên bệnh nhân: ");
                scanf(" %[^\n]", hoTen);
                printf("Nhập tuổi: ");
                scanf("%d", &tuoi);
                enqueue(&queue, sothutu++, hoTen, tuoi);
                printf("Thêm bệnh nhân thành công!\n");
                break;
            }
            case 2: {
                if (isEmpty(&queue)) {
                    printf("Không có bệnh nhân nào trong hàng đợi.\n");
                } else {
                    struct Node bn = dequeue(&queue);
                    printf("Bệnh nhân tiếp theo để khám:\n");
                    printf("Số thứ tự: %d, Họ tên: %s, Tuổi: %d\n", bn.soThuTu, bn.hoTen, bn.tuoi);
                    dakham++;
                }
                break;
            }
            case 3:
                printf("Số lượng người đã khám: %d\n", dakham);
                break;
            case 4:
                display(&queue);
                break;
            case 5:
                printf("Kết thúc chương trình.\n");
                exit(0);
            default:
                printf("Lựa chọn không hợp lệ. Vui lòng chọn lại.\n");
        }
    }

    return 0;
}
