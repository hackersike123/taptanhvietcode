#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct INFO
{
    char ma[50];
    char hoten[50];
    int ngay;
    int thang;
    int nam;
    float toan;
    float ly;
    float hoa;
};

INFO nhap(FILE *write)
{
    INFO sv;

    printf("Nhap ma sinh vien: ");
    scanf("%s", sv.ma);
    getchar();
    fprintf(write, "Ma sinh vien: %s\n", sv.ma);

    printf("Nhap ho ten: ");
    fgets(sv.hoten, 50, stdin);
    sv.hoten[strcspn(sv.hoten, "\n")] = 0;
    fprintf(write, "Ho va ten sinh vien: %s\n", sv.hoten);

    printf("Nhap ngay thang nam sinh: ");
    scanf("%d%d%d", &sv.ngay, &sv.thang, &sv.nam);
    getchar();
    fprintf(write, "Ngay sinh: %d/%d/%d\n", sv.ngay, sv.thang, sv.nam);

    printf("Nhap diem toan: ");
    scanf("%f", &sv.toan);
    getchar();
    fprintf(write, "Diem toan: %.2f\n", sv.toan);

    printf("Nhap diem ly: ");
    scanf("%f", &sv.ly);
    getchar();
    fprintf(write, "Diem ly: %.2f\n", sv.ly);

    printf("Nhap diem hoa: ");
    scanf("%f", &sv.hoa);
    getchar();
    fprintf(write, "Diem hoa: %.2f\n", sv.hoa);

    return sv;
}

int countAverage(INFO ds[], int n)
{
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        float avg = (ds[i].toan + ds[i].ly + ds[i].hoa) / 3;
        if (avg > 5 && ds[i].toan > 3 && ds[i].ly > 3 && ds[i].hoa > 3)
        {
            count++;
        }
    }

    return count;
}

INFO findMaxAge(INFO ds[], int n)
{
    INFO result = ds[0];
    int min_year = ds[0].nam;

    for (int i = 1; i < n; i++)
    {
        if (ds[i].nam < min_year)
        {
            min_year = ds[i].nam;
            result = ds[i];
        }
    }

    return result;
}

float calculateAverage(INFO sv)
{
    return (sv.toan + sv.ly + sv.hoa) / 3.0;
}

INFO findHighestAvgScore(INFO ds[], int n, int currentIndex, INFO currentHighest)
{
    if (currentIndex == n)
    {
        return currentHighest;
    }

    float currentAvg = calculateAverage(ds[currentIndex]);
    float highestAvg = calculateAverage(currentHighest);

    if (currentAvg > highestAvg)
    {
        currentHighest = ds[currentIndex];
    }

    return findHighestAvgScore(ds, n, currentIndex + 1, currentHighest);
}

void findSv(INFO ds[], int n)
{
    char x[100];
    printf("Nhap ten sinh vien can tim: ");
    fgets(x, 100, stdin);
    x[strcspn(x, "\n")] = 0;

    for (int i = 0; i < n; i++)
    {
        if (strcmp(ds[i].hoten, x) == 0)
        {
            printf("\nThong tin cua sinh vien can tim:\n");
            printf("Ma sinh vien: %s\n", ds[i].ma);
            printf("Ho ten: %s\n", ds[i].hoten);
            printf("Nam sinh: %d/%d/%d\n", ds[i].ngay, ds[i].thang, ds[i].nam);
            printf("Diem toan, ly, hoa lan luot la: %.2f - %.2f - %.2f\n", ds[i].toan, ds[i].ly, ds[i].hoa);

            return;
        }
    }

    printf("Khong tim thay sinh vien\n");
}

void sortByAvgScore(INFO ds[], int n)
{
    int i, j;
    INFO key;
    for (i = 1; i < n; i++)
    {
        key = ds[i];
        j = i - 1;

        while (j >= 0 && calculateAverage(ds[j]) > calculateAverage(key))
        {
            ds[j + 1] = ds[j];
            j = j - 1;
        }
        ds[j + 1] = key;
    }
}

void printSortedList(INFO ds[], int n)
{
    printf("\nDanh sach sinh vien sau khi sap xep theo diem trung binh tang dan:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s - Diem trung binh: %.2f\n", ds[i].hoten, calculateAverage(ds[i]));
    }
}

void insertNewStudent(INFO ds[], int *n)
{
    INFO newStudent = nhap(stdout);

    int i = *n - 1;
    while (i >= 0 && calculateAverage(ds[i]) > calculateAverage(newStudent))
    {
        ds[i + 1] = ds[i];
        i--;
    }

    ds[i + 1] = newStudent;
    (*n)++;
}

void writeToFile(INFO ds[], int n, const char *filename)
{
    FILE *out = fopen(filename, "w");
    if (out == NULL)
    {
        printf("Error opening output file\n");
        return;
    }

    fprintf(out, "Danh sach sinh vien sau khi them va sap xep:\n");
    for (int i = 0; i < n; i++)
    {
        fprintf(out, "%s - Diem trung binh: %.2f\n", ds[i].hoten, calculateAverage(ds[i]));
    }

    fclose(out);
}

int main()
{
    INFO ds[100];
    FILE *write = fopen("dssv.inp", "w");

    if (write == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    int n;
    printf("Nhap so luong sinh vien: ");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++)
    {
        printf("Nhap thong tin cua sinh vien thu %d:\n", i + 1);
        fprintf(write, "Thong tin cua sinh vien thu %d\n", i + 1);
        ds[i] = nhap(write);
        printf("\n");
        fprintf(write, "\n");
    }
    fclose(write);

    int avg = countAverage(ds, n);
    printf("Co %d sinh vien co diem trung binh lon hon 5 va khong co mon nao duoi 3\n", avg);

    INFO ans = findMaxAge(ds, n);
    printf("Ten cua nguoi co so tuoi lon nhat la: %s\n", ans.hoten);

    INFO highestAvgStudent = findHighestAvgScore(ds, n, 0, ds[0]);
    printf("Sinh vien co diem trung binh cao nhat la: %s\n", highestAvgStudent.hoten);
    printf("Diem trung binh: %.2f\n", calculateAverage(highestAvgStudent));

    findSv(ds, n);

    sortByAvgScore(ds, n);
    printSortedList(ds, n);

    printf("\nThem mot sinh vien moi:\n");
    insertNewStudent(ds, &n);

    printf("\nDanh sach sau khi them sinh vien moi:\n");
    printSortedList(ds, n);

    writeToFile(ds, n, "dssv.out");

    return 0;
}