#include "../header/sae.h"
// test rapide de commit jean...

/**
 * @brief Test fonction Jean
 * 
 */
// void testJean(void)
// {
//     printf(" \n --> Modification du nombre de places dans un IUT :\n");
//     printf(   "     ---------------------------------------------\n\n");

//     Log * tLog;
//     VilleIut *tIut[50] ;

//     int nbVilles;
//     int nbLog;

//     //Chargement des fichiers
//     tLog = chargementLog("../donnees/log.don", &nbLog);
//     nbVilles = chargIutDon(tIut, 50, "../donnees/iut.don");


//     int e = 0;
//     for ( int i = 0; i < nbVilles ; i ++)
//     {
//         printf(" Ville ( IUT ) : %10s \n -------------------\n ", tIut[i] -> nom);

//         while ( tIut[e] -> lDept != NULL )
//         {
//            printf(" Departement ( %10s ) : %10s | places : %5d \n", 
//            tIut[e] -> lDept -> nomDept, tIut[e] -> lDept -> nbP); 

//            tIut[e] -> lDept = tIut[e] -> lDept -> suiv;
//         }
//     }
// }


/*
void guillaume(void)
{
    Candidat *tCandid[50];
    int nbCandidats=0;
    char ville[50], departement[50];

    nbCandidats = creerCandidat(tCandid, nbCandidats);

    printf("Nom de la ville : ");
    scanf("%s%*c", ville);

    printf("Nom du departement : ");
    scanf("%s%*c", departement);

    tCandid[0]->lchoix = creerCandidature(tCandid[0]->lchoix, ville, departement, 0, 0);
    tCandid[0]->nbChoix +=1 ;

    printf("Nom de la ville : ");
    scanf("%s%*c", ville);

    printf("Nom du departement : ");
    scanf("%s%*c", departement);

    tCandid[0]->lchoix = creerCandidature(tCandid[0]->lchoix, ville, departement, 0, 0);
    tCandid[0]->nbChoix +=1 ;

    afficherUnCandidat(*tCandid[0]);

    tCandid[0] -> lchoix = supprimerCandidature(tCandid[0]->lchoix, tCandid[0]->nbChoix);
    tCandid[0]->nbChoix-=1;

    //tCandid[0] -> lchoix = supprmRecru ( tCandid[0] -> lchoix, 1);

    printf(" ( temporaire( 4 )... --> %s \n\n", tCandid[0] -> lchoix -> ville);

    afficherUnCandidat(*tCandid[0]);
}

*/


