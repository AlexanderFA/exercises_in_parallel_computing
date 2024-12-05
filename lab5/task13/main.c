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

    if (rank == 0) {
        message = rank;
        MPI_Send(&message, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
        printf("[%d]: Sent message '%d'\n", rank, message);
    } else {
        MPI_Recv(&message, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
        printf("[%d]: Received message '%d'\n", rank, message);

        message++;

        MPI_Send(&message, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
        printf("[%d]: Sent message '%d'\n", rank, message);
    }

    MPI_Finalize();
    return 0;
}
