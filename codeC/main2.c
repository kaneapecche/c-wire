#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"

int main() {

// Appeler le script shell
    int result = system("./info1.sh");

    if (result == -1) {
        printf("Erreur lors de l'exécution du script\n");
        return 1;  // Retourner une erreur si le script échoue
    } else {
        printf("Script exécuté avec succès\n");
    }


    Arbre* racine = NULL;
    FILE* sortie = fopen("sortie.txt", "w");
    if (sortie == NULL) {
        exit(1);
    }

    int id;
    long int capa, conso;
    int h = -1;

    while (scanf("%d:%ld:%ld\n", &id, &capa, &conso) == 3) {
        racine = insertionAVL(racine, id, &h, capa, conso);
    }

    parcoursprefixe(racine, sortie);
    fclose(sortie);
    return 0;
}
