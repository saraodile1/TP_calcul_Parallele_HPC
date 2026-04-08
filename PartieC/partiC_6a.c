#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// Fonction qui élève chaque élément du tableau au carré
void carre(int *tableau, int n) {
    int total = 0;

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        tableau[i] = tableau[i] * tableau[i];
        total += tableau[i];
    }

    printf("Total = %d\n", total);
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        printf("Usage: %s <taille_du_tableau> [nombre_threads]\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    // Vérifier si OMP_NUM_THREADS est défini
    char *env_threads = getenv("OMP_NUM_THREADS");

    if (env_threads != NULL) {
        printf("OMP_NUM_THREADS est défini à %s (prioritaire)\n", env_threads);
        // On ne touche pas aux threads → OpenMP utilisera cette valeur
    } else if (argc == 3) {
        int nb_threads = atoi(argv[2]);
        printf("OMP_NUM_THREADS non défini, utilisation de l'argument : %d threads\n", nb_threads);
        omp_set_num_threads(nb_threads);
    } else {
        printf("Aucun nombre de threads spécifié, utilisation par défaut\n");
    }

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

    printf("Nombre de threads disponibles (max) : %d\n", omp_get_max_threads());

    double start = omp_get_wtime();

    // Affichage du nombre réel de threads utilisés
    #pragma omp parallel
    {
        #pragma omp single
        printf("Nombre réel de threads dans la boucle : %d\n", omp_get_num_threads());
    }

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

