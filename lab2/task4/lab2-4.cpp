#include <omp.h>
#include <iostream>

int main() {
    int rank; // Объявляем переменную rank
    int k;
    std::cout << "Enter the number of threads: ";
    std::cin >> k;

    #pragma omp parallel num_threads(k) private(rank)
    {
        rank = omp_get_thread_num();
        #pragma omp critical
        {
            std::cout << "I am " << rank << " thread." << std::endl;
        }
    }

    return 0;
}
