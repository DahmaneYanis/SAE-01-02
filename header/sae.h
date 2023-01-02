#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
------------------------------------------------------------------------
        Prise en charge de l'OS pour le nettoyage de l'affichage
------------------------------------------------------------------------
*/

#ifdef _WIN32
#define clean   system("cls");
#define color   system("color 70");
void testColor(void);
#endif

#ifdef __linux__
#define clean   system("clear")
#endif



/*
------------------------------------------------------------------------
                            Les structures
------------------------------------------------------------------------
*/
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


/*
------------------------------------------------------------------------
                            Les structures
------------------------------------------------------------------------
*/
// sae.c
void Globale(void);
void menuVisiteur(void);
int afficherMenuVisiteur(void);
int choixMenuVisiteur(void);

// listeDeparements.c
ListeDept ajouterEnTete(ListeDept ldept, char nomDept[], char resp[], int nbP);
ListeDept supprimerEnTete(ListeDept ldept);
ListeDept supprimer(ListeDept ldept, char nom[]);
ListeDept ajouterDept(ListeDept ldept, char nomDept[], char resp[], int nbP);
ListeDept listenouv();
bool vide(ListeDept ldept);
int longueur(ListeDept ldept);
void afficherListe(ListeDept ldept);

// iut.c