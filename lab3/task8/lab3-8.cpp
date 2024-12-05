#include <omp.h>
#include <stdio.h>

#define N 10

int main() {
    int n;
    printf("Введите размер квадратной матрицы от 1 до 10: ");
    scanf("%d", &n);

    if (n <= 0 || n > N) {
        printf("Неверный размер.\n");
        return 1;
    }

    double A[N][N], B[N][N], C[N][N];
    int i, j, k;

    printf("Введите элементы матрицы A:\n");
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            scanf("%lf", &A[i][j]);
        }
    }

    printf("Введите элементы матрицы B:\n");
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            scanf("%lf", &B[i][j]);
        }
    }

    #pragma omp parallel for shared(A, B, C) private(i, j, k)
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            C[i][j] = 0.0;
            for (k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    printf("Result matrix C:\n");
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            printf("%.2f ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
