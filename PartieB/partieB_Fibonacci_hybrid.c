#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <mpi.h>

long long fibonacci_hybrid(int n) {
    if(n <= 1) return n;
    long long x, y;
    #pragma omp task shared(x)
    x = fibonacci_hybrid(n-1);
    #pragma omp task shared(y)
    y = fibonacci_hybrid(n-2);
    #pragma omp taskwait
    return x + y;
}

int main(int argc, char* argv[]) {
    int rank, size, n = 40;
    if(argc > 1) n = atoi(argv[1]);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long long partial;
    #pragma omp parallel
    {
        #pragma omp single
        partial = fibonacci_hybrid(n / size);
    }

    long long total;
    MPI_Reduce(&partial, &total, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0) {
        printf("Fibonacci(%d) approx = %lld\n", n, total);
    }

    MPI_Finalize();
    return 0;
}

