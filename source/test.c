#include "../header/sae.h"


/**
 * @brief Test fonction Jean
 * 
 */
void testJean(void)
{
    int nbvilles;
    VilleIut *tIut[50] ;

    nbvilles=  chargIutDon(tIut, 50, "../donnees/iut.don");
    //tIut =  (VilleIut **)malloc(sizeof(VilleIut *)*nbvilles);
    // strcpy(tIut[0]->nom, "John");
    // strcpy(tIut[0]->ldept->nomDept, "Info");
    // strcpy(tIut[0]->ldept->resp, "YAnis");
    // tIut[0]->ldept->nbP = 12;
    // tIut[0]->ldept->suiv = NULL;


    afficheVillesIUT(tIut, nbvilles);
    sauvegarderFichierIutDon(tIut, nbvilles, "result.don");
}
