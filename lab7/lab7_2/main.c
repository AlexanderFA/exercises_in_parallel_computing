#include <stdio.h>
#include <omp.h>
#include <mpi.h>

// #define n 1000

int main(int argc, char *argv[]) {
    int pid, size, n_threads, n;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (pid == 0) {
        printf("Enter the number of threads: ");
        scanf("%d", &n_threads);
        printf("Enter N: ");
        scanf("%d", &n);
    }
    MPI_Bcast(&n_threads, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    omp_set_num_threads(n_threads);

    double pid_pi = 0;

    int local_length = (int) (n / size);
    int end = ((pid + 1) * local_length);
    if (pid == size - 1) {
        end += n % local_length;
    }

    #pragma omp parallel reduction(+:pid_pi)
    {
        int tid = omp_get_thread_num();
        double tid_pi = 0;
        
        #pragma omp for
        for (int j = (pid * local_length); j < end; j++) {
            double x = (j + 0.5) / n;
            pid_pi += 4 / (1 + x * x);
        }
    }

    double total_pi = 0.0;
    MPI_Reduce(&pid_pi, &total_pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (pid == 0) {
        total_pi /= n;
        printf("Estimated pi value: %.30f\n", total_pi);
    }

    MPI_Finalize();
    return 0;
}
