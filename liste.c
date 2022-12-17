#include "sae.h"

/**
 * \brief Ajoute un maillon en tête de la liste de départements.
 *
 * \param ldept La liste de départements à laquelle le maillon doit être ajouté.
 * \param nomDept Le nom du département à ajouter.
 * \param resp Le responsable du département à ajouter.
 * \param nbP Le nombre de personnes dans le département à ajouter.
 *
 * \return La nouvelle liste de départements, avec le maillon en tête.
 */
ListeDept ajouterEnTete(ListeDept ldept, char nomDept[], char resp[], int nbP)
{
    MaillonDept *m;

    m = (MaillonDept *)malloc(sizeof(MaillonDept));
    if (!m)
    {
        printf("Erreur de malloc\n");
        exit(1);
    }
    strcpy(m->nomDept, nomDept);
    strcpy(m->resp, resp);
    m->nbP = nbP;
    if (vide(ldept))
    {
        m->suiv = NULL;
        return m;
    }
    m->suiv = ldept;
    return m;
}

/**
 * \brief Supprime le maillon en tête de la liste de départements.
 * \param ldept La liste de départements dont le maillon en tête doit être supprimé.
 * \return La nouvelle liste de départements, sans le maillon en tête.
 *
 * Si la liste est vide ou ne contient qu'un seul élément, la fonction retourne une nouvelle liste vide.
 * Si la liste contient plusieurs éléments, le maillon en tête est supprimé et la fonction retourne la nouvelle liste de départements,
 * en commençant par le deuxième maillon.
 */
ListeDept supprimerEnTete(ListeDept ldept)
{
    MaillonDept *aux;
    if (!ldept)
    {
        printf("Operation impossible\n");
        exit(1);
    }
    if (!ldept->suiv)
        return listenouv();
    aux = ldept->suiv;
    free(ldept); 
    return aux;
}

/**
 * @brief Vérifie si une liste de départements est vide.
 * @param ldept La liste de départements à vérifier.
 * @return true si la liste est vide, false sinon.
 */
bool vide(ListeDept ldept)
{
    if (!ldept)
        return true;
    return false;
}
/**
 * @brief Créer une nouvelle liste de départements vide.
 * 
 * @return La nouvelle liste de départements vide. 
 */
ListeDept listenouv()
{
    ListeDept l;

    l = NULL;
    return l;
}

/**
 * @brief Affiche tous les départements d'une liste, avec leurs noms, leurs responsables et leur nombre de places, sous forme de tableau.
 * @param ldept Liste de départements à afficher.
 */
void afficherListe(ListeDept ldept)
{
    // Affichage de l'en-tête du tableau
    printf("| %-30s | %-30s | %-10s |\n", "Nom du département", "Responsable", "Places");
    printf("+--------------------------------+--------------------------------+------------+\n");

    // Parcours de la liste
    while (ldept != NULL)
    {
        // Affichage des informations du département
        printf("| %-30s | %-30s | %-10d |\n", ldept->nomDept, ldept->resp, ldept->nbP);

        // Passage au département suivant
        ldept = ldept->suiv;
    }
}