#include <stdio.h>

// 函数原型声明
void quicksort(int A[], int p, int r);
int partition(int A[], int p, int r);
void exchange(int* a, int* b);
void printArray(int A[], int n);

int main() {
    int A[] = {9, 7, 5, 11, 12, 2, 14, 3, 10, 6};
    int n = sizeof(A) / sizeof(A[0]);

    printf("\nThe unsorted array A is:\n");
    printArray(A, n);

    quicksort(A, 0, n - 1);

    printf("\nThe sorted array A is:\n");
    printArray(A, n);
    printf("\n");

    return 0;
}

// 快速排序函数
void quicksort(int A[], int p, int r) {
    if (p < r) {
        int q = partition(A, p, r);
        printf("The sorted array with pivot A[%d] = %d in quicksort(A, %d, %d)is:\n", q, A[q], p, r);
        printArray(A, 10);
        quicksort(A, p, q - 1);
        quicksort(A, q + 1, r);
    }
}

// 分区函数
int partition(int A[], int p, int r) {
    int x = A[r]; //pivot
    int count = p - 1;
    for (int i = p; i < r; i++) {
        if (A[i] <= x) {
            count++;
            exchange(&A[count], &A[i]); // 交换A[i]和A[j]
        }
    }
    exchange(&A[count + 1], &A[r]); // 将基准值交换到正确的位置
    return count + 1;
}

// 交换两个整数的函数
void exchange(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int A[], int n){
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}
