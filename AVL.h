typedef struct arbre{
    int id_station;
    struct arbre* gauche;
    struct arbre* droit;
    int equilibre;
    int capacite_total;
    int conso_total;
}Arbre;

