## Lab 1 - Hello world with multithreading
Implemented in GOlang (with goroutines) and Clang with OpenMPI

Usage:
1. `cd lab1/lab1_go && go run main.go`
2. `g++-14 -fopenmp lab1.cpp -o whatevername && mpirun -n 1 ./whatevername` or just `./whatevername`
![Demonstration of go hello-world](lab1/lab1_go/helloworld_goroutines.png)

## Lab 2 - OpenMP - public and private variables, reduction
### Distributing of sum function among threads and total summarization in public variable with use of "reduction"
Usage: `g++-14 -fopenmp lab2-5.cpp -o whatevername && ./whatevername`

## Lab 3 - Parallel computing for matrix multiplication. Auto-scheduling of computing load dependency on resources availability
### Keywords% "schedule", "section"
Usage `g++-14 lab3-8.cpp -o whatevername && ./whatevername`
![Demonstration of matrix multiplication](lab3/task8/result.png)
![Check](lab3/task8/check.png)

## Lab 4 - MPI. Multiprocessing computations
### Keywords: MPI_Init, MPI_Comm_rank, MPI_Comm_size, MPI_Finalize
Usage: `mpicc -g0 -o whatever main.c && mpirun -n 10 ./whatever`
