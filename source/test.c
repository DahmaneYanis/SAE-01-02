#include "../header/sae.h"
// test rapide de commit jean...

/**
 * @brief Test fonction Jean
 * 
 */
void testJean(void)
{
    printf(" \n --> Modification du nombre de places dans un IUT :\n");
    printf(   "     ---------------------------------------------\n\n");

    Log * tLog;
    VilleIut *tIut[50] ;

    int nbVilles;
    int nbLog;

    //Chargement des fichiers
    tLog = chargementLog("../donnees/log.don", &nbLog);
    nbVilles = chargIutDon(tIut, 50, "../donnees/iut.don");


    int e = 0;
    for ( int i = 0; i < nbVilles ; i ++)
    {
        printf(" Ville ( IUT ) : %10s \n -------------------\n ", tIut[i] -> nom);

        while ( tIut[e] -> lDept != NULL )
        {
           printf(" Departement ( %10s ) : %10s | places : %5d \n", 
           tIut[e] -> lDept -> nomDept, tIut[e] -> lDept -> nbP); 

           tIut[e] -> lDept = tIut[e] -> lDept -> suiv;
        }
    }
}
