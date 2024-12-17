#!/bin/bash

# Vérifier si le bon nombre d'arguments est passé
if [ "$#" -ne 3 ]; then
  echo "Usage: $0 <fichier_d_entree> <type_de_station> <type_de_consommateur>"
  exit 1
fi

# Récupérer les arguments
INPUT_FILE="$1"
STATION_TYPE="$2"
CONSUMER_TYPE="$3"

# Vérifier que le fichier d'entrée existe
if [ ! -f "$INPUT_FILE" ]; then
  echo "Le fichier $INPUT_FILE n'existe pas."
  exit 1
fi

# Déterminer le type de station en fonction de l'argument
case $STATION_TYPE in
  "hva") STATION_COLUMN="HV-A Station";;
  "hvb") STATION_COLUMN="HV-B Station";;
  "lv") STATION_COLUMN="LV Station";;
  *) echo "Type de station invalide. Choisissez 'hva', 'hvb' ou 'lv'."; exit 1;;
esac

# Déterminer le type de consommateur en fonction de l'argument
case $CONSUMER_TYPE in
  "comp") CONSUMER_COLUMN="Company";;
  "indiv") CONSUMER_COLUMN="Individual";;
  "all")
    # Pour 'all' avec 'lv', prendre en compte les deux types de consommateurs
    if [ "$STATION_TYPE" != "lv" ]; then
      echo "L'option 'all' est uniquement valide pour la station 'lv'."
      exit 1
    fi
    CONSUMER_COLUMN="all"  # 'all' signifie prendre en compte 'comp' et 'indiv'
    ;;
  *) echo "Type de consommateur invalide. Choisissez 'comp', 'indiv' ou 'all'."; exit 1;;
esac

# Extraire l'entête pour trouver les indices des colonnes
HEADER=$(head -n 1 "$INPUT_FILE")
STATION_INDEX=$(echo "$HEADER" | tr ';' '\n' | grep -n "$STATION_COLUMN" | cut -d: -f1)
CONSUMER_INDEX=$(echo "$HEADER" | tr ';' '\n' | grep -n "$CONSUMER_COLUMN" | cut -d: -f1)

if [ -z "$STATION_INDEX" ]; then
  echo "Impossible de trouver la colonne pour la station spécifiée."
  exit 1
fi

# Si le consommateur est "all", on devra chercher et inclure à la fois "Company" et "Individual"
if [ "$CONSUMER_COLUMN" == "all" ]; then
  # On va afficher toutes les lignes où le type de station correspond et où l'un des consommateurs est valide
  awk -F';' -v station_idx="$STATION_INDEX" '
    NR == 1 || ($station_idx != "-")
  ' "$INPUT_FILE"
else
  if [ -z "$CONSUMER_INDEX" ]; then
    echo "Impossible de trouver la colonne pour le consommateur spécifié."
    exit 1
  fi

  # Filtrer et afficher les résultats en fonction des critères
  echo "Résultats pour $STATION_COLUMN et $CONSUMER_COLUMN :"
  awk -F';' -v station_idx="$STATION_INDEX" -v consumer_idx="$CONSUMER_INDEX" '
    NR == 1 || ($station_idx != "-" || $consumer_idx != "-")
  ' "$INPUT_FILE"
fi
