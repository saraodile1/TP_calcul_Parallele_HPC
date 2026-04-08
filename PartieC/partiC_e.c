#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// Fonction qui élève chaque élément du tableau au carré
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
    for (int i = 0; i < n; i++)
        tableau[i] = rand() % 100;

    printf("Tableau avant carré (premiers 10 éléments) :\n");
    for (int i = 0; i < (n < 10 ? n : 10); i++)
        printf("%d ", tableau[i]);
    printf("\n");

    // Afficher le nombre de threads disponibles par défaut
    printf("Nombre de threads disponibles (max) : %d\n", omp_get_max_threads());

    // Mesurer le temps
    double start = omp_get_wtime();

    // Pour afficher le nombre réel de threads utilisés
    #pragma omp parallel
    {
        #pragma omp single
        printf("Nombre réel de threads dans la boucle : %d\n", omp_get_num_threads());
    }

    // Appel de la fonction carre (parallélisée)
    carre(tableau, n);

    double end = omp_get_wtime();
    printf("Temps écoulé : %f secondes\n", end - start);

    printf("Tableau après carré (premiers 10 éléments) :\n");
    for (int i = 0; i < (n < 10 ? n : 10); i++)
        printf("%d ", tableau[i]);
    printf("\n");

    free(tableau);
    return 0;
}

