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

void menuPartie4( Candidat ** tCand, VilleIut **tIut, int nbvilles, int nbcand )
{   
    int rep = 0, numero = 0, verif = 0 ;
    char rep2;
    char ville[50], departement[50];

    while ( rep != 3 )
    {
        clean;
        printf("====================================================================\n");
        printf("      Phase de resultats et de validation de candidatures\n");
        printf("====================================================================\n\n\n");

        printf(" ---> Vous etes : \n");
        printf("      -----------\n\n");
        printf(" 1.) Un candidat. \n 2.) Un responsable de departement.\n 3.) Pour quitter. ");

        scanf("%d", &rep);

        switch (rep)
        {
            case 1 :
            printf(" \n ---> Quel est votre numero de candidat : ");
            scanf("%s%*c", &numero);
            verif = menuCandidatPartie4(tCand, tIut,  numero, nbvilles, nbcand );
            miseAJourListesDepartements( tIut, nbvilles );

            while ( verif == 1 )
            {
                printf(" ---> Souhaitez-vous saisir a nouveau ? ( O / N ) : ");
                scanf("%c%*c", &rep2);

                if ( rep2 == 'o' || rep2 == 'O' )
                {
                    printf(" \n ---> Quel est votre numero de candidat : ");
                    scanf("%s%*c", &numero);
                    verif = menuCandidatPartie4(tCand, tIut,  numero, nbvilles, nbcand );
                    miseAJourListesDepartements( tIut, nbvilles );
                }
            }
            break;

            case 2 : 
            printf("\n\n ---> Dans quelle ville est votre departement : ");
            scanf("%s", ville);
            printf("\n ---> Quel est le nom de votre departement : ");
            scanf("%s", departement);

            verif = menuResponsableDeptPartie4(ville, departement, tIut, nbvilles );
            while ( verif == 1 )
            {
                printf(" ---> Souhaitez-vous saisir a nouveau ? ( O / N ) : ");
                scanf("%c%*c", &rep2);

                if ( rep2 == 'o' || rep2 == 'O')
                {
                    printf("\n\n ---> Dans quelle ville est votre departement : ");
                     scanf("%s", ville);
                    printf("\n ---> Quel est le nom de votre departement : ");
                    scanf("%s", departement);

                    verif = menuResponsableDeptPartie4(ville, departement, tIut, nbvilles );
                }
            }
            break;

            case 3 : return;
        }
    }
}

int menuResponsableDeptPartie4( char ville[], char departement[], VilleIut ** tIut, int nbvilles )
{
    int e = 0, rep;
    MaillonDeptV2 * dept; // = ( MaillonDeptV2 * ) malloc ( sizeof( MaillonDeptV2 ));
    
    printf("=======================================================================\n");
    printf("       Menu responsable de departement | phase de validation\n");
    printf("=======================================================================\n");
    // On parcours le tableau des villes pour voir si elle existe. 
    for ( int i = 0; i < nbvilles ; i++ )
    {
        // Ville trouvée, on commence à parcourir la liste des départements.
        if ( strcmp( tIut[i] -> nom, ville ) == 0 )
        {
            while ( tIut[i] -> lDeptV2 != NULL )
            {   
                // Si on trouve le departement, on le recupere pour l'utiliser par la suite. 
                if ( strcmp( tIut[i] -> lDeptV2 -> nomDept, departement ) == 0 )
                {
                    dept = tIut[i] -> lDeptV2;

                    // Le e = 1 nous confirme que le departement a été trouvé. 
                    e = 1;
                }
                else tIut[i] -> lDeptV2 = tIut[i] -> lDeptV2 -> suiv;
            }
        }
    }

    // On quitte la fonction si le departement et / ou la ville n'ont pas été trouvés. 
    if ( e == 0 )
    {
        printf(" \n\n\n ---> Departement ou ville non trouvee, retour au menu principal...\n");
        return 1;
    }

    // Maintenant on a bien le departement du responsable de departement. 

    while ( rep > 2 )
    {
        printf(" 1.) Afficher la liste des candidats admis dans votre departement. \n");
        printf(" 2.) Afficher la liste des candidats en attente dans votre departement.\n");
        printf(" 3.) Retour au menu principal.\n\n\n");
        printf(" ---> Votre reponse : ");
        scanf("%d", &rep);

        switch (rep)
        {
            case 1 : affichageListesDept( dept -> lAdmis, "admis", dept ->  nomDept );
            break;

            case 2 : affichageListesDept( dept -> lAttente, "en attente ", dept ->  nomDept );
            break;
        }
    }
    return 0;
}

void miseAJourListesDepartements( VilleIut ** tIut ,int  nbvilles )
{   
    int i = 0, libres, vide;

    // On parcours toutes les villes du tableau...
    for ( i = 0 ; i < nbvilles ; i++ )
    {
        while ( tIut[i] -> lDeptV2 != NULL )
        {   
            // // On enlève des admis les candidats qui se sont désistés et on récupère le nombre de places ainsi libérées. 
            // tIut[i] -> lDeptV2 -> lAdmis = suppressionCandidatsDessides( tIut[i] -> lDeptV2 -> lAdmis, &libres);
            
            // // On enlève de la file d'attente les candidats qui se sont désisté. 
            // tIut[i] -> lDeptV2 -> lAttente = suppressionCandidatsDessides( tIut[i] -> lDeptV2 -> lAttente, &vide );

            // for ( int e = 0 ; e < libres ; e++ )
            //     // Tant qu'il y a des places de libre, on ajoute des candidats au fond de la liste d'admis 
            //     tIut[i] -> lDeptV2 -> lAdmis = ajouterEnQueue( tIut[i] -> lDeptV2 -> lAdmis, tIut, i);
        }
    }
}

ListeCandidats ajouterEnQueue( ListeCandidats ladmis, ListeCandidats lattentes, VilleIut ** tIut, int pos )
{
    // On accède au dernier maillon non vide de la liste 
    while ( ladmis -> suiv != NULL )
        ladmis = ladmis -> suiv;
    
    // On met dans le maillon vide le premier maillon de la file d'attente. 
    ladmis -> suiv = tIut[pos] -> lDeptV2 -> lAttente;
    ladmis -> suiv -> suiv = NULL;
    tIut[pos] -> lDeptV2 -> lAttente = supprimerEnTeteCandidat( tIut[pos] -> lDeptV2 -> lAttente );

    return ladmis;
}

ListeCandidats supprimerEnTeteCandidat( ListeCandidats l )
{
    if ( l == NULL )
    {
        printf(" \n --> operation impossible \n");
        exit(1);
    }

    MaillonCandidat * aux = ( MaillonCandidat * ) malloc ( sizeof( MaillonCandidat ));
    if ( aux == NULL )
    {
        printf(" `\n --> Erreur allocation memoire\n");
        exit(1);
    }

    aux = l;
    l = l -> suiv;
    free( aux );

    return l;
}

int menuCandidatPartie4( Candidat **tCand, VilleIut **tIut,  int numero, int nbvilles, int nbcand )
{
    int i = 0, e = 0, v = 0;
    char rep;
    Candidat * c = ( Candidat * ) malloc ( sizeof( Candidat ));
    if ( c == NULL )
    {
        printf("\n --> Erreur allocation memoire...\n");
        exit(1);
    }

    // On parcours le tableau de candidat pour voir si le numero existe 
    for ( i = 0; i < nbcand ; i++ )
    {
        if ( tCand[i] -> numero == numero )
        {
            c = tCand[i];
            e = 1;
        }
    }
    if ( e == 0)
    {
        printf(" \n ---> Votre numero de candidat est introuvable. ");
        return 1;
    }

    printf("================================================================\n");
    printf("       Espace candidat | Phase de validation des voeux \n");
    printf("================================================================\n\n\n");

    // On compte le nombre de choix qui ont ete acceptes par le departement 
    v = compterNombreValidations( *c, tIut, nbvilles);

    // aucun choix n'a ete accepte, on renvoie l'utilisateur au menu car il n'a rien à faire ici 
    if ( c == 0 )
    {
        printf(" --> Vous n'avez ete accepte dans aucun de vos choix, vous allez donc etre redirige au menu principal...\n\n");
        return 2;
    }

    printf(" - Vous avez ete accepte dans %d departement de vos choix ! \n\n");
    printf(" ---> Souhaitez vous valider ( ou non ) vos voeux ? \n ");
    printf(" Attention, si vous validez un voeu les autres seront automatiquement consideres comme refuses ! )");
    printf("\n\n ---> Votre reponse ( O / N ) :");
    printf("\n      -------------------------", v);
    scanf("%c", &rep);

    if ( rep == 'o' && rep == 'O' )
    {
        *c = validationCandidat( *c, tIut, nbvilles );
        tCand[i] = c;
    }
    return 0;
}

int compterNombreValidations( Candidat c, VilleIut ** tIut, int nbvilles )
{
    int compteur = 0;
    // On parcours les choix du candidat 
    while ( c.lchoix != NULL )
    {
        // Si le choix a ete accepte par le departement, le compteur augmente de 1 
        if ( c.lchoix -> decisionDepartement == 0 ) compteur = compteur + 1;
        c.lchoix = c.lchoix -> suiv;
    }

    return compteur;
}

Candidat validationCandidat( Candidat c, VilleIut ** tIut, int nbvilles )
{
    int compteur = c.nbChoix;
    char rep;

    // Je parcours la liste de choix du candidat 
    while ( c.lchoix != NULL )
    {   
        // Si le candidat est accepté, on lui demande de valider ou non...
        if ( c.lchoix -> decisionDepartement == 0)
        {
            printf("\n --> Vous avez ete accepte au departement %s de %s, accepter le voeu ? ( O / N ) : ");
            scanf("%c%*c", &rep);

            // Dans le cas où il accepte...
            if ( rep == 'o' && rep == 'O' )
            {
                c.lchoix -> validationCandidat = 0;
                printf(" ---> Vous avez bien accepte votre voeu ! \n");
            }
            else
            {
                // On parcours le reste des choix où il a été accepté et on met la validation du candidat à 1  
                while ( c.lchoix != NULL )
                {
                    if ( c.lchoix -> decisionDepartement == 0 )
                        c.lchoix -> validationCandidat = 1;
                    c.lchoix = c.lchoix -> suiv;
                }
            }
        }
    }
    // On retourne le candidat avec ses choix de validés ( ou non...)
    return c;
}