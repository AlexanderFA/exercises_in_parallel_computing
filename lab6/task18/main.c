#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define SEED 35791246

int main(int argc, char *argv[]) {
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int decimals, n;
    if (rank == 0) {
        printf("Enter the number of decimals: ");
        scanf("%d", &decimals);
        n = (int) pow(10, decimals);
    }

    MPI_Bcast(&decimals, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int points_per_process = n / size;
    int count = 0;
    double x, y;

    srand(SEED + rank);
    for (int i = 0; i < points_per_process; i++) {
        x = (double) rand() / RAND_MAX;
        y = (double) rand() / RAND_MAX;
        if (x * x + y * y <= 1.0) {
            count++;
        }
    }

    int total_count = 0;
    MPI_Reduce(&count, &total_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double pi = 4.0 * total_count / n;
        printf("Estimated pi value: %.*f\n", decimals, pi);
    }

    MPI_Finalize();
    return 0;
}
