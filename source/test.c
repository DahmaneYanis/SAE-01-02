#include "../header/sae.h"


/**
 * @brief Test fonction Jean
 * 
 */
void testJean(void)
{
    VilleIut **tIut = (VilleIut **)malloc(sizeof(VilleIut *)*5);
    strcpy(tIut[0]->nom, "John");
    strcpy(tIut[0]->ldept->nomDept, "Info");
    strcpy(tIut[0]->ldept->resp, "YAnis");
    tIut[0]->ldept->nbP = 12;
    tIut[0]->ldept->suiv = NULL;


    //afficheVillesIUT(tIut, 0);
}
