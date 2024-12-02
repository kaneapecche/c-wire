#include <stdio.h>
#include<math.h>
#include<stdlib.h>

typedef enum{
    hvb=1, hva, lv, centrale;
}Nom_station;

typedef struct{
    Nom_station id;
    int capacite;
    int somme_consommateur;
}Station;

typedef struct arbre{
    Station station;
    struct arbre* gauche;
    struct arbre* droit;
    int equilibre;
    int capacite_total;
    int conso_total;
}Arbre;

typedef struct{
    False, True;
}Bool;

//Fonctions pour la partie de l'arbre binaire equilibrer 

Arbre* creation(int r){ //creation d'un nouveau noeud dans l'arbre 
    Arbre* noeud=malloc(sizeof(Arbre));
    if(pnew==NULL){
        exit(1);
    }
    noeud->station=r;
    noeud->gauche=NULL;
    noeud->droit=NULL;
    noeud->equilibre=0;
    return noeud;
}

Bool estVide(Arbre* racine){ //verifie si l'arbre a des fils ou est vide 
    if(racine == NULL){
        return True;
    }
    return False;
}

Bool existeGauche(Arbre* racine){ //verifie si le fils gauche existe 
    if(!estVide(racine)){
        if(racine->gauche != NULL){
            return True;
        }
    }
    return False;
}

Bool existeDroit(Arbre* racine){ //verifie si le fils droit exiiste 
    if(!estVide(racine)){
        if(racine->droit!=NULL){
            return True;
        }
    }
    return False;
}

Bool estFeuille(Arbre* racine){ //verifie si c'est une feuille 
    if(!estVide(racine)){
        if(!existeDroit(racine) && !existeGauche(racine)){
            return True;
        }
    }
    return False;
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
    pivot->equilibre = min( eq_a-2, eq_a+eq_p-2, eq_p-1 )
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
    pivot->equilibre = max( eq_a+2, eq_a+eq_p+2, eq_p+1 )
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
int doublerotationdroite(Arbre* a){
    a->gauche=rotationgauche(a->gauche);
    return rotationdroite(a);
}
 
int doublerotationgauche(Arbre* a){
    a->droit=rotationdroite(a->droit);
    return rotationgauche(a);
    }


Arbre*insertionAVL (Arbre*a, Station station ,int *h){
    if (a==NULL){
    *h=1;
    retun creation(station);
    }
    else if(station <a->station){
    a->gauche=insertionAVL(a->gauche, station, &h);
    *h=-*h;
    }
    else if(station>a->station){
    a->droit=insertionAVL(a->droit, station,&h);
    }
    else{
    *h=0;
    return a;
    }
    if(*h!=0){
    a->equilbre=a->equilibre + *h;
        if(a->equilibre==0){
        *h=0;
        }
        else{
        *h=1;
        }
    }
    return a;
}

Arbre* recherche( Arbre* a, Station s){ //recherche un noeud specifique dans l'arbre 
    if(a==NULL){
        exit(2);
    }
    else if (a->station==s){
        return a;
    }
    else if (s<a->station){
        return recherche(a->gauche, s);
    }
    else{
        return recherche(a->droit, s);
    }
}

/*------

--------

--------*/

//fonctions pour le traitements des donnees 
//somme des consommations pour une station 
int somme_conso(){

}

//lecture et traitement des donnees 



//verifie l'integralite d'une ligne de donnees avant de la traiter 
/*il faut faire une fonction somme. pour cela, dans le shell on triera le fichier 
afin de juste récupérer le type de station que l'on recherche ainsi que ses 
consommateurs directe et sa capacié. dans la partie c, on va juste récupére
ses données que l'on mettra sous la forme d'un avl dont l'élément sera l'id
de la station. comme plusieurs consommateurs peuvent etre branché sur la meme
station, les identifiants se répéterons, dans ce cas la, on récupréez
simplement la capacité et la conso qu'on ajoute au noeaud deja existant.
comme c'est un avl, lorsque l'on rajoute une nouvelle station dans l'arbre
(avec un nouvel identifiant), on sera peut-etre mener a faire des rotationq,...*/





