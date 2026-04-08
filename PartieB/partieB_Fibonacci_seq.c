#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long fibonacci_seq(int n) {
    if (n <= 1) return n;
    return fibonacci_seq(n-1) + fibonacci_seq(n-2);
}

int main(int argc, char* argv[]) {
    int n = 40; // exemple
    if(argc > 1) n = atoi(argv[1]);
    clock_t start = clock();
    printf("Fibonacci(%d) = %lld\n", n, fibonacci_seq(n));
    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Temps = %f secondes\n", time_taken);

    return 0;
}

