#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "AVL.h"

int main(){
    Arbre* racine = NULL;
    FILE* sortie = fopen("sortie.txt","w");
    if(sortie==NULL){
        exit(1);
    }
    int id;
    long int capa, conso;
    int h=-1;
    while(scanf("%d:%ld:%ld\n", &id, &capa, &conso)==3){
        racine=insertionAVL(racine, id, &h, capa, conso);
        //la somme est calculée dans la fonction insertionAVL
        //voir s'il est possible de fzaire la somme directment dans la fonction insertion
    }
    parcoursprefixe(racine, sortie);
    return 0;
}
