#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    const int ALPHABET_SIZE = 26;
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char str[100];
    int length;
    int count[ALPHABET_SIZE];
    int sums[ALPHABET_SIZE * size];
    
    if (rank == 0) {
        printf("Enter string: ");
        scanf("%s", str);
        length = strlen(str);
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            count[i] = 0;
        }
    }
    MPI_Bcast(&length, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&str, length, MPI_CHAR, 0, MPI_COMM_WORLD);

    int local_length = (int) (length / size);
    int local_count[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        local_count[i] = 0;
    }

    // Define chunks
    int end = ((rank + 1) * local_length);
    if (rank == size - 1) {
        end += length - local_length * size;
    }
    for (int i = (rank * local_length); i < end; i++) {
        // printf("I am %d process processing %d index, char %c, asci %d!\n", rank, i, str[i], (int) str[i]);
        local_count[str[i] - 'a']++;
    }

    // MPI_Barrier(MPI_COMM_WORLD);
    MPI_Reduce(&local_count, &count, ALPHABET_SIZE, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (count[i] > 0) {
                printf("%c => %d\n", i + 'a', count[i]);
            }
        }
    }

    MPI_Finalize();
    return 0;
}
