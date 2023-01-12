#include "../header/sae.h"

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

    // Allocation de la memoire pour le nouveau maillon.
    m = (MaillonDept *)malloc(sizeof(MaillonDept));
    if (!m)
    {
        printf("Erreur de malloc\n");
        exit(1);
    }
    // On ajoute le nom du departement, le nom du responsable ainsi que le nombre de places en 1ere année.
    strcpy(m->nomDept, nomDept);
    strcpy(m->resp, resp);
    m->nbP = nbP;
    if (vide(ldept))
    {
        // La liste est vide, alors m n'as pas de suiv:
        m->suiv = NULL;
        return m;
    }
    // La liste n'est pas vide, on ajoute le maillon en tete de la nouvelle liste qu'on renvois.
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
 * \brief Ajoute un maillon à la liste de départements, en ordre alphabétique.
 *
 * \param ldept La liste de départements à laquelle le maillon doit être ajouté.
 * \param nomDept Le nom du département à ajouter.
 * \param resp Le responsable du département à ajouter.
 * \param nbP Le nombre de personnes dans le département à ajouter.
 *
 * \return La nouvelle liste de départements, avec le maillon ajouté à la bonne position.
 *
 * Si la liste est vide, le maillon est ajouté en tête de la liste.
 * Si la liste contient déjà des éléments, le maillon est ajouté en ordre alphabétique selon le nom du département.
 */
ListeDept ajouterDept(ListeDept ldept, char nomDept[], char resp[], int nbP)
{
    MaillonDept *temp;

    if (vide(ldept))
        return ajouterEnTete(ldept, nomDept, resp, nbP);
    temp = ldept;
    while (temp->suiv && strcmp(temp->suiv->nomDept, nomDept) <= 0)
    {
        temp = temp->suiv;
    }
    if (strcmp(temp->nomDept, nomDept) == 0)
    {
        printf("Ce departement existe deja.\n");
        // [A completer]
        return ldept;
    }
    temp->suiv = ajouterEnTete(temp->suiv, nomDept, resp, nbP);
    return ldept;
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
 * @brief Calcule la longueur d'une liste de départements.
 * @param ldept La liste de département à compter
 * @return La longueur de la liste.
 */
int longueur(ListeDept ldept)
{
    int i = 0;
    while (ldept)
    {
        ldept = ldept->suiv;
        i++;
    }
    return i;
}

/**
 * @brief Affiche tous les départements d'une liste, avec leurs noms, leurs responsables et leur nombre de places, sous forme de tableau.
 * @param ldept Liste de départements à afficher.
 */
void afficherListe(ListeDept ldept)
{
    // Affichage de l'en-tête du tableau
    printf("| %-30s | %-30s | %-10s |\n", "Nom du departement", "Responsable", "Places");
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