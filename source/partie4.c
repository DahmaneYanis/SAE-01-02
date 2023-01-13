#include "../header/sae.h"

// ==============================================================================
// Partie 4 
// ==============================================================================

/**
 * @brief Affiche une liste de candidats après l'avoir triée par ordre alphabétique 
 * 
 * @param lcand liste de candidats à trier et afficher 
 * @param type type de liste à afficher ( en attente ou admis )
 * @param nomDept nom du departement dont est issu la liste
 */
void affichageListesDept( ListeCandidats lcand, char * type, char * nomDept )
{
    lcand = trierListeCandidats( lcand );

    printf( " Liste des candidats %s du departement %10s  \n -------------------------------------------------------\n\n", type, nomDept);

    while ( lcand != NULL)
    {
        printf("  | Nom : %10s | Prenom : %10s | Numero : %8s |\n", 
        lcand -> candidat.nom, lcand -> candidat.prenom, lcand -> candidat.numero);

        lcand = lcand -> suiv;
    }
}
/**
 * @brief Trie par ordre alphabétique les candidats d'une liste 
 * 
 * @param l liste de candidats à trier.
 * 
 * @return  La liste triée 
 */
ListeCandidats trierListeCandidats( ListeCandidats l )
{
    ListeCandidats nvL;

    while ( l != NULL )
    {
        nvL = insertionCroissanteCand( nvL, l );
        l = l -> suiv;
    }

    return nvL;
}

/**
 * @brief Permet d'insérer un nouveau Maillon de candidats dans la liste par ordre alphabétique 
 * @param l la liste dont est issu le maillon à insérer
 * @param nvL la nouvelle liste où est inséré le maillon
 * 
 * @return  La nouvelle liste avec le maillon au bon endroit
 */
ListeCandidats insertionCroissanteCand( ListeCandidats nvL, ListeCandidats l )
{
    if ( l == NULL)
    {
        nvL = insertionTeteCand( nvL,  l );
        return nvL;
    }

    if ( strcmp( l -> candidat.nom, nvL -> candidat.nom ) < 0 )
    {
        nvL = insertionTeteCand( nvL, l );
        return nvL;
    }

    if ( strcmp( l -> candidat.nom, nvL -> candidat.nom ) == 0 )
    {
        if ( strcmp( l -> candidat.prenom, nvL -> candidat.prenom ) < 0 )
        {
            nvL = insertionTeteCand( nvL, l );
            return nvL;
        }
    }

    nvL -> suiv = insertionCroissanteCand( nvL -> suiv, l );
    return nvL;
}
        
/**
 * @brief Insère en tête de la nouvelle liste un nouveau maillon
 * @param l liste d'où est issu le nouveau maillon à intégrer
 * @param nvL Liste où est insérer le nouveau Maillon 
 * @return  La nouvelle liste avec le maillon au bon endroit  
 */
ListeCandidats insertionTeteCand( ListeCandidats nvL, ListeCandidats l )
{
    MaillonCandidat * m = ( MaillonCandidat * ) malloc ( sizeof( MaillonCandidat ));
    if ( m == NULL )
    {
        printf("\n -> Erreur allocation memoire...\n");
        exit(1);
    }

    m -> candidat = l -> candidat;
    m -> suiv = nvL;
    nvL = m;
    free( l );

    return nvL;
}
