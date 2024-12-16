#include "verification.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void verificationalloc() { // alloue la place et verifie si l'allocation ait reussi A ou sinn message d'erreur
	Arbre* pnew=malloc(sizeof(Arbre));
	if(pnew==NULL) {
		printf("erreur d'allocation\n");
		exit(10);
	}
	free(pnew);
}

void verificationferme(FILE* fichier) { //-ferme un fichier et verifie que l'operation a reussi C

	// Ferme le fichier et verifie si l'operation reussie
	if (fclose(fichier) != 0) {
		printf("Erreur de fermeture du fichier\n");
		exit(20);  // Arrete du programme avec un code d'erreur
	}

	// Si le fichier est ferme correctement
	printf("Fichier fermé\n");
}

 //verifie que les arguments sont valides A/ verifie que le type de station est valide /verifie lacces au fichier avant de louvrir C
void erreurs(int argc, char *argv[]) {
    // Vérifie si les arguments sont valides sinon arrete le programme
    if (argc < 4) {  
        printf("Erreur, il y a trop peu d'arguments\n");
        exit(30); 
    }
    // Vérifie que le type de station est valide
    char types_station = {"hvb", "hva", "lv"};
    int station = 0;
    for (int i = 0; i < 3; i++) {
        if (strcmp(argv[2], types_station[i]) == 0) {
            station = 1;
        }
    }

    if (!station) {
        printf("Erreur : type de station invalide\n");
        exit(40);  // Arrêt du programme avec un code d'erreur
    }

    // Vérifie l'accès au fichier avant de l'ouvrir
    FILE *fichier = fopen(argv[1], "r"); //verifie l'ouverture du fichier en lecture 
    if (fichier == NULL) {
        printf("Erreur, impossible d'ouvrir le fichier %s\n", argv[1]);
        exit(50);  // Arrêt du programme avec un code d'erreur
    }
    


    // Vérifie que le type de consommateur est valide
    if (strcmp(argv[3], "comp") != 0 && strcmp(argv[3], "indiv") != 0 && strcmp(argv[3], "all") != 0) {
        printf("Erreur : type de consommateur incorrect\n");
        exit(60);  // Arrêt du programme avec un code d'erreur
    }

    // Ferme le fichier après la vérification
    verificationferme(fichier);
}


void verification(Arbre * a){
    if(a==NULL){
        printf("Erreur");
        exit(30);
    }
}
