#ifndef AVL_H
#include "verification.h"

typedef struct arbre{
    int id_station;
    struct arbre* gauche;
    struct arbre* droit;
    int equilibre;
    int capacite_total;
    int conso_total;
}Arbre;

Arbre* creation(int s);

int estVide(Arbre* racine);

int existeGauche(Arbre* racine);

int existeDroit(Arbre* racine);

int estFeuille(Arbre* racine);

Arbre* rotationgauche(Arbre* a);

Arbre* rotationdroite(Arbre* a);

int hauteur(Arbre* racine);

int facteur(Arbre* racine);

int doublerotationdroite(Arbre* a);

int doublerotationgauche(Arbre* a);

Arbre* equilibrage(Arbre *a);

Arbre*insertionAVL (Arbre* a, int id_station ,int *h, int capa, int conso);

#endif

Arbre* recherche( Arbre* a, int s);

