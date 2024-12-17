#!/bin/bash

verification_arg(){
    if [ -z $1 ] || [ -z $2 ] || [ -z $3 ]; then
        echo "arguments manquants"
        return 1
    else 
        if [ ! -f "$1" ]; then 
            echo "Le fichier n'existe pas"
            return 2
        else
            echo "Fichier existant, OK"
        fi
        a='indiv'
        b='all'
        c="comp"
        case $2 in
            'hvb'|'hva') 
                echo "Argument 2 valide"
                if [ "$3" == "$c" ]; then
                    echo "Argument 3 valide"
                else
                    echo "Erreur : argument 3 invalide"
                    return 3
                fi
                ;;
            'lv')
                echo "Argument 2 valide"
                if [ "$3" == "$a" ] || [ "$23" == "$b" ] || [ "$3" == "$c" ]; then
                    echo "Argument 3 valide"
                else
                    echo "Erreur : argument 3 invalide"
                    return 4
                fi
                ;;
            *)
                echo "Erreur : Argument 2 invalide"
                return 5
                ;;
        esac 
    fi
    if [ -z $5 ]; then
       echo "pas d'aide"
    else
        d="-h"
        if [ "$5" != "$d" ]; then
            echo "argument 5 invalide"
            return 6
        else
            aide
        fi  
    fi
    if [ -z $4 ]; then
        echo "pas d'id de centrale"
    else
        e=5
        if (( "$4" > "$e" )); then
            echo "argument 4 invalide"
            return 7
        else
            echo 'argumnt 4 valide'
        fi
        return 0
    fi
}


#fonction qui affiche une aide détaillée sur l'utilisation du script
aide(){
    echo -e "Utilisation : $0  <arg 1>  <arg2 >  <arg 3>  <arg4>  <arg5>\n"
    echo "Description : L'utilisation de ce script nécessite 3 à 5 arguments :"
    echo "-argument 1 : le chemin du fichier de données, il indique l'endroit où se trouve le fichier d'entrée"
    echo "-argument 2 : le type de station à traiter (hvb, hva ou lv)"
    echo "-argument 3 : le type de consommateur à traiter (comp pour entreprises, indiv pour particuliers ou all pour tous)"
    echo "-argument 4 : OPTIONEL - identifiant de la centrale, permet de filtrer les résultats pour une centrale spécifique"
    echo "-argument 5 : OPTIONEL - (-h) permet d'afficher une aide détaillée sur l'utilisation du script"
    echo "Attention! Dans le cas des stations hvb et hva, la seule option de consommateur est comp"
}



verification_arg $1 $2 $3 $4 $5
res1=$?
if (( res1 != 0 )); then
    echo "$res1"
    aide
else
    echo 'OK'
fi

#verifie l'existance du fichier c sinon elle le compile
if [ ! -f test2 ]; then 
    echo "l'executable programme.c est introuvable. compilation ..."
    gcc -o test2 test2.c
    if [ $? -ne 0 ]; then 
        echo 'erreur : echec de la compilation'
        exit 1
    fi
fi

start_time=$(date +%s)
    end_time=$(date +%s)
    duration=$(( end_time - start_time ))
    echo "temps d'exucation : ${duration}.0 sec"

#cat $1
outputFile='./sortie.csv'
> "$outputFile"
case $2 in
    'hvb')
        grep -E "^[0-9];[0-9];-;-;" "$1" | cut -f 2,7,8 -d ';' | tr '-' '0' | ./test2 | sort -t ":" -k 2,2n > "$outputFile"
        cat "$outputFile"
        echo "$?"
    ;;
    'hva')
        cut -f 3,5,7,8 -d ';' "$1" | tr '-' '0' | grep -v '^0;' | cut -f 1,3,4 -d ';' > tmp.txt
    ;;
    'lv')
        echo 'test'
    ;;
    *)
        echo 'test'
    ;;
esac




if [ -f sortie.txt ]; then 
    cp sortie.txt "$2-$3-$4.csv"
fi

#recuperation de la somme du fichier c
#creation du fichier avec les valeurs 
#par ordre croissant 