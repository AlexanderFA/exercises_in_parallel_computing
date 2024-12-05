#include <omp.h>
#include <iostream>

int main() {
    #pragma omp parallel num_threads(10)
    {
        int id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
	if (id % 2 == 0) {
	        #pragma omp critical
        	std::cout << "I am " << id << " thread from " << num_threads << " threads!" << std::endl;
	}
    }
    return 0;
}
