#include <iostream>
#include <omp.h>

int main() {
    int k, N;
    printf("Введите количество нитей (k): ");
    scanf("%d", &k);
    printf("Введите (N): ");
    scanf("%d", &N);

    int sum = 0;

    #pragma omp parallel num_threads(k) reduction(+:sum)
    {
        #pragma omp for
        for (int i = 1; i <= N; ++i) {
            sum += i;
        }

        printf("[%d]: Sum = %d\n", omp_get_thread_num(), sum);
    }

    printf("Sum = %d\n", sum);

    return 0;
}
