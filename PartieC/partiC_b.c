#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Fonction qui élève chaque élément du tableau au carré
void carre(int *tableau, int n) {
    for (int i = 0; i < n; i++) {
        tableau[i] = tableau[i] * tableau[i];
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <taille_du_tableau>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);  // Lire la taille depuis la ligne de commande
    int *tableau = (int *)malloc(n * sizeof(int));
    if (!tableau) {
        printf("Erreur d'allocation mémoire !\n");
        return 1;
    }

    srand(time(NULL));  // Initialisation de la graine pour rand()

    // Remplissage du tableau avec des valeurs aléatoires
    for (int i = 0; i < n; i++) {
        tableau[i] = rand() % 100;  // Valeurs entre 0 et 99
    }

    // Affichage du tableau avant le carré
    printf("Tableau avant carré :\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", tableau[i]);
    }
    printf("\n");

    // Appel de la fonction carre
    carre(tableau, n);

    // Affichage du tableau après le carré
    printf("Tableau après carré :\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", tableau[i]);
    }
    printf("\n");

    free(tableau); // Libérer la mémoire
    return 0;
}
