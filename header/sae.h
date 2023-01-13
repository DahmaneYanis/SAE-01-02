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
#define clean   system("clear");
#endif

/*
------------------------------------------------------------------------
                            Les structures
------------------------------------------------------------------------
*/

//Proposition structure de candidat & choix pour la partie 2 ( jean ) : 
typedef struct
{
    char ville[50];
    char departement[50];
    int decisionDepartement;
    int validationCandidat;
}Choix;

typedef struct
{
    int numero;
    char nom[50];
    char prenom[50];
    float notes[4];
    int nbChoix;
    Choix *choix;
}Candidat;

//Proposition de structure de candidature pour la Partie 3 ( jean ) :

typedef struct maillonCandidat
{
    Candidat candidat;
    struct maillonCandidat * suiv;
} MaillonCandidat, * ListeCandidats;

// Structures de la partie 1 : 
typedef struct log
{
    char utilisateur[30];
    char mdp[30];
    char status[15];
}Log;

typedef struct maillonDept
{
    char nomDept[30];
    char resp[30];
    int nbP;
    struct maillonDept *suiv;

}MaillonDept, *ListeDept;


typedef struct maillonDeptV2
{
    char nomDept[30];
    char resp[30];
    int nbP;

    //Mise a jour du maillon pour correspondre à la partie 3 : 
    int moyMin;
    int admisMax;
    ListeCandidats lAdmis;
    ListeCandidats lAttente;
    struct maillonDeptV2 *suiv;

} MaillonDeptV2, * ListeDeptV2;

typedef struct 
{
    char nom[30];
    ListeDept lDept;

    // Mise à jour pour correspondre à la partie 3 
    ListeDeptV2 lDeptV2;
}VilleIut;

/*
------------------------------------------------------------------------
                            Les prototypes
------------------------------------------------------------------------
*/
// sae.c
void testJean(void);
void guillaume(void);

void Globale(void);
Log * chargementLog(char * nomFichier, int * nbLog);
int existeUtilisateur(char * utilisateur, int * indice, Log * tLog, int nbLog);
int mdpValide(char * mdp, int indice, Log * tLog);
//void menuVisiteur(VilleIut *villeIut, int nbVilles);
void menuVisiteur(Log * tLog, int nbLog, VilleIut *tIut[], int nbVilles);
void menuCandidat(Log * tLog, int nbLog, VilleIut *tIut[], int nbVilles);
int choixMenuCandidat(void);
int afficherMenuCandidat(void);
int afficherMenuVisiteur(void);
int choixMenuVisiteur(void);
void banniereConnection(void);
void saisieNomUtilisateur(char * utilisateur);
void saisieMdp(char * mdp);
void seConnecter(Log * tLog, int nbLog);
void seConnecterTest(void);

int modifiePlacesDept(VilleIut **villeIut, int nbVilles, char *ville, char *nomDept, int nbP);
int modifieRespDept(VilleIut *tVilleIut[], int nbVilles, char ville[], char nomDept[], char nvNomResp[]);
void afficheIUTDept(VilleIut* *villeIut, int nbVilles, char *nomDept);
void afficheVillesIUT(VilleIut **villeIut, int nbVilles);
void afficheNbPlacesDep(VilleIut *tVilleIut[], int nbVilles, char nomDept[]);
void menuAdmin(VilleIut **villeIut, int nbVilles);

void afficherCandidat(Candidat candidat);
void afficherCandidats(Candidat *candidats, int nbCandidats);
int creerCandid(Candidat tCand[], int nbCandidats);

ListeDeptV2 configurationDeptV2( ListeDept ldept );

void affichageListesDept( ListeCandidats lcand, char * type, char * nomDept );
ListeCandidats trierListeCandidats( ListeCandidats l );
ListeCandidats insertionCroissanteCand( ListeCandidats nvL, ListeCandidats l );
ListeCandidats insertionTeteCand( ListeCandidats nvL, ListeCandidats l );

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


// chargEtSauvFich.c
int chargIutDon(VilleIut *tVilleIut[], int nbMax, char nomFich[]);
void lireDep(FILE *flot, char nomDept[], int *nbP, char resp[]);
int appartientIut(VilleIut *tVilleIut[], int nb, char nom[], int *trouve);
void sauvegarderFichierIutDon(VilleIut *tVilleIut[], int nbVille, char nomFich[]);

