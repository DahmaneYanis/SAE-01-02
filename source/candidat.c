#include "../header/sae.h"

/**

    @brief Modifie les informations d'un candidat
    @param c Pointeur vers le candidat à modifier
    @return Pointeur vers le candidat modifié
*/
Candidat *modifierCandidat(Candidat *c)
{
    int choix;
    printf("Que voulez vous modifier\n1-Le nom\n2-Le Prenom\n3-Les notes\n");
    scanf("%d", &choix);
    switch (choix)
    {
        case 1:
            printf("Nom actuel : %s\nVeuillez saisir le nouveau nom\n", c->nom);
            fgets(c->nom, 50, stdin);
            c->nom[strlen(c->nom) - 1] = '\0';
            break;
        case 2:
            printf("Prenom actuel : %s\nVeuillez saisir le nouveau prenom\n", c->prenom);
            fgets(c->nom, 50, stdin);
            c->prenom[strlen(c->prenom) - 1] = '\0';
            break;
        case 3:
            printf("Voici les notes actuels : %.2f %.2f %.2f %.2f\nVeuillez saisir les nouvelles notes(note1/note2/note3/note4)", c->notes[0], c->notes[1], c->notes[2], c->notes[3]);
            scanf("%f/%f/%f/%f", &c->notes[0], &c->notes[1], &c->notes[2], &c->notes[3]);
            break;
    }
    return c;
}