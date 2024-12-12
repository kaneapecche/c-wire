
#!/bin/bash

# Vérifier si un argument est passé
if [ "$#" -ne 1 ]; then //représente le nb d'arguments passé au script 
    echo "Usage: $0 {comp|indiv|all}" // correspond au nom du programme a exécuté
    exit 1
fi

# Lire l'argument (comp, indiv, all)
categorie=$1
total=0

# Vérifier si la catégorie est valide
if [[ ! "$categorie" =~ ^(comp|indiv|all)$ ]]; then
    echo "Catégorie invalide. Utilisez 'comp', 'indiv' ou 'all'."
    exit 2
fi

# Lire le fichier des consommateurs
while read -r ligne; do
    # Extraire la catégorie et la valeur
    categorie_ligne=$(echo "$ligne" | awk '{print $1}')
    value=$(echo "$ligne" | awk '{print $2}') // awk sert a extraire une partie spécifique de chaque ligne 

    # Ajouter la valeur selon la catégorie demandée
    if [ "$categorie" == "all" ] || [ "$categorie" == "$categorie_ligne" ]; then
        total=$((total + value))
    fi
done < consommateurs.txt

# Afficher la somme
echo "La somme des consommateurs pour la catégorie '$categorie' est : $total"




