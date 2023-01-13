#include "../header/sae.h"


/**
 * @brief Ajoute un choix à la liste de choix 
 * @param lchoix juste de choix auquel un  mayon est rajouté
 * @param ville La ville du nouveau choix
 * @param departement Le departement du nouveau choix
 * @param decision La décision du département pour le choix
 * @param validation La validation du candidat pour le choix 
 
 * @return La liste avec le nouveau maillon
 */
lChoix ajouterEnTeteC( lChoix lchoix, char ville[], char departement[], int decision, int validation)
{
    Choix * c = ( Choix * ) malloc ( sizeof ( Choix ));
    if ( c == NULL )
    {
        printf("\n --> Erreur d'allocation memoire \n");
        exit(1);
    }

    strcpy( c -> ville,  ville );
    strcpy( c -> departement, departement );
    c -> decisionDepartement = decision;
    c -> validationCandidat = validation;

    c -> suiv = lchoix;
    lchoix = c;

    return lchoix;
}

/**
 * @brief supprime un maillon de la liste 
 * @param lchoix juste de choix auquel un  mayon est rajouté
 *
 * @return La liste avec le maillon en moins
 */
lChoix supprimerEnTeteC( lChoix lchoix )
{
    Choix * aux;
    if ( lchoix == NULL )
    {
        printf(" \n --> operation impossible \n");
        exit(1);
    }

    aux = lchoix;
    lchoix = lchoix -> suiv;
    free( aux );

    return lchoix;
}
/**
 * @brief Initialise une liste vide 
 * @return La liste vide
 */
lChoix listenouvC()
{
    lChoix l;
    l = NULL;
    return l;
}



