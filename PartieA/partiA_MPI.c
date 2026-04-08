#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int rank, size;
    int N; // taille du tableau
    int partial_sum = 0, total_sum = 0;
    int chunk;

    double start, end;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Le master récupère la taille du tableau
    if (rank == 0) {
        if (argc < 2) {
            printf("Usage: mpirun -np <num_procs> ./partiA_MPI <taille_tableau>\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        N = atoi(argv[1]);
    }

    // Partager la taille du tableau avec tous les processus
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    chunk = N / (size - 1); // taille du morceau pour chaque worker

    // Synchronisation
    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();

    if (rank == 0) {
        // MASTER
        int* data = (int*)malloc(N * sizeof(int));
        for (int i = 0; i < N; i++) {
            data[i] = i + 1; // remplir le tableau
        }

        printf("MASTER: distribution des données...\n");

        for (int i = 1; i < size; i++) {
            MPI_Send(&data[(i-1)*chunk], chunk, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        for (int i = 1; i < size; i++) {
            MPI_Recv(&partial_sum, 1, MPI_INT, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("MASTER: reçu somme partielle de P%d = %d\n", i, partial_sum);
            total_sum += partial_sum;
        }

        printf("MASTER: Somme totale = %d\n", total_sum);
        free(data);
    }
    else {
        // WORKERS
        int* local_data = (int*)malloc(chunk * sizeof(int));

        MPI_Recv(local_data, chunk, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        partial_sum = 0;
        for (int i = 0; i < chunk; i++) {
            partial_sum += local_data[i];
        }

        printf("WORKER P%d: somme partielle = %d\n", rank, partial_sum);

        MPI_Send(&partial_sum, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
        free(local_data);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();

    // Seul le master affiche le temps
    if (rank == 0) {
        printf("Temps d'exécution = %f secondes\n", end - start);
    }

    MPI_Finalize();
    return 0;
}

