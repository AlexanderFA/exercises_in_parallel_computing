#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int size;
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        printf("%d processes.\n", size);
    } else if (rank % 2 == 0) {
        printf("I am %d: SECOND!\n", rank);
    } else {
        printf("I am %d: FIRST!\n", rank);
    }

    MPI_Finalize();
    return 0;
}
