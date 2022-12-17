#include "sae.h"


int main(void)
{
	ListeDept ldept;

	ldept = listenouv();
	
	ldept = ajouterEnTete(ldept, "Informatique", "John Doe", 15);
	ldept = ajouterEnTete(ldept, "Bio", "Ryan Taro", 20);
	afficherListe(ldept);
	ldept = supprimerEnTete(ldept);
	afficherListe(ldept);
}