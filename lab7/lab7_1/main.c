#include <stdio.h>
#include <omp.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, n_threads;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter the number of threads: ");
        scanf("%d", &n_threads);
    }
    MPI_Bcast(&n_threads, 1, MPI_INT, 0, MPI_COMM_WORLD);

    omp_set_num_threads(n_threads);

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        printf("I am %d thread from %d process. Number of hybrid threads = %d\n", tid, rank, n_threads * size);
    }

    MPI_Finalize();
    return 0;
}
