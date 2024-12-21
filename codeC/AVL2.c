#include "AVL.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Arbre* creation(int s) {
    Arbre* noeud = malloc(sizeof(Arbre));
    if (noeud == NULL) {
        exit(1);
    }
    noeud->id_station = s;
    noeud->gauche = NULL;
    noeud->droit = NULL;
    noeud->equilibre = 0;
    noeud->capacite_total = 0;
    noeud->conso_total = 0;
    free(noeud);
    return noeud;
}

int estVide(Arbre* racine) {
    return (racine == NULL);
}

int existeGauche(Arbre* racine) {
    return (racine != NULL && racine->gauche != NULL);
}

int existeDroit(Arbre* racine) {
    return (racine != NULL && racine->droit != NULL);
}

int estFeuille(Arbre* racine) {
    return (racine != NULL && !existeDroit(racine) && !existeGauche(racine));
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Arbre* rotationgauche(Arbre* a) {
    Arbre* pivot;
    pivot = a->droit;
    a->droit = pivot->gauche;
    pivot->gauche = a;
    a->equilibre = a->equilibre - max(pivot->equilibre, 0) - 1;
    pivot->equilibre = min(min(a->equilibre - 2, a->equilibre + pivot->equilibre - 2), pivot->equilibre - 1);
    return pivot;
}

Arbre* rotationdroite(Arbre* a) {
    Arbre* pivot;
    pivot = a->gauche;
    a->gauche = pivot->droit;
    pivot->droit = a;
    a->equilibre = a->equilibre - min(pivot->equilibre, 0) + 1;
    pivot->equilibre = max(max(a->equilibre + 2, a->equilibre + pivot->equilibre + 2), pivot->equilibre + 1);
    return pivot;
}

int hauteur(Arbre* racine) {
    if (estVide(racine)) {
        return -1;
    }
    if (estFeuille(racine)) {
        return 0;
    }
    return 1 + max(hauteur(racine->gauche), hauteur(racine->droit));
}

int facteur(Arbre* racine) {
    if (racine != NULL) {
        racine->equilibre = hauteur(racine->droit) - hauteur(racine->gauche);
    }
    return racine->equilibre;
}

Arbre* doublerotationdroite(Arbre* a) {
    a->gauche = rotationgauche(a->gauche);
    return rotationdroite(a);
}

Arbre* doublerotationgauche(Arbre* a) {
    a->droit = rotationdroite(a->droit);
    return rotationgauche(a);
}

Arbre* equilibrage(Arbre* a) {
    if (a->equilibre <= 2) {
        if (a->droit->equilibre <= 0) {
            return rotationgauche(a);
        } else {
            return doublerotationgauche(a);
        }
    } else if (a->equilibre <= -2) {
        if (a->gauche->equilibre <= 0) {
            return rotationdroite(a);
        } else {
            return doublerotationdroite(a);
        }
    }
    return a;
}

Arbre* insertionAVL(Arbre* a, int id_station, int* h, long int capa, long int conso) {
    if (a == NULL) {
        *h = 1;
        a = creation(id_station);
        a->capacite_total += capa;
        a->conso_total += conso;
        return a;
    } else if (id_station == a->id_station) {
        a->capacite_total += capa;
        a->conso_total += conso;
        return a;
    } else if (id_station < a->id_station) {
        a->gauche = insertionAVL(a->gauche, id_station, h, capa, conso);
        *h = -(*h);
    } else if (id_station > a->id_station) {
        a->droit = insertionAVL(a->droit, id_station, h, capa, conso);
    } else {
        *h = 0;
        return a;
    }

    if (*h != 0) {
        a->equilibre += *h;
        if (a->equilibre == 0) {
            *h = 0;
        } else {
            *h = 1;
        }
    }
    return a;
}

void verificationalloc() {
    Arbre* pnew = malloc(sizeof(Arbre));
    if (pnew == NULL) {
        printf("Erreur d'allocation\n");
        exit(10);
    }
    free(pnew);
}

void parcoursprefixe(Arbre* a, FILE* fichier) {
    if (a != NULL) {
        fprintf(fichier, "%d:%ld:%ld\n", a->id_station, a->capacite_total, a->conso_total);
        parcoursprefixe(a->gauche, fichier);
        parcoursprefixe(a->droit, fichier);
    }
}
