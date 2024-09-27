#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

#define T 100

// Fonction pour déterminer si un nombre est premier
int is_prime(int n) {
    if (n <= 1) return 0;       // Les nombres <= 1 ne sont pas premiers
    if (n <= 3) return 1;       // 2 et 3 sont premiers
    if (n % 2 == 0 || n % 3 == 0) return 0; // Les multiples de 2 et 3 ne sont pas premiers
    
    // Vérification des multiples de 6 pour optimisation
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}

// Fonction exécutée par chaque processus travailleur
void worker(int read_fd, int write_fd, int id) {
    int start, end, num;

    while (1) {
        // Lecture des bornes de l'intervalle à tester
        if (read(read_fd, &start, sizeof(int)) <= 0 || read(read_fd, &end, sizeof(int)) <= 0) {
            break;
        }

        // Condition de fin pour le travailleur
        if (start == 0 && end == 0) {
            break;
        }

        // Test des nombres dans l'intervalle et envoi des nombres premiers trouvés
        for (int i = start; i <= end; ++i) {
            if (is_prime(i)) {
                num = i;
                write(write_fd, &id, sizeof(int));
                write(write_fd, &num, sizeof(int));
            }
        }
        
        // Condition de fin pour le travailleur
        if (start == 0 && end == 0) {
            break;
        }
    }
    // Fermeture des descripteurs de fichiers et sortie du processus
    close(read_fd);
    close(write_fd);
    exit(EXIT_SUCCESS);
}

int main() {
    int N, p;
    p=-1;
    N=-1;
    printf("============================\nEntrez la taille N : \n");
    scanf("%d", &N);
    printf("============================\nEntrez le nombre de processus p : \n");
    scanf("%d", &p);
    while (N<=0 || p<=0){
        if (N<=0){
            printf("N doit être supérieur à 0\n");
            printf("============================\nEntrez la taille N : \n");
            scanf("%d", &N);
        }
        if (p<=0){
            printf("p doit être supérieur à 0\n");
            printf("============================\nEntrez le nombre de processus p : \n");
            scanf("%d", &p);
        }
    }


    // Initialisation des tubes
    int master_to_worker[p][2];
    int worker_to_master[p][2];

    // Création des tubes pour la communication entre le processus maître et les travailleurs
    for (int i = 0; i < p; ++i) {
        if (pipe(master_to_worker[i]) == -1 || pipe(worker_to_master[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    // Création des processus travailleurs
    for (int i = 0; i < p; ++i) {
        if (fork() == 0) {
            // Ferme les l'écriture et lecture pour éviter des erreurs 
            close(master_to_worker[i][1]);
            close(worker_to_master[i][0]);

            worker(master_to_worker[i][0], worker_to_master[i][1], i);
        } else {
            // Fermes les tubes 
            close(master_to_worker[i][0]);
            close(worker_to_master[i][1]);
        }
    }

    // Répartition des intervalles de travail entre les travailleurs
    int interval_size = N / p;
    int start, end;

    for (int i = 0; i < p; ++i) {
        start = i * interval_size + 1;
        end = (i == p - 1) ? N : start + interval_size - 1;

        if (write(master_to_worker[i][1], &start, sizeof(int)) == -1 || 
            write(master_to_worker[i][1], &end, sizeof(int)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    // Envoi des signaux de fin de travail aux travailleurs
    for (int i = 0; i < p; ++i) {
        start = end = 0;
        // Ecriture dans le tube
        if (write(master_to_worker[i][1], &start, sizeof(int)) == -1 || 
            write(master_to_worker[i][1], &end, sizeof(int)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    // Lecture des résultats des travailleurs et affichage des nombres premiers trouvés
    for (int i = 0; i < p; ++i) {
        int id, num;
        while (1) {
            // Lecture du résultats dans le tube
            if (read(worker_to_master[i][0], &id, sizeof(int)) <= 0 || read(worker_to_master[i][0], &num, sizeof(int)) <= 0) {
                break;
            }
            // Afficher les resultats 
            if (num != 0) {
                printf("Travailleur %d a trouvé le nombre premier : %d\n", id, num);
            } else {
                break;
            }
        }
    }

    // Attente de la fin de tous les processus travailleurs
    for (int i = 0; i < p; ++i) {
        wait(NULL);
    }

    return 0;
}
