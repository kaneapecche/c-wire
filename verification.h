#ifndef VERIFICATION_H
#define VERIFICATION_H

#include<stdio.h>
#include<stdlib.h>
#include<AVL.h>
#include<string.h>

void verificationalloc();

void verificationferme(FILE* fichier);

void erreurs(int argc, char *argv[]);

void verification(Arbre * a);

#endif
