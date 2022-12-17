#include "sae.h"


int main(void)
{
	ListeDept ldept;

	ldept = listenouv();
	
	ldept = ajouterEnTete(ldept, "Informatique", "John Doe", 150);
	ldept = ajouterEnTete(ldept, "Bio", "Ryan Taro", 200);
	afficherListe(ldept);
	ajouter(ldept, "Chimie", "Henri Laserre", 80);
	afficherListe(ldept);
}