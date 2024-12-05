#include <stdio.h>
// #include <omp.h>
// #include <mpi.h>

int main(int argc, char *argv[]) {
    // int n = 1000000000;
    int n = 1000;
    double pi = 0;
    for (int i = 0; i < n; i++) {
        double x = (i + 0.5) / n;
        pi += 4 / (1 + x * x);
    }
    pi /= n;
    printf("%.30f\n", pi);
    return 0;
}
