#include "../header/sae.h"

/**
 * \brief Permet de convertir la liste de departement des VilleIut de la partie 1
        dans la nouvelle version pour correspondre à la partie 3. Et la fonction 
        définie au passage le nombre maximal d'admis pour le département et sa 
        moyenne minimale à obtenir pour y accéder. 
 * \param ldept La liste de départements de la partie 1 pour une villeIut 
 * \return La nouvelle liste de départements adaptée à la partie 3.
 *
 */
ListeDeptV2 configurationDeptV2( ListeDept ldept, float moy )
{
    // On crée le liste de la seconde version des maillons de départements et on la met à null pour commencer 
    ListeDeptV2 lDeptV2 = NULL;

    // Si la liste de base est nulle on renvoie la version 2 de la liste nulle aussi 
    if ( ldept == NULL ) return lDeptV2;

    // On parcours tous les maillons de la liste de base 
    while ( ldept != NULL )
    {
        // utilisé par la suite pour libérer les maillons de la première liste au fur et à mesure 
        MaillonDept * aux = ( MaillonDept * ) malloc ( sizeof( MaillonDept ));
        if ( aux == NULL )
        {
            printf(" \n ---> Erreur d'allocation memoire... \n");
            exit(1);
        }

        // On crée au fur et à mesure des maillons pour la seconde liste 
        MaillonDeptV2 * mV2 = ( MaillonDeptV2 * ) malloc ( sizeof( MaillonDeptV2 ));
        if ( mV2 == NULL)
        {
            printf("\n --> Erreur d'allocation memoire...\n");
            exit(1);
        }

        // On transfère les informations de la première version du maillon vers la seconde version. 
        mV2 -> admisMax = ldept -> nbP; // initialement on considère que ces valeurs sont les mêmes ( mais possible de les changer après )
        mV2 -> moyMin = moy; // Initialiement le département possède une moyenne minimale définie en paramètre de la fonction
        strcpy( ldept -> nomDept, mV2 -> nomDept );
        strcpy( ldept -> resp, mV2 -> resp );
        mV2 -> nbP = ldept -> nbP;

        // on itinialise les listes qui stockeront les candidats
        lDeptV2 -> lAdmis = NULL;
        lDeptV2 -> lAttente = NULL;
        
        // on ajoute la nouvelle version du maillon en tête de la nouvelle liste 
        mV2 -> suiv = lDeptV2;
        lDeptV2 = mV2;

        aux = ldept;
        // on passe au maillon suivant 
        ldept = ldept -> suiv;
        // on supprimer au fur et à mesure la première liste et ses maillons 
        free(aux);
    }

    return lDeptV2; // on donne la seconde version de la liste 
}



void menuPartie3( VilleIut ** tIut, int nbvilles )
{
    int rep = 0, verif = 0;
    char rep2, ville[50], departement[50];
    // On commence par transformer la version 1 des maillons département dans leur version 2 
    for ( int e = 0 ; e < nbvilles ; e++ )
        // On configure chaque département et on donne 13 de moy à tous pour commencer...
        tIut[e] -> lDeptV2 = configurationDeptV2( tIut[e] -> lDept, 13);

    while ( rep <= 2 )
    {
        printf("=======================================================================\n");
        printf("       Menu phase de traitement des dossiers de candidatures\n");
        printf("=======================================================================\n\n\n");

        printf(" ---> Vous etes : \n      -----------\n\n");
        printf(" 1.) Responsable d'admission pour un departement. \n 2.) Candidat souhaitant consulter son dossier. ");

        printf("\n\n\n ---> Votre reponse : ");
        scanf("%d%*c", &rep);

        switch(rep)
        {
            case 1 : 
                printf("\n\n ---> Dans quelle ville est votre departement : ");
                scanf("%s", ville);
                printf("\n ---> Quel est le nom de votre departement : ");
                scanf("%s", departement);
                verif = menuResponsableAdmissionPartie3( tIut, nbvilles, ville, departement );
                while ( verif == 1 )
                {
                    printf(" \n ---> Souhaitez-vous recommencer ( 0 / N ) : ");
                    scanf("%c", &rep2);

                    if ( rep2 == 'o' || rep2 == 'O' )
                    {
                        printf("\n\n ---> Dans quelle ville est votre departement : ");
                        scanf("%s", ville);
                        printf("\n ---> Quel est le nom de votre departement : ");
                        scanf("%s", departement);
                        verif = menuResponsableAdmissionPartie3( tIut, nbvilles, ville, departement );
                    }
                }
            break;

            
            case 2 :
                // menuCandidat( );
                printf(" Appeller le menu candidat......\n");
            break;
        }

    }
}

int menuResponsableAdmissionPartie3( VilleIut ** tIut, int nbVilles, char ville[], char departement[] )
{
    MaillonDeptV2 * dept;
    int rep, e = 0, i ;
        // On parcours le tableau des villes pour voir si elle existe. 
    for ( i = 0; i < nbVilles ; i++ )
    {
        // Ville trouvée, on commence à parcourir la liste des départements.
        if ( strcmp( tIut[i] -> nom, ville ) == 0 )
        {
            while ( tIut[i] -> lDeptV2 != NULL || e == 1 )
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

    printf("============================================================================\n");
    printf("    Menu responsable d'admission | phase de traitement des candidatures\n ");
    printf("============================================================================\n");

    printf("\n - Iut de : ¨%s , departement : %s", tIut[i] -> nom, tIut[i] -> lDeptV2 -> nomDept);
    printf("\n - Nombre de places en admission : %d, moyenne minimale a posseder : %f. ");

    printf("\n\n\n Que souhaitez-vous faire ? \n --------------------------\n\n");
    printf(" 1.) Définir nouvelle moyenne pour votre departement. \n 2.) Definir nouveau nombre admis pour votre departement.\n 3.) Quitter.\n\n\n ---> Votre reponse : ");

    scanf("%d", &rep);

    switch(rep)
    {
        case 1 : 
        // On met à jour la moyenne du département
         tIut[i] -> lDeptV2 = miseAJourMoyenneDept( tIut[i] -> lDeptV2 );
        break;

        case 2 : 
        // On met à jour le nombre d'admis du départemement 
        tIut[i] -> lDeptV2 =  miseAJourNbAdmisDept( tIut[i] -> lDeptV2 );
        break;

        case 3 : return 0;
    }
}

ListeDeptV2 miseAJourMoyenneDept( ListeDeptV2 l )
{
    printf("\n --> Quel moyenne minimale souhaitez-vous donner au departement : ");
    scanf("%f", l -> moyMin );

    return l;
}

ListeDeptV2 miseAJourNbAdmisDept( ListeDeptV2 l )
{
    printf("\n --> Quel nombre d'admis maximal souhaitez-vous donner au departement  : ");
    scanf("%f", l -> admisMax );

    return l;
}