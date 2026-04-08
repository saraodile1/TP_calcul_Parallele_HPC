#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>  // Inclure OpenMP

// Fonction qui élève chaque élément du tableau au carré (parallélisée)
void carre(int *tableau, int n) {
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        tableau[i] = tableau[i] * tableau[i];
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <taille_du_tableau>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    int *tableau = (int *)malloc(n * sizeof(int));
    if (!tableau) {
        printf("Erreur d'allocation mémoire !\n");
        return 1;
    }

    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        tableau[i] = rand() % 100;
    }

    printf("Tableau avant carré :\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", tableau[i]);
    }
    printf("\n");

    // Obtenir le nombre de threads disponibles avant la boucle
    printf("Nombre de threads disponibles : %d\n", omp_get_max_threads());

    // Appel de la fonction carre (parallélisée)
    carre(tableau, n);

    printf("Tableau après carré :\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", tableau[i]);
    }
    printf("\n");

    free(tableau);
    return 0;
}
