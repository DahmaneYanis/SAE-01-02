#include "../header/sae.h"


/**
 * @brief Test fonction Jean
 * 
 */
void testJean(void)
{
    VilleIut **tIut = (VilleIut **)malloc(sizeof(VilleIut *)*5);
    strcpy(tIut[0]->nom, "John");
    strcpy(tIut[0]->lDept->nomDept, "Info");
    strcpy(tIut[0]->lDept->resp, "Yanis");
    tIut[0]->lDept->nbP = 12;
    tIut[0]->lDept->suiv = NULL;


    //afficheVillesIUT(tIut, 0);
}
