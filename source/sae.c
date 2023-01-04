#include "../header/sae.h"

/**
 * @brief Fonction globale qui :
 * - Charge les fichiers dans les structures adaptées
 * - Appel la fonction du menu général (visiteur) avec les données enregistrées
 * - Sauvegarde toutes les données dans les fichiers correspondants avant de terminer le logiciel
 */
void Globale(void)
{
    //Chargement des fichiers

    //Appel du menu visiteur
    menuVisiteur();

    //Sauvegarde dans les fichiers
}

/**
 * @brief Cette fonction affiche le menu des options disponibles pour un visiteur
 * et demande à l'utilisateur de faire son choix en appelant la fonction
 * choixMenuVisiteur. Selon le choix de l'utilisateur, la fonction appelle la fonction correspondante
 * ou met fin à l'exécution de la fonction.
*/
void menuVisiteur(void)
//void menuVisiteur(VilleIut *villeIut, int nbVilles)
{
    int choix;
    int actif = 1;
    
    clean

    while(actif)
    {
        choix = choixMenuVisiteur();
        clean
        switch(choix)
        {
            case 1:
                //afficheVillesIUT(villeIut, nbVilles);
                printf("Affiche les villes qui ont des IUT. (En attente de la fonction de chargement)\n");
                break;
            case 2:
                printf("Affiche le nombre de place dans un departement (En attente de Guillaume)\n");
                break;
            case 3 :
                printf("Affiche les departements d'un IUT donne (En attente de Loris)\n");
                break;
            case 4 :
                printf("Affiche les IUT possedant un departement donne (En attente de Jean)\n");
                break;
            case 5 :
                printf("Fonction pour se connecter (En attente de Yanis)\n");
                break;
            case 0 :
                actif = 0;
                break;
        }
    }
}

/**
 * @brief Affiche le menu des options disponibles pour un visiteur.
 * 
 * Cette fonction affiche à l'écran un menu proposant plusieurs options 
 * pour un visiteur du site. Le menu est présenté sous la forme d'une liste 
 * numérotée, avec un numéro associé à chaque option. Le visiteur peut 
 * faire son choix en saisissant le numéro correspondant à l'option souhaitée.
 * 
 * Voici les options proposées dans le menu :
 * 
 * - Afficher toutes les villes possédant un IUT
 * - Afficher le nombre de places dans un département donné
 * - Afficher les départements d'un IUT donné
 * - Afficher les IUT possédant un département donné
 * - Se connecter
 * - Quitter
 * 
 * @return Le choix de l'utilisateur, sous forme d'un entier
 */
int afficherMenuVisiteur(void) {
    int choix;

    printf("============================================================\n\t\t\tMENU VISITEUR\n============================================================\n\n");
  
    printf("\t1. Afficher toutes les villes possedant un IUT\n");
    printf("\t2. Afficher le nombre de places dans un departement donne\n");
    printf("\t3. Afficher les departements d'un IUT donne\n");
    printf("\t4. Afficher les IUT possedant un departement donne\n");
    printf("\t5. Se connecter\n");
    printf("\t0. Quitter\n");
    printf("\nChoix : ");

    scanf("%d%*c", &choix);
    return choix; 
}

/**
 * @brief Demande à l'utilisateur de faire un choix parmi les options du menu visiteur
 * 
 * Cette fonction affiche le menu des options disponibles pour un visiteur 
 * et demande à l'utilisateur de faire son choix en saisissant un nombre compris 
 * entre 0 et 5. Si l'utilisateur saisit un nombre incorrect, il sera invité à 
 * resaisir son choix jusqu'à ce qu'il saisisse un nombre valide.
 * 
 * @return int Le choix de l'utilisateur compris entre 0 et 5
 */
int choixMenuVisiteur(void)
{
    int choix;

    choix = afficherMenuVisiteur();

    while (choix < 0 || choix > 5)
    {
        clean
        printf("\nChoix incorrect.\n\n");
        choix = afficherMenuVisiteur();
    }

    return choix;
}

/**
 * Modifie le nombre de places d'un département dans un IUT.
 *
 * @param villeIut tableau de pointeurs sur les structures VilleIut
 * @param nbVilles nombre de villes dans le tableau villeIut
 * @param ville nom de la ville où se trouve l'IUT
 * @param nomDept nom du département à modifier
 * @param nbP nouveau nombre de places
 *
 * @return 1 si le département a été trouvé et modifié, 0 sinon
 */
int modifiePlacesDept(VilleIut *villeIut, int nbVilles, char *ville, char *nomDept, int nbP)
{
    // Recherche de la ville et du département
    int i;
    for (i = 0; i < nbVilles; i++)
    {
        if (strcmp(villeIut[i].nom, ville) == 0)
        {
            // Ville trouvée, recherche du département
            MaillonDept *dept = villeIut[i].ldept;
            while (dept != NULL && strcmp(dept->nomDept, nomDept) != 0)
            {
                dept = dept->suiv;
            }
            if (dept != NULL)
            {
                // Département trouvé, modification du nombre de places
                dept->nbP = nbP;
                return 1;
            }
            else
            {
                // Département non trouvé
                return 0;
            }
        }
    }

    // Ville non trouvée
    return 0;
}

/**
 * Affiche les IUT possédant un département spécifique.
 *
 * @param villeIut tableau de pointeurs sur les structures VilleIut
 * @param nbVilles nombre de villes dans le tableau villeIut
 * @param nomDept nom du département à rechercher
 */
void afficheIUTDept(VilleIut *villeIut, int nbVilles, char *nomDept)
{
    int i;
    for (i = 0; i < nbVilles; i++)
    {
        // Parcours de la liste chaînée de départements de la ville
        MaillonDept *dept = villeIut[i].ldept;
        while (dept != NULL)
        {
            if (strcmp(dept->nomDept, nomDept) == 0)
            {
                // Département trouvé, affichage de la ville
                printf("IUT de %s\n", villeIut[i].nom);
                break;
            }
            dept = dept->suiv;
        }
    }
}

/**
 * Affiche les villes qui ont des IUT.
 *
 * @param villeIut tableau de pointeurs sur les structures VilleIut
 * @param nbVilles nombre de villes dans le tableau villeIut
 */
void afficheVillesIUT(VilleIut *villeIut, int nbVilles)
{
    int i;
    for (i = 0; i < nbVilles; i++)
    {
        // Affichage du nom de la ville
        printf("%s\n", villeIut[i].nom);
    }
}

/**
 * Affiche et gère le menu administrateur.
 *
 * @param villeIut tableau de pointeurs sur les structures VilleIut
 * @param nbVilles nombre de villes dans le tableau villeIut
 */
void menuAdmin(VilleIut *villeIut, int nbVilles)
{
    int choix;
    do
    {
        // Affichage du menu
        printf("\nMenu administrateur:\n");
        printf("1. Modifier le nombre de places d'un département\n");
        printf("2. Créer un département dans un IUT\n");
        printf("3. Supprimer un département d'un IUT\n");
        printf("4. Lancer la phase de candidature\n");
        printf("5. Arrêter la phase de candidature\n");
        printf("6. Modifier le nom du responsable d'un département\n");
        printf("7. Quitter\n");
        printf("\nVotre choix: ");

        // Saisie du choix de l'utilisateur
        scanf("%d", &choix);

        // Traitement du choix de l'utilisateur
        switch (choix)
        {
            case 1:
                // Modification du nombre de places d'un département
                //modifiePlacesDept(villeIut, nbVilles);
                break;
            case 2:
                // Création d'un département dans un IUT
                //creeDeptIUT(villeIut, nbVilles);
                break;
            case 3:
                // Suppression d'un département d'un IUT
                //supprimeDeptIUT(villeIut, nbVilles);
                break;
            case 4:
                // Lancement de la phase de candidature
                //lanceCandidature();
                break;
            case 5:
                // Arrêt de la phase de candidature
                //arreteCandidature();
                break;
            case 6:
                // Modification du nom du responsable d'un département
                //modifieRespDept(villeIut, nbVilles);
                break;
            case 7:
                // Quitter
                //printf("Au revoir!\n");
                break;
            default:
                // Choix non valide
                //printf("Choix non valide.\n");
            break;
        }
    } while (choix != 7);
}

/*
================================================
                    Partie 2
================================================
*/

/**
 * @brief Affiche les informations d'un candidat
 * @param candidat Le candidat à afficher
 */
void afficherCandidat(Candidat candidat)
{
    printf("Numéro du candidat : %d\n", candidat.numero);
    printf("Nom : %s\n", candidat.nom);
    printf("Prénom : %s\n", candidat.prenom);
    printf("Notes : %.2f %.2f %.2f %.2f\n", candidat.notes[0], candidat.notes[1], candidat.notes[2], candidat.notes[3]);
    printf("Nombre de choix : %d\n", candidat.nbChoix);
    for (int i = 0; i < candidat.nbChoix; i++)
    {
        printf("Choix %d :\n", i + 1);
        printf("  Ville : %s\n", candidat.choix[i].ville);
        printf("  Département : %s\n", candidat.choix[i].departement);
        printf("  Décision du département : %d\n", candidat.choix[i].decisionDepartement);
        printf("  Validation : %d\n", candidat.choix[i].validationCandidat);
    }
}

/**
 * @brief Affiche la liste des candidats
 * 
 * @param candidats Le tableau de candidats à afficher
 * @param nbCandidats Le nombre de candidats dans le tableau
 */
void afficherCandidats(Candidat *candidats, int nbCandidats)
{
    for (int i = 0; i < nbCandidats; i++)
    {
        printf("\nCandidat %d :\n", i + 1);
        afficherCandidat(candidats[i]);
    }
}
