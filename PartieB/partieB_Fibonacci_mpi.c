#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

long long fibonacci(int n) {
    if(n <= 1) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

int main(int argc, char* argv[]) {
    int rank, size, n = 40;
    if(argc > 1) n = atoi(argv[1]);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    double start = MPI_Wtime();
    // Chaque processus calcule Fibonacci(n/size) approximatif
    long long partial = fibonacci(n / size);

    long long total;
    MPI_Reduce(&partial, &total, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    double end = MPI_Wtime();
    if(rank == 0) {
        printf("Temps = %f secondes\n", end - start);
        printf("Fibonacci(%d) approx = %lld\n", n, total);
    }

    MPI_Finalize();
    return 0;
}

