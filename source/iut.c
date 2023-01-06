#include "../header/sae.h"

VilleIut ajouterDepartement(VilleIut iut, char nom[30], char resp[30], int nbP)
{
    iut.lDept = ajouterDept(iut.lDept, nom, resp, nbP);
    return iut;
}