#include "sae.h"


int main(void)
{
	ListeDept ldept;
	VilleIut iut;

	//TESTS des fonctions de manipulation des structures VilleIut et ListeDept
	iut.ldept = listenouv();
	strcpy(iut.nom, "Clermont Ferrand");
	iut.ldept = ajouterDept(iut.ldept, "Chimie", "Henri Laserre", 80);
	iut.ldept = ajouterDept(iut.ldept, "Chimie", "Henri Laserre", 80);
	afficherListe(iut.ldept);
}