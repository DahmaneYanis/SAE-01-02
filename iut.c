#include "sae.h"

VilleIut ajouterDepartement(VilleIut iut, char nom[30], char resp[30], int nbP)
{
    iut.ldept = ajouterDept(iut.ldept, nom, resp, nbP);
    return iut;
}