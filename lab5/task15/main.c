#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int size;
    int rank;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int message;

    MPI_Sendrecv(&rank, 1, MPI_INT, (rank + 1) % size, 0, &message, 1, MPI_INT, (rank - 1 + size) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("[%d]: Received message '%d'\n", rank, message);

    MPI_Finalize();
    return 0;
}
