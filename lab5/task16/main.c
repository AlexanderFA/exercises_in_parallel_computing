#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int size;
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int message[size];

    for (int i = 0; i < size; i++) {
        if (i != rank) {
            MPI_Send(&rank, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }

    for (int i = 0; i < size; i++) {
        if (i != rank) {
            MPI_Recv(&message[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("[%d]: Received message '%d' from %d\n", rank, message[i], i);
        }
    }

    MPI_Finalize();
    return 0;
}
