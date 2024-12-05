## Lab 1 - Hello world with multithreading
Implemented in GOlang and Clang with OpenMPI

Usage:
1. `cd lab1/lab1_go && go run main.go`
2. `g++-14 -fopenmp lab1.cpp -o whatevername && mpirun -n 1 ./whatevername` or `./whatevername`

## Lab 2 - OpenMP - public and private variables, reduction
### Distributing of sum function among threads and total summarization in public variable with use of "reduction"
Usage: `g++-14 -fopenmp lab2-5.cpp -o whatevername && ./whatevername`

## Lab 3 - Parallel computations for matrix multiplication.
### Usage of "schedule", "section"

## Lab 4 - MPI. Multiprocessing computations
### Keywords: MPI_Init, MPI_Comm_rank, MPI_Comm_size, MPI_Finalize
Usage: `mpicc -g0 -o whatever main.c && mpirun -n 10 ./whatever`
