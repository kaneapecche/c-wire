#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "AVL.h"
#include "verification.h"




int main(){
    Arbre* racine;
    FILE* f = fopen("sortie.txt", "w");
    if(f==NULL){
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
    int id, capa, conso;
    while(scanf("%d %d %d\n", &id, &capa, &conso)==3){
    	int h= hauteur(racine);
        racine=insertionAVL(racine, id, &h, capa, conso);
        //la somme est calculée dans la fonction insertionAVL
        fprintf(f, "%d %d %d\n", id, capa, conso);
        //voir s'il est possible de fzaire la somme directment dans la fonction insertion
    }
    fclose(f);
    return 0;
}
