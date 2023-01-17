#include "../header/sae.h"

/*
================================================
                    Partie 1
================================================
*/

/**
 * @brief Fonction globale qui :
 * - Charge les fichiers dans les structures adaptées
 * - Appel la fonction du menu général (visiteur) avec les données enregistrées
 * - Sauvegarde toutes les données dans les fichiers correspondants avant de terminer le logiciel
 */
void Globale(void)
{
    //printf(" \n ---> lancement de la fonction globale.... \n\n");
    Log * tLog;
    VilleIut ** tIut;
    Candidat *tCand[50];

    int nbCand = 0;
    int nbLog;
    int nbIut, nbIutMax;

    //Chargement des fichiers
    tLog = chargementLog("../donnees/log.don", &nbLog);
    tIut = chargeIutDon("../donnees/iut.don", &nbIut, &nbIutMax);

    //nbVilles = chargIutDon(tIut, 50, "../donnees/iut.don");

    //Appel du menu visiteur
    menuVisiteur(tLog, nbLog, tIut, nbIut);
    //afficherDeptIutDonne(tIut, nbIut);

    //TEST menu candidat en attendant la conexion et tout la
    //nbCand = creerCandidat(tCand, nbCand);
    //menuCandidat(tLog, nbLog, tIut, nbIut, tCand[0]); //Sauvegarde dans les fichiers
}

/**
 * @brief Charge un fichier de logs dans un tableau de structures Log
 * @param nomFichier [CHAINE DE CARACTERE] Le nom du fichier à charger
 * @return Log* [TABLEAU DYNAMIQUE DE STRUCTURE] Le tableau de structures Log contenant les logs du fichier
    */
Log * chargementLog(char * nomFichier, int * nbLog)
{
    FILE * fichier;
    Log * tLog;
    Log * tAnnexe;
    
    int nbLogMax;

    int i;

    fichier = fopen(nomFichier, "r");

    if (fichier == NULL)
    {
        printf("Erreur de fichier\n");
        exit(1);
    }

    tLog = (Log *) malloc(sizeof(Log)*5);
    nbLogMax = 5;
    
    i = 0;
    while (!feof(fichier))
    {
        // Taille physique insuffisante
        if (i == nbLogMax)
        {
            tAnnexe = realloc(tLog, sizeof(Log)*(nbLogMax + 5));
            
            // Test si le realloc n'a pas fonctionné
            if (tAnnexe == NULL)
            {
                printf("Problème de realloc\n");
                exit(1);
            }

            tLog = tAnnexe;
            nbLogMax+= 5;
        }

        fscanf(fichier, "%s %s %s", tLog[i].utilisateur, tLog[i].mdp, tLog[i].status);
        i++;
    }
    *nbLog = i;
    return tLog;
}

void test(VilleIut * tIut[], int nbVilles)
{
    for (int i = 0 ; i <nbVilles ; i++)
    {
        printf("%s\n", tIut[i]->nom);
    }
}

/**
 * @brief Cette fonction affiche le menu des options disponibles pour un visiteur
 * et demande à l'utilisateur de faire son choix en appelant la fonction
 * choixMenuVisiteur. Selon le choix de l'utilisateur, la fonction appelle la fonction correspondante
 * ou met fin à l'exécution de la fonction.
*/
void menuVisiteur(Log * tLog, int nbLog, VilleIut *tIut[], int nbIut)
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
                afficheVillesIUT(tIut, nbIut);
                wait
                clean
                break;
            case 2:
                //afficheNbPlace(tIut, nbIut);
                wait
                clean  
                break;
            case 3 :
                afficherDeptIutDonne(tIut, nbIut);
                wait
                clean
                break;
            case 4 :
                printf("En attente de je ne sais qui\n");
                //afficheIUTRecupDept(tIut, nbIut);
                break;
            case 5 :
                seConnecter(tLog, nbLog, tIut, nbIut);
                clean
                break;
            case 0 :
                actif = 0;
                break;
        }
    }
}

/**
 * @brief Cette fonction affiche le menu des options disponibles pour un candidat
 * et demande à l'utilisateur de faire son choix en appelant la fonction
 * choixMenuCandidat. Selon le choix de l'utilisateur, la fonction appelle la fonction correspondante
 * ou met fin à l'exécution de la fonction.
*/
void menuCandidat(Log * tLog, int nbLog, VilleIut *tIut[], int nbVilles, Candidat *c)
{
    int choix;
    int actif = 1;
    int decision = 0, validation = 0;
    char ville[30], dep[30];
    clean

    while(actif)
    {
        choix = choixMenuCandidat();
        clean
        switch(choix)
        {
            case 1:
                afficherUnCandidat(*c);
                getchar();
                clean
                break;
            case 2:
                afficheVillesIUT(tIut, nbVilles - 1);
                //saisirCandidature(ville, dep, tIut, nbVilles);
                c->lchoix = creerCandidature(c->lchoix, ville, dep, decision, validation, &c->nbChoix);
                c->nbChoix += 1;
                printf("%s\n", c->lchoix->ville);
                printf("Operation validee\n");
                getchar();
                clean
                break;
            case 3 :
                c->lchoix = supprimerCandidature(c->lchoix, &c->nbChoix);
                break;
            case 4 :
                //Supprimer une candidature
                break;
            case 0 :
                actif = 0;
                break;
        }
    }
}

/*
FAUX
*/
/**
    @brief Cette fonction permet à l'utilisateur de saisir les informations sur une candidature. Il doit d'abord saisir le nom de la ville,
    puis le nom du département correspondant. Si les informations saisies ne sont pas valides, l'utilisateur est invité à les resaisir.
    @param ville Nom de la ville saisie
    @param dep Nom du département saisi
    @param tiut Liste des villes et départements
    @param nbVille Nombre de villes dans la liste
    @return void
*/
/*
void saisirCandidature(char ville[], char dep[], VilleIut *tiut[], int nbVille)
{
    int pos, res;

    printf("Veuillez saisir le nom de la ville\n");
    scanf("%s", ville);
    pos = existeVille(tiut, ville, nbVille);
    while ( pos == -1)
    {
        printf("Veuillez saisir le nom de la ville\n");
        scanf("%s", ville);
        pos = existeVille(tiut, ville, nbVille);
    }
    afficherListe(tiut[pos]->lDept);
    printf("Veuilllez saisir le nom de departement\n");
    scanf("%s", dep);
    res = existeDept(tiut[pos]->lDept, dep);
    while (res == 0)
    {
        afficherListe(tiut[pos]->lDept);
        printf("Veuilllez saisir le nom de departement\n");
        scanf("%s", dep);
        res = existeDept(tiut[pos]->lDept, dep);
    }
}
*/
/**

@brief affiche le menu des candidats et renvoie le choix de l'utilisateur

@return int : le choix de l'utilisateur
*/
int choixMenuCandidat(void)
{
    int choix;

    choix = afficherMenuCandidat();
    while (choix < 0 || choix > 3)
    {
        clean
        printf("\nChoix incorrect.\n\n");
        choix = afficherMenuCandidat();
    }
    return choix;
}

/**

@brief affiche le menu pour les visiteurs et renvoie le choix de l'utilisateur

@return int : le choix de l'utilisateur
*/
int afficherMenuCandidat(void)
{
    int choix;

    printf("============================================================\n\t\t\tMENU CANDIDAT\n============================================================\n\n");
    printf("\t1. Afficher son profil\n");
    printf("\t2. Ajouter une candidature\n");
    printf("\t3. Supprimer une candidature\n");
    printf("\t0. Quitter\n");
    printf("\nChoix : ");
    scanf("%d%*c", &choix);
    return choix; 
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
int afficherMenuVisiteur(void)
{
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
 * @brief Fonction de test pour la connection
 * 
 */
void seConnecterTest(void)
{
    Log * tLog;

    char mdp[30], utilisateur[30];

    int indice, existe, nbLog, valide;

    nbLog = 0;
    tLog = chargementLog("../donnees/log.don", &nbLog); //TEMP

    banniereConnection(); // Affichage

    saisieNomUtilisateur(utilisateur); // Récupération du nom d'utilisateur

    existe = existeUtilisateur(utilisateur, &indice, tLog, nbLog);

    saisieMdp(mdp); // Récupération du mot de passe
    
    valide = mdpValide(mdp, indice, tLog);
}

/**
 * @brief Fonction de connection
 * 
 * @param tLog Tableau de Log
 * @param nbLog [Taille Logique] 
 * @param tIut Tableau de pointeur de VilleIut
 * @param nbIut [Taille Logique] 
 */
void seConnecter(Log * tLog, int nbLog, VilleIut ** tIut, int nbIut)
{
    char mdp[30], utilisateur[30];
    int existe, indice, valide;

    banniereConnection(); // Affichage
    saisieNomUtilisateur(utilisateur); // Récupération du nom d'utilisateur
    
    existe = existeUtilisateur(utilisateur, &indice, tLog, nbLog);
    if(!existe)
    {
        printf("Utilisateur inexistant !\nAppuyez sur [entrée] pour continuer...");
        scanf("%*c");
        return;
    }

    saisieMdp(mdp);

    valide = mdpValide(mdp, indice, tLog);
    
    if(valide)
    {
        clean
        printf("Connection valide en tant que %s\n", tLog[indice].status);
        
        if(strcmp(tLog[indice].status, "admin") == 0)
        {
            menuAdmin(tIut, nbIut);
        }
        if(strcmp(tLog[indice].status, "candidat") == 0)
        {
            //IntermediaireMenuCandidat(tLog, nbLog, tIut, nbIut);
        }
        if(strcmp(tLog[indice].status, "responsable") == 0)
        {
            menuResponsable(tLog, nbLog, tIut, nbIut);
        }
    }
    else
    {
        wait
    }
}

/**
 * @brief Recupere le choix dans le menu de responsable
 * 
 * @return int choix valable
 */
int choixMenuResponsable(void)
{
    int choix;

    choix = afficherMenuResponsable();

    while (choix < 0 || choix > 11)
    {
        clean
        printf("\nChoix incorrect.\n\n");
        choix = afficherMenuResponsable();
    }

    return choix;
}

/**
 * @brief Affichage du menu Responsable
 * 
 * @return int choix de l'utilisateur
 */
int afficherMenuResponsable(void)
{
    int choix;

    printf("============================================================\n\t\t\tMENU RESPONSABLE\n============================================================\n\n");
  
    printf("\t1. Afficher les candidatures pour le departement\n");
    printf("\t2. Traiter les candidatures\n");
    printf("\t3. Definir les criteres d'admission\n");
    printf("\t4. Savoir si un candidat est admis\n");
    printf("\t5. Liste des candidats en liste d'attente\n");
    printf("\t6. Liste des candidats admis\n");
    printf("\t7. Sauvegarder les admissions et la liste d'attente d'Info-Clermont\n");
    printf("\t8. Afficher toutes les villes possedant un IUT\n");
    printf("\t9. Afficher le nombre de places dans un departement donne\n");
    printf("\t10. Afficher les departements d'un IUT donne\n");
    printf("\t11. Afficher les IUT possedant un departement donne\n");
    printf("\t0. Quitter\n");
    printf("\nChoix : ");

    scanf("%d%*c", &choix);
    return choix; 
}

void menuResponsable(Log * tLog, int nbLog, VilleIut *tIut[], int nbIut)
{
    int choix;
    int actif = 1;
    
    clean

    while(actif)
    {
        choix = choixMenuResponsable();
        clean
        switch(choix)
        {
            case 1:
                printf("Afficher les candidatures pour le departement\n");
                scanf("%*c");
                clean  
                break;
            case 2:
                printf("Traiter les candidatures\n");
                scanf("%*c");
                clean  
                break;
            case 3 :
                printf("Definir critere d'admission\n");
                scanf("%*c");
                clean
                break;
            case 4 :
                printf("Candidat donné admis ?\n");
                scanf("%*c");
                clean
                break;
            case 5 :
                printf("Liste candidat en liste d'attente\n");
                scanf("%*c");
                clean
                break;
            case 6 :
                printf("Liste candidat admis\n");
                scanf("%*c");
                clean
                break;
            case 7 :
                printf("Sauvegarder admission et lsite d'attente de clermont\n");
                scanf("%*c");
                clean
                break;
            case 8:
                afficheVillesIUT(tIut, nbIut);
                printf("\nAppuyez sur entree pour continuer...");
                scanf("%*c");
                clean
                break;
            case 9:
                //afficheNbPlace(tIut, nbIut);
                printf("\nAppuyez sur entree pour continuer...");
                scanf("%*c");
                clean  
                break;
            case 10 :
                afficherDeptIutDonne(tIut, nbIut);
                break;
            case 11 :
                //afficheIUTRecupDept(tIut, nbIut);
                break;
            case 0 :
                actif = 0;
                break;
        }
    }
}


/**
 * @brief Vérifie si un utilisateur existe dans le tableau de structures de log.
 * 
 * @param utilisateur [CHAINE DE CARACTERES] Le nom de l'utilisateur à rechercher.
 * @param indice [POINTEUR] Pointeur vers un entier qui sera modifié pour stocker l'indice de l'utilisateur s'il est trouvé.
 * @param tLog [TABLEAU] Tableau de structures de log.
 * @param nbLog [Taille Logique] Nombre d'éléments dans le tableau de structures de log.
 * 
 * @return int 1 --> l'utilisateur existe | 0 --> l'utilisateur n'existe pas
 */
int existeUtilisateur(char * utilisateur, int * indice, Log * tLog, int nbLog)
{
    for (int i = 0 ; i < nbLog ; i++)
    {
        if (strcmp(tLog[i].utilisateur,utilisateur) == 0)
        {
            *indice = i;
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Valide si le mot de passe donné correspond au mot de passe enregistré dans la structure de log.
 * 
 * @param mdp [CHAINE DE CARACTERES] Le mot de passe à valider.
 * @param indice L'indice de la structure de log à utiliser pour la vérification.
 * @param tLog [TABLEAU] Le tableau de structures de log.
 * 
 * @return int 1 --> le mot de passe correspond | 0 --> le mot de passe ne correspond pas
 */
int mdpValide(char * mdp, int indice, Log * tLog)
{
    if (strcmp(tLog[indice].mdp, mdp) == 0) return 1;
    else return 0;
}

/**
 * @brief Affichage de la bannière de connexion.
 */
void banniereConnection(void)
{
    clean
    printf("------------------------------------------------------------\n\t\t\tSE CONNECTER\n------------------------------------------------------------\n\n");
}

/**
 * @brief Saisie du nom d'utilisateur par l'utilisateur.
 * 
 * Affiche une invite à l'écran et enregistre la saisie de l'utilisateur
 * dans la chaîne de caractères passée en paramètre.
 * 
 * @param utilisateur [POINTEUR] Pointeur vers la chaîne de caractères où enregistrer
 * la saisie de l'utilisateur.
 */
void saisieNomUtilisateur(char * utilisateur)
{
    printf("\tNom d'utilisateur : ");
    scanf("%s%*c", utilisateur);
    printf("\n");
}

/**
 * @brief Saisie du mot de passe par l'utilisateur.
 * 
 * Affiche une invite à l'écran et enregistre la saisie de l'utilisateur
 * dans la chaîne de caractères passée en paramètre.
 * 
 * @param mdp [POINTEUR] Pointeur vers la chaîne de caractères où enregistrer
 * la saisie de l'utilisateur.
 */
void saisieMdp(char * mdp)
{
    printf("\tMot de passe : ");
    scanf("%s%*c", mdp);
    printf("\n");
}

/**
 * @brief Saisie le nombe de place du departement
 *
 * @return le nombre de places
 */
int saisirNbPlaceDep(void)
{
    int nbP;
    printf("Veuillez saisir le nouveau nombre de places :\n");
    scanf("%d", &nbP);
    return nbP;
}

void saisirRespDep(char resp[])
{
    printf("Veuillez saisir le nom du responsable\n");
    fgets(resp, 30, stdin);
    resp[strlen(resp) - 1] = '\0';
}

/**
 * @brief Modifie le nom du responsable d'un département dans un IUT
 * 
 * @param tVilleIut tableau de pointeurs sur les structures VilleIut
 * @param nbVilles nombre de villes dans le tableau villeIut
 * @param ville nom de la ville où se trouve l'IUT
 * @param nomDept Nom du département où l'on modifie le nom du responsable 
 * @param nvNomResp nouveau nom de responsable
 * 
 * @return 1 si le nom du responsable a été trouvé et modifié, 0 sinon
 */
int modifieRespDept(VilleIut *tiut[], int nbVilles, char ville[], char nomDept[], char nvNomResp[])
{
    // Recherche de la ville et du département
    int i;
    for (i = 0; i < nbVilles; i++)
    {
        if (strcmp(tiut[i] -> nom, ville) == 0)
        {
            // Ville trouvée, recherche du département
            MaillonDept *dept = tiut[i] -> lDept;

            while ( dept != NULL && strcmp( dept -> nomDept, nomDept) != 0)
            {
                dept = dept ->suiv;
            }
            if (dept != NULL)
            {
                // Département trouvé, modification du nom du responsable du département
                strcpy(dept->resp, nvNomResp);
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
*@brief Affiche les départements d'un IUT donné
*@param tiut tableau des villes d'IUT
*@param nbVille nombre de villes d'IUT dans le tableau
*@return void
*/
void afficherDeptIutDonne(VilleIut *tiut[], int nbVille)
{
    int res;
    char nom[30];

    afficheVillesIUT(tiut, nbVille);
    printf("Veuillez saisir le nom de l'iut que vous voulez afficher.\n");
    scanf("%s%*c", nom);
    res = existeVille(tiut, nom, nbVille);
    if (res == -1)
    {
        printf("Cet IUT n'existe pas\n");
        wait
        return ;
    }
    afficherListe(tiut[res]->lDept);
}

/**
 * @brief Affiche les IUT possédant un département spécifique.
 *
 * @param tiut tableau de pointeurs sur les structures VilleIut
 * @param nbVilles nombre de villes dans le tableau villeIut
 * @param nomDept nom du département à rechercher
 */
void afficheIUTDept(VilleIut *tiut[], int nbVilles, char *nomDept)
{
    clean;
    printf("==========================================================================\n");
    printf("           Affiche les IUT possédant un departement specifique \n");
    printf("==========================================================================\n");


    int i, e = 0 ;
    for (i = 0; i < nbVilles; i++)
    {
        // Parcours de la liste chaînée de départements de la ville
        MaillonDept *dept = tiut[i] -> lDept;
        while (dept != NULL)
        {
            if (strcmp(dept->nomDept, nomDept) == 0)
            {
                // Département trouvé, affichage de la ville
                printf(" -> IUT de %s\n", tiut[i] -> nom);
                e = 1;
            }

            dept = dept->suiv;
        }
    }
    if ( e == 0 ) printf(" \n ---> Departement inexistant...\n");

    printf("\n\n\n");
}

/**
    * @brief Affiche les villes qui ont des IUT.
    * @param villeIut tableau de pointeurs sur les structures VilleIut
    * @param nbVilles nombre de villes dans le tableau villeIut
*/
void afficheVillesIUT(VilleIut *tiut[], int nbVilles)
{
    clean
    printf("==============================================================\n");
    printf("                 Villes possedant un IUT  \n ");
    printf("==============================================================\n");

    for (int i = 0; i < nbVilles; i++)
    {
        // Affichage du nom de la ville
    printf(" -> %s\n", tiut[i]-> nom);
    }
}

/**
 * @brief Affiche les IUT et le nombre de places associé pour un département donné
 * 
 * @param tVilleIut tableau de pointeurs sur les structures VilleIut
 * @param nbVilles nombre de villes dans le tableau villeIut
 * @param nomDept nom du département à rechercher
 */
void afficheNbPlacesDep(VilleIut *tiut[], int nbVilles, char nomDept[])
{
    int i;
    for (i = 0; i < nbVilles; i++)
    {
        // Parcours de la liste chaînée de départements de la ville
        MaillonDept *dept = tiut[i] -> lDept;
        while (dept != NULL)
        {
            if (strcmp(dept->nomDept, nomDept) == 0)
            {
                // Département trouvé, affichage de la ville et de son nombre de places
                printf("IUT de %s avec %d places.\n", tiut[i] -> nom, tiut[i] -> lDept -> nbP);
                break;
            }
            dept = dept->suiv;
        }
    }
}

int existeVille(VilleIut *tIut[], char ville[], int nbvilles )
{
    int i = 0;

    //recherche de la ville 
    for( i = 0; i < nbvilles; i ++ )
    {
        if ( strcmp( tIut[i] -> nom, ville ) == 0 ) return i; // ville trouvée...
    }
    return -1;
}


/**
 * Affiche et gère le menu administrateur.
 *
 * @param villeIut tableau de pointeurs sur les structures VilleIut
 * @param nbVilles nombre de villes dans le tableau villeIut
 */
void menuAdmin(VilleIut **villeIut, int nbVilles)
{
    int choix;
    char ville[30], nomDep[30], resp[30];
    int pos, nbP;
    MaillonDept *dep;

    do
    {
        // Affichage du menu
        clean
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
        scanf("%d%*c", &choix);

        // Traitement du choix de l'utilisateur
        switch (choix)
        {
            case 1:
                pos = saisirVille(villeIut, nbVilles, ville);
                dep = saisirDep(villeIut[pos]->lDept);
                nbP = saisirNbPlaceDep();
                dep->nbP = nbP;
                break;
            case 2:
                pos = saisirVille(villeIut, nbVilles, ville);
                nbP = saisirNouvDep(nomDep, resp);
                ajouterDept(villeIut[pos]->lDept, nomDep, resp, nbP);
                break;
            case 3:
                pos = saisirVille(villeIut, nbVilles, ville);
                dep = saisirDep(villeIut[pos]->lDept);
                villeIut[pos]->lDept = supprimerDept(villeIut[pos]->lDept, dep->nomDept);
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
                pos = saisirVille(villeIut, nbVilles, ville);
                dep = saisirDep(villeIut[pos]->lDept);
                saisirRespDep(resp);
                strcpy(dep->resp, resp);

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

/**
 * @brief saisie les donnees d'un departement
 * 
 * @param nomDep nom du departement
 * @param resp nom du responsable
 * @return int nombre de places
 */
int saisirNouvDep(char *nomDep, char *resp)
{
    int nbP;

    printf("Veuillez saisir le nom du nouveau departement\n");
    scanf("%s%*c", nomDep);
    printf("Veuillez saisir le nom du responsable\n");
    scanf("%s%*c", resp);
    printf("Veuillez saisir le nombre de places du departement\n");
    scanf("%d", &nbP);
    return nbP;

}

int saisirVille(VilleIut *tiut[], int nbVilles, char ville[])
{
    int res;

    afficheVillesIUT(tiut, nbVilles);
    printf("Veuillez saisir la ville :\n");
    scanf("%s%*c", ville);
    res = existeVille(tiut, ville, nbVilles);
    while (res == -1)
    {
        clean
        afficheVillesIUT(tiut, nbVilles);
        printf("Veuillez saisir la ville :\n");
        scanf("%s%*c", ville);
        res = existeVille(tiut, ville, nbVilles);
    }
    return res;
}

MaillonDept *saisirDep(ListeDept ldept)
{
    MaillonDept *m = ldept;
    char nomDep[30];
    int res;

    afficherListe(ldept);
    printf("Veuillez saisir un departement :\n");
    scanf("%s%*c", nomDep);
    res = existeDept(ldept, nomDep);
    while (res == 0)
    {
        afficherListe(ldept);
        printf("Invalide\nVeuillez saisir un departement :\n");
        scanf("%s%*c", nomDep);
        res = existeDept(ldept, nomDep);
    }
    while (m)
    {
        if (strcmp(m->nomDept, nomDep) == 0)
            return m;
        m = m->suiv;
    }
    return m;
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
 void afficherUnCandidat(Candidat candidat)
{
    int c = 1;
    printf("Candidat numero  %7d ", candidat.numero);
    printf(" | Nom : %10s | ", candidat.nom);
    printf(" Prenom : %10s ", candidat.prenom);
    printf(" | Notes : %.2f %.2f %.2f %.2f | ", candidat.notes[0], candidat.notes[1], candidat.notes[2], candidat.notes[3]);
    printf(" Nombre de choix : %d\n\n", candidat.nbChoix);

    printf(" \n Choix du candidat :\n");
    printf(   " -------------------\n\n");

    while ( candidat.lchoix != NULL )
    {
        printf(" %d.) Iut : %10s ; departement : %10s ; decision Departement : %d ; validation candidat : %d\n",c,
               candidat.lchoix -> ville, candidat.lchoix -> departement, candidat.lchoix -> decisionDepartement, 
               candidat.lchoix -> validationCandidat);
        
        candidat.lchoix=candidat.lchoix->suiv;
        c=c+1;
    }

    printf(" \n\n");
} 

/**
 * @brief Affiche la liste des candidats
 * 
 * @param candidats Le tableau de candidats à afficher
 * @param nbCandidats Le nombre de candidats dans le tableau
 */
void afficherCandidats(Candidat **candidats, int nbCandidats)
{
    for (int i = 0; i < nbCandidats; i++)
    {
        printf("\nCandidat numero %8d | Nom : %10s | Prenom : %10s \n", candidats[i] -> numero,
         candidats[i] -> nom, candidats[i] -> prenom);
    }
}

/**
 * @brief Permet de créer un candidat  
 * 
 * @param tCand Tableau de pointeur sur une structure de candidat
 * @param nbCandidats nombre de candidats créés
 * 
 * @return Retourne le nombre de candidats 
 */
int creerCandidat(Candidat *tCand[], int nbCandidats)
{
    int i=0;
    Candidat *c;
 
    c = (Candidat *) malloc (sizeof(Candidat));
    if(c==NULL)
    {
        printf("Probleme malloc\n");
        exit(1);
    }
    c->numero = nbCandidats+1;
    printf("Le numero du candidat entrain d'etre cree est : %d\n", c->numero);
    printf("Nom du candidat (peut contenir des espaces): ");
    fgets(c->nom, 50, stdin);
    c->nom[strlen(c->nom) - 1] = '\0';
    printf("Prenom du candidat (peut contenir des espaces): ");
    fgets(c->prenom, 50, stdin);
    c->prenom[strlen(c->prenom) - 1] = '\0';
    i=0;
    while(i<4)
    {
        printf("Rentrez la note numero %d : ", i+1);
        scanf("%f", &c->notes[i]);
        while(c->notes[i] < 0 || c->notes[i] > 20)
        {
            printf("Erreur, la note doit etre comprise entre 0 et 20.\nRessaisir la note numero %d : ", i+1);
            scanf("%f", &c->notes[i]);
        }
        i = i + 1;
    }
    c->nbChoix = 0;
    c->lchoix = listenouvC();
    tCand[nbCandidats] = c;    
    return nbCandidats + 1;
}

/**
 * @brief Supprime un choix de la liste de choix d'un candidat
 * 
 * @param lchoix la liste de choix à modifier 
 * @param nbchoix le nombre de choix dans la liste de choix
 *
 * @return la liste avec le choix en moins 
 */
lChoix supprimerCandidature( lChoix l, int *nbchoix)
{
    lChoix temp = l;

    if ( l == NULL )
    {
        printf(" \n --> Le candidat ne possede aucun choix...\n\n");
        return l;
    }

    printf("\n Voici les choix du candidat : \n");
    printf(  " -----------------------------\n\n");
    int rep = 0, c = 0;

    for( int i = 0; i < *nbchoix; i ++ )
    {
        printf(" %d.) Ville : %10s ; Departement : %10s \n",i + 1, l -> ville, l -> departement);
        l = l -> suiv;
    }

    printf(" \n\n --> Quel choix supprimer ? : ");
    scanf("%d%*c", &rep);
    temp = supprmRecru( temp, rep );
    *nbchoix -= 1;
    return temp;
}

lChoix supprmRecru( lChoix l, int rep )
{
    if ( rep == 1 )
    {
        l = supprimerEnTeteC( l );
        return l;
    }
    
    l -> suiv = supprmRecru( l -> suiv, rep -1 );
    
    return l;
}

/**
 * @brief Permet de créer une candidature à un candidat
 * 
 * @param choixCandid Liste de candidature
 * @param ville nom de la ville de la candidature
 * @param departement nom du departement de la candidature
 * @param decision 0 par defaut
 * @param validation 0 par defaut
 * @return Liste mis à jour
 */
lChoix creerCandidature(lChoix choixCandid, char ville[], char departement[], int decision, int validation, int *nbchoix)
{
    if(choixCandid == NULL)
        return ajouterEnTeteC(choixCandid, ville, departement, decision, validation);
    if(strcmp(ville, choixCandid->ville) < 0) 
        return ajouterEnTeteC(choixCandid, ville, departement, decision, validation);
    if(strcmp(ville, choixCandid->ville) == 0 && strcmp(departement, choixCandid->departement) < 0)
        return ajouterEnTeteC(choixCandid, ville, departement, decision, validation);
    choixCandid->suiv = creerCandidature(choixCandid->suiv, ville, departement, 0, 0, nbchoix);
    *nbchoix += 1;
    return choixCandid;
}

/*
================================================
                    Partie 3
================================================
*/

/**
 * \brief Permet de convertir la liste de departement des VilleIut de la partie 1
        dans la nouvelle version pour correspondre à la partie 3. Et la fonction 
        définie au passage le nombre maximal d'admis pour le département et sa 
        moyenne minimale à obtenir pour y accéder. 
 * \param ldept La liste de départements de la partie 1 pour une villeIut 
 * \return La nouvelle liste de départements adaptée à la partie 3.
 *
 */
ListeDeptV2 configurationDeptV2( ListeDept ldept )
{
    ListeDeptV2 lDeptV2 = NULL;

    if ( ldept == NULL ) return lDeptV2;

    while ( ldept != NULL )
    {
        MaillonDept * aux = ( MaillonDept * ) malloc ( sizeof( MaillonDept ));
        if ( aux == NULL )
        {
            printf(" \n ---> Erreur d'allocation memoire... \n");
            exit(1);
        }

        MaillonDeptV2 * mV2 = ( MaillonDeptV2 * ) malloc ( sizeof( MaillonDeptV2 ));
        if ( mV2 == NULL)
        {
            printf("\n --> Erreur d'allocation memoire...\n");
            exit(1);
        }

        printf(" \n Quelle est la moyenne minimale a avoir pour le departement %10s  ? : ", ldept -> nomDept);
        scanf("%d", mV2 -> moyMin);

        printf(" \n Quel est le nombre maximal d'admis pour le departement %10s ", ldept -> nomDept);
        scanf("%d", mV2 -> admisMax);

        strcpy( ldept -> nomDept, mV2 -> nomDept );
        strcpy( ldept -> resp, mV2 -> resp );
        mV2 -> nbP = ldept -> nbP;

        lDeptV2 -> lAdmis = NULL;
        lDeptV2 -> lAttente = NULL;
        
        mV2 -> suiv = lDeptV2;
        lDeptV2 = mV2;

        aux = ldept;
        ldept = ldept -> suiv;
        free(aux);
    }
    
    return lDeptV2;
}

/*
FAUX
*/
/*
void afficheNbPlace(VilleIut ** tIut, int nbIut)
{
    char ville[30];
    char dep[30];
    int i, res;
    MaillonDept *aux;

    printf("Veuillez saisir un Iut\n");
    scanf("%s", ville);
    i = existeVille(tIut, ville, nbIut);
    if (i == -1)
    {
        printf("Veuillez saisir un Iut\n");
        scanf("%s", ville);
        i = existeVille(tIut, ville, nbIut);
    }
    printf("Veuillez saisir un departement\n");
    scanf("%s", dep);
    res = existeDept(tIut, nbIut);
    while (res == -1)
    {
        printf("Veuillez saisir un departement\n");
        scanf("%s", dep);
        res = existeDept(tIut, nbIut);
    }
    aux = tIut[i]->lDept;
    while (aux)
    {
        if (strcmp(aux, dep) == 0)
        {
            printf("%d", aux->nbP);
            return ;
        }
    }
}
*/
/*
================================================
                    Partie 3
================================================
*/
