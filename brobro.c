#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>



typedef struct arbre{
    int id_station;
    struct arbre* gauche;
    struct arbre* droit;
    int equilibre;
    int capacite_total;
    int conso_total;
}Arbre;

//Fonctions pour la partie de l'arbre binaire equilibrer 

Arbre* creation(int s){ //creation d'un nouveau noeud dans l'arbre 
    Arbre* noeud=malloc(sizeof(Arbre));
    if(noeud==NULL){
        exit(1);
    }
    noeud->id_station=s;
    noeud->gauche=NULL;
    noeud->droit=NULL;
    noeud->equilibre=0;
    noeud->capacite_total=0;
    noeud->conso_total=0;
    return noeud;
}

int estVide(Arbre* racine){ //verifie si l'arbre a des fils ou est vide 
    if(racine == NULL){
        return 1;
    }
    return 0;
}

int existeGauche(Arbre* racine){ //verifie si le fils gauche existe 
    if(!estVide(racine)){
        if(racine->gauche != NULL){
            return 1;
        }
    }
    return 0;
}

int existeDroit(Arbre* racine){ //verifie si le fils droit exiiste 
    if(!estVide(racine)){
        if(racine->droit!=NULL){
            return 1;
        }
    }
    return 0;
}

int estFeuille(Arbre* racine){ //verifie si c'est une feuille 
    if(!estVide(racine)){
        if(!existeDroit(racine) && !existeGauche(racine)){
            return 1;
        }
    }
    return 0;
}

int min(int a, int b){
   return (a<b)? a : b;
}

int max(int a, int b){
   return (a>b)? a : b;
}


Arbre* rotationgauche(Arbre* a){ //rotation a gauche en cas de desequillibrage 
    Arbre* pivot;
    int eq_a;
    int eq_p;

    pivot=a->droit;
    a->droit=pivot->gauche;
    pivot->gauche=a;
    eq_a=a->equilibre;
    eq_p=pivot->equilibre;
    a->equilibre=eq_a-max(eq_p, 0)-1;
    pivot->equilibre = min( min(eq_a-2, eq_a+eq_p-2), eq_p-1 );
    a=pivot;
    return a;

}

Arbre* rotationdroite(Arbre* a){ //rotation a droite en cas de desequillibrage
    Arbre* pivot;
    int eq_a;
    int eq_p;

    pivot=a->gauche;
    a->gauche=pivot->droit;
    pivot->droit=a;
    eq_a=a->equilibre;
    eq_p=pivot->equilibre;
    a->equilibre=eq_a-min(eq_p, 0)+1;
    pivot->equilibre = max( max(eq_a+2, eq_a+eq_p+2), eq_p+1 );
    a=pivot;
    return a;
}

int hauteur(Arbre* racine){ //retourne la hauteur de l'arbre
    if(estVide(racine)){
        exit(1);
    }
    if(estFeuille(racine)){
        return 0;
    }
    return 1 + max(hauteur(racine->gauche), hauteur(racine->droit));
}

int facteur(Arbre* racine){ //retourne le facteur d'equilibre 
    if(!estVide(racine)){
        racine->equilibre = hauteur(racine->droit) - hauteur(racine->gauche);
    }
    return racine->equilibre;
}
Arbre* doublerotationdroite(Arbre* a){
    a->gauche=rotationgauche(a->gauche);
    return rotationdroite(a);
}
 
Arbre* doublerotationgauche(Arbre* a){
    a->droit=rotationdroite(a->droit);
    return rotationgauche(a);
}


Arbre* equilibrage(Arbre *a){    //reequilibre en cas de desequillibrage
    if(a->equilibre <= 2){
        if((a->droit->equilibre) <= 0){
            return rotationgauche(a);
        }
        else{
            return doublerotationgauche(a);
        }
    }
    else if (a->equilibre <= -2){
        if((a->gauche->equilibre) <= 0){
            return rotationdroite(a);
        }
        else{
            return doublerotationdroite(a);
        }
    }
    return a; 
}

Arbre* insertionAVL (Arbre* a, int id_station ,int *h, int capa, int conso){
    if (a==NULL){
        *h=1;
        a  =  creation(id_station);
        a->capacite_total+=capa;
        a->conso_total+=conso;
        return a;
    }
    else if(id_station< a->id_station){
        a->gauche=insertionAVL(a->gauche, id_station, h, capa, conso);
        *h=-*h;
    }
    else if(id_station > a->id_station){
        a->droit=insertionAVL(a->droit, id_station, h, capa, conso);
    }
    else{
        *h=0;
        return a;
    }
    if(*h!=0){
        a->equilibre=a->equilibre + *h;
        if(a->equilibre==0){
            *h=0;
        }
        else{
            *h=1;
        }
    }
    return a;
}

/*Arbre* recherche( Arbre* a, int s){ //recherche un noeud specifique dans l'arbre 
    if(a==NULL){
        exit(2);
    }
    else if (a->id_station==s){
        return a;
    }
    else if (s<a->id_station){
        return recherche(a->gauche, s);
    }
    else{
        return recherche(a->droit, s);
    }
}*/


void verificationalloc() { // alloue la place et verifie si l'allocation ait reussi A ou sinn message d'erreur
    Arbre* pnew=malloc(sizeof(Arbre));
    if(pnew==NULL) {
        printf("erreur d'allocation\n");
        exit(10);
    }
    free(pnew);
}



void parcoursprefixe(Arbre* a){
    if(a!=NULL){
    printf("%d:%d:%d\n", a->id_station, a->capacite_total, a->conso_total);
    parcoursprefixe(a->gauche);
    parcoursprefixe(a->droit);
    }
}



int main(){
    Arbre* racine = NULL;
    int id, capa, conso;
    int h=-1;
    while(scanf("%d;%d;%d", &id, &capa, &conso)==3){
        racine=insertionAVL(racine, id, &h, capa, conso);
        //la somme est calculée dans la fonction insertionAVL
        //voir s'il est possible de fzaire la somme directment dans la fonction insertion
    }
    parcoursprefixe(racine);
    return 0;
}
