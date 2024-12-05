#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char str[100];
    int length;
    int count[26];
    int sums[26 * size];

    if (rank == 0) {
        printf("Enter string: ");
        scanf("%s", str);
        length = strlen(str);
        for (int i = 0; i < 26; i++) {
            count[i] = 0;
        }
    }
    MPI_Bcast(&length, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&str, length, MPI_CHAR, 0, MPI_COMM_WORLD);

    int local_length = (int) (length / size);
    int local_count[26];
    for (int i = 0; i < 26; i++) {
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
        // count[str[i] - 'a']++;
    }
    // for (int i = 0; i < 26; i++) {
    //     if (local_count[i] > 0) {
    //         printf("%c => %d, asci %d\n", i + 'a', local_count[i], i + 'a');
    //     }
    // }
    // MPI_Barrier(MPI_COMM_WORLD);

    // MPI_Gather(&local_count, 26, MPI_INT, &sums, 26 , MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_count, &count, 26, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    // printf("size %lu\n", sizeof(sums) / sizeof(sums[0]));
    
    if (rank == 0) {
        // for (int i = 0; i < 26 * size; i++) {
        //     printf("%d => %d; ", i, sums[i]);
        //     if ((i + 1) % 13 == 0) {
        //         printf("\n");
        //     }
        // }
        // printf("\n");
        for (int i = 0; i < 26; i++) {
            if (count[i] > 0) {
                printf("%c => %d\n", i + 'a', count[i]);
            }
        }
    }

    MPI_Finalize();
    return 0;
}
