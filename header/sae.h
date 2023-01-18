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
#define color   system("color 07");
void testColor(void);
#endif

#ifdef __linux__
#define clean   system("clear");
#endif

#ifndef wait
#define wait    printf("Appuyez sur entree pour continuer...") ; \
                scanf("%*c");
#endif
/*
------------------------------------------------------------------------
                            Les structures
------------------------------------------------------------------------
*/

//Proposition structure de candidat & choix pour la partie 2 ( jean ) : 
typedef struct choix
{
    char ville[50];
    char departement[50];
    int decisionDepartement;
    int validationCandidat;
    struct choix *suiv;

}Choix, *lChoix;

typedef struct
{
    int numero;
    char nom[50];
    char prenom[50];
    float notes[4];
    int nbChoix;
    lChoix lchoix;
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
    float moyMin;
    int admisMax;
    ListeCandidats lAdmis;
    ListeCandidats lAttente;
    struct maillonDeptV2 * suiv;

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
void menuCandidat(Log * tLog, int nbLog, VilleIut *tIut[], int nbVilles, Candidat *c);
Candidat IntermediaireMenuCandidat(ListeCandidats lCand, int *trouve);
void saisirCandidature(char ville[], char dep[], VilleIut *tiut[], int nbVille);
VilleIut *saisieIut(VilleIut *tiut[], int nbVille, int *res);
int choixMenuCandidat(void);
int afficherMenuCandidat(void);
int afficherMenuVisiteur(void);
int choixMenuVisiteur(void);
void banniereConnection(void);
void saisieNomUtilisateur(char * utilisateur);
void saisieMdp(char * mdp);
void menuVisiteur(Log * tLog, int nbLog, VilleIut *tIut[], int nbIut, ListeCandidats lCand);


int saisirNbPlaceDep(void);
void saisirRespDep(char *resp);
void seConnecter(Log * tLog, int nbLog, VilleIut ** tIut, int nbIut, ListeCandidats lCand);
void seConnecterTest(void);

int saisirNbPlaceDep(void);
int modifieRespDept(VilleIut *tiut[], int nbVilles, char ville[], char nomDept[], char nvNomResp[]);
void afficherDeptIutDonne(VilleIut *tiut[], int nbVilles);
void afficheIUTDept(VilleIut *tiut[], int nbVilles);
void afficheVillesIUT(VilleIut *tiut[], int nbVilles);
void afficheNbPlacesDep(VilleIut *tiut[], int nbVilles);
int existeVille( VilleIut *tiut[], char ville[], int nbvilles );
void menuAdmin(VilleIut *tiut[], int nbVilles);
int saisirVille(VilleIut *tiut[], int nbVilles, char ville[]);
MaillonDept *saisirDep(ListeDept ldept);
int saisirNouvDep(char *nomDep, char *resp);

void afficherUnCandidat(Candidat candidat);
void afficherCandidats(Candidat **candidats, int nbCandidats);
int creerCandidat(Candidat *tCand[], int nbCandidats);
lChoix supprimerCandidature( lChoix l, int *nbchoix);
lChoix supprmRecru( lChoix l, int rep );
lChoix creerCandidature(lChoix choixCandid, char ville[50], char departement[50], int decision, int validation, int *nbchoix);


// listeDeparements.c
ListeDept ajouterEnTete(ListeDept ldept, char nomDept[], char resp[], int nbP);
ListeDept supprimerEnTete(ListeDept ldept);
ListeDept supprimerDept(ListeDept ldept, char nomDep[]);
ListeDept ajouterDept(ListeDept ldept, char nomDept[], char resp[], int nbP);
ListeDept listenouv();
bool vide(ListeDept ldept);
int longueur(ListeDept ldept);
int existeDept(ListeDept ldept, char nom[]);
void afficherListe(ListeDept ldept);

// Choix.c
lChoix ajouterEnTeteC( lChoix lchoix, char ville[], char departement[], int decision, int validation);
lChoix supprimerEnTeteC( lChoix lchoix );
lChoix listenouvC(void);

// iut.c


// chargEtSauvFich.c

void sauvegardeCandidat(ListeCandidats m, int nbCandidat);
void sauvegardeIut(VilleIut ** tIut, int nbIut);
void testCharge(void);
void lectureDep(ListeDept ldept, FILE * fichier);
ListeDept initialiseDep(void);
ListeDept lireDep(FILE * fichier);
void lectureIut(VilleIut * iut, FILE * fichier);
VilleIut * initialiseIut(void);
VilleIut * lireIut (FILE * fichier);
VilleIut ** chargeIutDon(char nomFichier[], int * nbIut, int * nbMax);
VilleIut ** initialiseTabIut(void);
void tailleSupTabIut(VilleIut ** tIut, int *nbMax);
void fusionIut(VilleIut ** tIut, int * nbIut);
int existe(char * nom, VilleIut ** tIut, int nbIut, int iDepart, int * indice);
void fusion(VilleIut ** tIut, int nbIut, int i, int j);
void supprimerIut(VilleIut ** tIut, int nbIut, int j);

ListeCandidats chargeCandidat(int * nbCandidat);
MaillonCandidat * lireCandidat(FILE * flot);
lChoix lireChoix (FILE *flot);
lChoix recupChoix(FILE *flot, int nbChoix);
lChoix ajouteChoix(lChoix l, lChoix nouv);
ListeCandidats ajouteCandidat (ListeCandidats l, MaillonCandidat * nouv);


// candidat.c

Candidat *modifierCandidat(Candidat *c);
void affichageListesDept( ListeCandidats lcand, char * type, char * nomDept );
ListeCandidats trierListeCandidats( ListeCandidats l );
ListeCandidats insertionCroissanteCand( ListeCandidats nvL, ListeCandidats l );
ListeCandidats insertionTeteCand( ListeCandidats nvL, ListeCandidats l );

void menuPartie4( Candidat ** tCand, VilleIut **tIut, int nbvilles, int nbcand );
int menuResponsableDeptPartie4( char ville[], char departement[], VilleIut ** tIut, int nbvilles );
void miseAJourListesDepartements( VilleIut ** tIut , int nbvilles );
ListeCandidats ajouterEnQueue( ListeCandidats ladmis, ListeCandidats lattentes, VilleIut ** tIut, int pos );
ListeCandidats supprimerEnTeteCandidat( ListeCandidats l );
int menuCandidatPartie4( Candidat **tCand, VilleIut **tIut,  int numero, int nbvilles, int nbcand );
int compterNombreValidations( Candidat c, VilleIut ** tIut, int nbvilles );
Candidat validationCandidat( Candidat c, VilleIut ** tIut, int nbvilles );


// Partie3.c 

ListeDeptV2 configurationDeptV2( ListeDept ldept );

void menuPartie3( VilleIut ** tIut, int nbvilles );
int menuResponsableAdmissionPartie3( VilleIut ** tIut, int nbVilles, char ville[], char departement[] );
ListeDeptV2 miseAJourMoyenneDept( ListeDeptV2 l );
ListeDeptV2 miseAJourNbAdmisDept( ListeDeptV2 l );

//phase.c
void afficherMenuAdmin(void);

//sae.c
void afficheNbPlace(VilleIut ** tIut, int nbIut);
void menuResponsable(Log * tLog, int nbLog, VilleIut *tIut[], int nbIut);
int afficherMenuResponsable(void);


//test
