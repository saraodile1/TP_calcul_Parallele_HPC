#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

long long fibonacci_omp(int n) {
    if (n <= 1) return n;
    if (n < 20) return fibonacci_omp(n-1) + fibonacci_omp(n-2); // cutoff
    long long x, y;
    #pragma omp task shared(x)
    x = fibonacci_omp(n-1);
    #pragma omp task shared(y)
    y = fibonacci_omp(n-2);
    #pragma omp taskwait
    return x + y;
}

int main(int argc, char* argv[]) {
    int n = 40;
    if(argc > 1) n = atoi(argv[1]);

    long long result;
    double start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        result = fibonacci_omp(n);
    }

    double end = omp_get_wtime();
    printf("Threads = %d\n", omp_get_max_threads());
    printf("Temps = %f secondes\n", end-start);
    printf("Fibonacci(%d) = %lld\n", n, result);
    return 0;
}

