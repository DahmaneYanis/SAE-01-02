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
}MaillonDept, *ListeDept;

// Utilise pour le tableau de pointeurs sur cette structure (pour Guillaume)
typedef struct 
{
    char nom[30];
    ListeDept ldept;
}VilleIut;

// Liste.c
ListeDept ajouterEnTete(ListeDept ldept, char nomDept[], char resp[], int nbP);
ListeDept supprimerEnTete(ListeDept ldept);
ListeDept ajouter(ListeDept ldept, char nomDept[], char resp[], int nbP);
ListeDept listenouv();
bool vide(ListeDept ldept);
int longueur(ListeDept ldept);
void afficherListe(ListeDept ldept);