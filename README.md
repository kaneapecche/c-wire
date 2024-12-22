Le but de notre projet est de prendre un gros dossier qui n'est pas traitable sans code afin de trier les données en fonction des stations que l'utilisateur choisit. 
A partir de cela les données sont trier par ordre croissant et de là on fait la somme des capacités et des consommateurs.

Pour que vous puissiez exécuter ce programme, il faut tout d'abord que vous cloniez le projet:
vous devez appuyez sur le bouton vert où il y a écrit Code puis vous allez voir qu'il y a un bouton Download ZIP,
donc vous télécharger le fichier Zip puis vous allez le dé-zipper le fichier dans votre explorateur de fichier et après vous pourrez l'exécuter à partir de votre terminal.

Il faudra rajouter le fichier c-wire_v25.dat dans vos fichiers car il est trop volumineux pour être sur le github.

Au niveau des commandes, vous allez entrée dans votre terminal :
- Compilez le projet en utilisant : make -C ./codeC
- puis pour tester que tous fonctionne vous faite:
      ./c-wire.sh
  puis ./c-wire.sh c-wire_v25.dat hvb comp
  puis ./c-wire.sh /home/assia/c-wire_v25.dat hvb comp
  puis open lv_indiv.txt

hvb comp est un exemple de ce que peut choisir l'utilisateur, il peut choisir :

- hvb comp
- hva comp
- lv comp
- lv indiv
- lv all
- lv all minmax

il faudra donc choisir lequel on exécute avec ./c-wire.sh /home/assia/c-wire_v25.dat hvb comp
puis ouvrir avec open lv_indiv.txt pour que cela fonctionne il faudra bien faire attention à mettre le tiret seulement pour l'ouverture

attention ./c-wire.sh /home/assia/c-wire_v25.dat hvb comp pour cette commande /home/assia/ cela doit être remplacé par votre chemin celui-ci est présent lorsque vous
allez avoir votre fichier c-wire_v25.dat il faudra que vous fassiez un clic-droit et allez sur propriété et ça affichera votre chemin.

vous pourrez également effacer les fichiers générer grâce au clean
