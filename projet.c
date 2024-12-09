#include <stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

typedef enum{
    hvb=1, hva, lv, centrale
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

/*typedef struct{
    False, True;
}Bool;*/

//Fonctions pour la partie de l'arbre binaire equilibrer 

Arbre* creation(Station s){ //creation d'un nouveau noeud dans l'arbre 
    Arbre* noeud=malloc(sizeof(Arbre));
    if(noeud==NULL){
        exit(1);
    }
    noeud->station=s;
    noeud->gauche=NULL;
    noeud->droit=NULL;
    noeud->equilibre=0;
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
    pivot->equilibre = min( eq_a-2, eq_a+eq_p-2, eq_p-1 );
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
    pivot->equilibre = max( eq_a+2, eq_a+eq_p+2, eq_p+1 );
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
int doublerotationdroite(Arbre* a){
    a->gauche=rotationgauche(a->gauche);
    return rotationdroite(a);
}
 
int doublerotationgauche(Arbre* a){
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


Arbre*insertionAVL (Arbre* a, Station station ,int *h){
    if (a==NULL){
    *h=1;
    retun creation(station);
    }
    else if(station.capacite < a->station.capacite){
    a->gauche=insertionAVL(a->gauche, station, h);
    *h=-*h;
    }
    else if(station.capacite > a->station.capacite){
    a->droit=insertionAVL(a->droit, station,h);
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
int parcoursprefixe(Arbre* a){
    if(a!=NULL){
    printf("%d", a->station.id);
    parcoursprefixe(a->gauche);
    parcoursprefixe(a->droit);
    }
}

int somme(Arbre* a, int e){
    int s=0;
    if(a != NULL){
     if(a->station.id==e){ 
         s += a->station.somme;
    }
    s += somme(a->gauche, e);
    s += somme(a->droit, e);
    
    return s;
}



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


int main(){

  int a, b, c;
    printf("Entrez trois entiers (séparés par des espaces) : ");
    scanf("%d %d %d", &a, &b, &c);

    Station s = {hvb, b, c};
    Arbre* arbre = creation(s);

    printf("Station créée : %d, Capacité : %d, Consommation : %d\n", s.id, s.capacite, s.somme_consommateur);

    return 0;
}
