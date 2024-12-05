#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n;
    if (rank == 0) {
        printf("Enter the value of n (1 ≤ n ≤ 10): ");
        scanf("%d", &n);
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int total_elements = n * n;
    double *A = (double *)malloc(total_elements * sizeof(double));
    double *B = (double *)malloc(total_elements * sizeof(double));
    double *C = (double *)malloc(total_elements * sizeof(double));

    if (rank == 0) {
        printf("Enter the elements of matrix A:\n");
        for (int i = 0; i < total_elements; ++i) {
            scanf("%lf", &A[i]);
        }
        printf("Enter the elements of matrix B:\n");
        for (int i = 0; i < total_elements; ++i) {
            scanf("%lf", &B[i]);
        }
    }

    // MPI_Bcast(A, total_elements, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(B, total_elements, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    int local_n = total_elements / size;
    if (local_n % n > 0) {
        local_n += 1;
    }
    double *local_A = (double *)malloc(local_n * sizeof(double));
    // double *local_B = (double *)malloc(local_n * sizeof(double));
    double *local_C = (double *)malloc(local_n * sizeof(double));

    MPI_Scatter(A, local_n, MPI_DOUBLE, local_A, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    // MPI_Scatter(B, local_n, MPI_DOUBLE, local_B, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // 1 3    5 4     14 1*4 + 3*0 = 4     A[0] * B[0] + A[1] * B[2];
    // 4 8    3 0     44 4*4 + 8*0 = 16    A[0] * B[1] + A[1] * B[3];
    //                                     A[2] * B[0] + A[3] * B[2];
    //                                     A[2] * B[1] + A[3] * B[3];
    for (int i = 0; i < local_n; i++) {
        local_C[i] = 0.0;
        for (int j = 0; j < n; j++) {
            local_C[i] += local_A[(int) (i/n) * n + j] * B[j * n + (i % n)];
        }
    }

    // MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gather(local_C, local_n, MPI_DOUBLE, C, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        printf("Result:\n");
        for (int i = 0; i < total_elements; ++i) {
            printf("%.2f ", C[i]);
            if ((i + 1) % n == 0) {
                printf("\n");
            }
        }
    }

    free(A);
    free(B);
    free(C);
    free(local_A);
    // free(local_B);
    free(local_C);

    MPI_Finalize();
    return 0;
}
