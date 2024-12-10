#!/bin/bash

#fonction qui vérifie la validité du nombre d'arguments passés en paramètres
nb_arg() {
    attendu=$1
    actuel=$2
    if (( $attendu == $actuel )); then
        echo "OK"
        return 0
    else
        echo "Nombre d'arguments invalide"
        return 1
    fi
}

#fonction qui affiche une aide détaillée sur l'utilisation du script
aide(){
    echo -e "Utilisation : $0  <arg 1>  <arg2 >  <arg 3>\n"
    echo "Description : Ce script nécessit 3 arguments :"
    echo "-argument 1 : le chemin du fichier de données, il indique l'endroit où se trouve le fichier d'entrée"
    echo "-argument 2 : le type de station à traiter (hvb, hva ou lv)"
    echo "-argument 3 : le type de consommateur à traiter (comp pour entreprises, indiv pour particuliers ou all pour tous)"
    echo "Attention! Dans le cas des stations hvb et hva, la seule option de consommateur est comp"
}

#fonction qui vérifie si les arguments passés en paramétres correspondent à ce qui est demandé
arg_valid(){
    a='indiv'
    b='all'
    c="comp"
    case $1 in
        'hvb'|'hva') 
            echo "Argument 2 valide"
            if [ "$2" == "$c" ]; then
                echo "Argument 3 valide"
                return 0
            else
                echo "Erreur : argument 3 invalide"
                aide
                return 1
            fi
            ;;
        'lv')
            echo "Argument 2 valide"
            if [ "$2" == "$a" ] || [ "$2" == "$b" ] || [ "$2" == "$c" ]; then
                echo "Argument 3 valide"
                return 0
            else
                echo "Erreur : argument 3 invalide"
                aide
                return 1
            fi
            ;;
        *)
            echo "Erreur : Argument 2 invalide"
            aide
            return 1
            ;;
    esac  
}

#fonction qui vérifie si le fichier en argument existe
test_fichier(){
    if [ ! -f "$1" ]; then 
        echo "Le fichier n'existe pas"
        return 1
    else
        echo "Fichier existant, OK"
    fi
}

filtrage(){
    cp $1 tmp
}
#verifier que y a tout les parmetres 
nb_arg 3 $#
    res1=$?
    if (( res1 == 1 )); then
        aide
    fi
    arg_valid $2 $3
    test_fichier $1
    res2=$?
    if(( res2 == 1 )); then
        aide
    fi
    fichier_donee=$1

#duree pour mesurer le temps 
start_time=$(date +%s)
    ./programme.c "$#"
    end_time=$(date +%s)
    duration=$((end_time - start_time))
    echo "temps d'exucation : ${duration}.0 sec"

#verifie l'existance du fichier c sinon elle le compile
if[! -f programme.c]; then 
    echo "l'executable programme.c est introuvable. compilation ..."
    make || {echo "erreur: echech de la compilation."; exit 1;}
fi

# fonction qui va permettre le filtrage 
centrale=$1 #fonction a regler dans les if faut voir comment on ecrit la condition a l'interieur
hvb=$2
hva=$3
lv=$4
  if[ $centrale -eq 5 ] ;
	cat 'c-wire_v25.dat' | grep -E "^$centrale;"
  fi
  if[^$hvb]
	cat 'c-wire_v25.dat' | grep -E "^$hvb;"
  fi
  if[^$hva]
	cat 'c-wire_v25.dat' | grep -E "^$hva;"
  fi
  if[^$lv]
	cat 'c-wire_v25.dat' | grep -E "^$lv;"
  fi
  
//nom du fichier de sortie
sortie_fichier="c-wire_v25.dat"

echo "liste des stations et informations"> $sortie_fichier

#fonction pour demander les informations sur chaque station
 
info_station(){
	
	#demander le type de station
	# read -p permet de poser des questions aà l'utilisateur et stocker sa réponse
	
	read -p "entrez le type de station (hvb, hva,lv):"type_station
	#demander la capacité de la station
	read -p "entrez la capacité de la station (en MW):"capacité
	#demander la somme des consommateurs branchés
	read -p "entrez la somme des consommateurs (en MW):"consommateurs
	
	#ajouter les informations dans le fichier, la fonction est utilisé pour ajouter une ligne au fichier contenant la valeur de la variable
	echo "Type de station: $type_station">> "$sortie_fichier"
	echo "Capacité: $capacité MW">> "$sortie_fichier"
	echo "Consommateurs:$consommateurs MW">> "$sortie_fichier"
 }

	
#afficher le contenu du fichier généré

echo "les informations sont bien dans le fichier '$sortie_fichier'."
cat  "$sortie_fichier" # lit le fichuier et affiche son contenu sur le terminal





