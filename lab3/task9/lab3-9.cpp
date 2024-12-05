#include <omp.h>
#include <stdio.h>

int main() {
    int k;
    printf("Введите количество нитей: ");
    scanf("%d", &k);

    #pragma omp parallel num_threads(k)
    {
        int thread_num = omp_get_thread_num();
        printf("[%d]: parallel region\n", thread_num);

        #pragma omp sections
        {
            #pragma omp section
            {
                printf("[%d]: came in section 1\n", thread_num);
            }

            #pragma omp section
            {
                printf("[%d]: came in section 2\n", thread_num);
            }

            #pragma omp section
            {
                printf("[%d]: came in section 3\n", thread_num);
            }
        }
    }

    return 0;
}
