#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct maillonDept
{
    char nomDept[30];
    char resp[30];
    int nbP;
    struct maillonDept *suiv;
}MaillonDept, *Ldept;

// Utilise pour le tableau de pointeurs sur cette structure (pour Guillaume)
typedef struct 
{
    char nom[30];
    Ldept l;
}VilleIut;