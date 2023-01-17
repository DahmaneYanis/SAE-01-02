#include "../header/sae.h"

/**
 * @brief Charge les données d'un fichier dans un tableau de pointeur de VilleIut
 * @param nomFichier [CHAINE DE CARACTERES] Nom du fichier contenant les données
 * @param nbIut [POINTEUR - Taille Logique] Nombre d'IUT
 * @param nbMax [POINTEUR - Taille Physique Dynamique] 
 * @return Tableau de pointeur de VilleIut rempli avec les données du fichier
 */
VilleIut ** chargeIutDon(char nomFichier[], int * nbIut, int * nbMax)
{
    FILE * fichier;
    VilleIut ** tIut;
    int i = 0;

    fichier = fopen(nomFichier, "r");

    if (fichier == NULL) 
    {
        printf("Error: Ouverture du fichier %s impossible\n", nomFichier);
        exit(1);
    }

    // Si tout s'est bien passé dans l'ouverture de fichier

    tIut = initialiseTabIut();

    *nbMax = 5;



    i = 0;
    while (!feof(fichier))
    {
        // Taille max atteinte ?
        if (i+1 == *nbMax)
        {
            tailleSupTabIut(tIut, nbMax); // Augmentation de la taille avec un realloc
        }

        tIut[i] = lireIut(fichier); // Lecture d'un IUT
        
        i++;
    }

    *nbIut = i-1;
    fclose(fichier);

    fusionIut(tIut, nbIut);

    return tIut;
}

/**
 * @brief Initialise un tableau de pointeur de VilleIut
 * @return Tableau de pointeur de VilleIut
 */
VilleIut ** initialiseTabIut(void)
{
    VilleIut ** tIut = (VilleIut **) malloc(sizeof(VilleIut *)*5);
    
    if (tIut == NULL)
    {
        printf("Error: Probleme d'allocation dynamique du tableau\n");
        exit(1);
    }

    return tIut;
}

/**
 * @brief Augmente la taille d'un tableau de pointeur de VilleIut
 * @param tIut Tableau de pointeur de VilleIut
 * @param nbMax [POINTEUR - Taille Physique Dynamique] Nouvelle taille max
 */
void tailleSupTabIut(VilleIut ** tIut, int *nbMax)
{
    VilleIut **aux;

    *nbMax+=5;
    aux = (VilleIut **) realloc(tIut, *nbMax);
    if (aux == NULL)
    {
        printf("Error : Probleme de realloc\n");
        exit(1);
    }

    tIut = aux;
}

/**
 * @brief Lit les données d'un IUT dans un fichier et les stocke dans une VilleIut
 * @param fichier [FICHIER] Données de l'IUT
 * @return une VilleIut rempli avec les données lues
 */
VilleIut * lireIut (FILE * fichier)
{
    VilleIut * iut;

    iut = initialiseIut();

    lectureIut(iut, fichier);

    return iut;
}

/**
 * @brief Initialise une VilleIut
 * @return VilleIut initialisé
 */
VilleIut * initialiseIut(void)
{
    VilleIut * iut;

    iut = (VilleIut *)malloc(sizeof(VilleIut));
    if (iut == NULL)
    {
        printf("Error : Probleme d'allocation dynamique de l'IUT\n");
        exit(1);
    }

    return iut;
}

/**
 * @brief Lit les données d'un IUT dans un fichier et les stocke dans une VilleIut
 * @param iut [POINTEUR] Pointeur vers une VilleIut où stocker les données
 * @param fichier [FICHIER] Données de l'IUT
 */
void lectureIut(VilleIut * iut, FILE * fichier)
{
    fscanf(fichier, "%s", iut->nom);

    iut->lDept = lireDep(fichier);
}

/**
 * @brief Lit les données d'un département dans un fichier et les stocke dans une liste chaînée
 * @param fichier [FICHIER] Données du département
 * @return une liste chaînée contenant les données du département
 */
ListeDept lireDep(FILE * fichier)
{
    ListeDept ldept;

    ldept = initialiseDep();

    lectureDep(ldept, fichier);
}

/**
 * @brief Initialise une liste chaînée de départements
 * @return la liste chaînée initialisée
 */
ListeDept initialiseDep(void)
{
    ListeDept ldept = (MaillonDept *) malloc(sizeof(MaillonDept));
    if (ldept == NULL)
    {
        printf("Erreur : Erreur de malloc ldept\n");
        exit(1);
    }

    return ldept;
}

/**
 * @brief Lit les données d'un département dans un fichier et les stocke dans une structure de Departement
 * @param ldept Liste chaînée où stocker les données
 * @param fichier [FICHIER] Données du département
 */
void lectureDep(ListeDept ldept, FILE * fichier)
{
    // Lecture des données du département 
    fscanf(fichier, "%s %d ", ldept->nomDept, &ldept->nbP);
    fgets(ldept->resp, 30, fichier);
    ldept->resp[strlen(ldept->resp)-1] = '\0';
    ldept->suiv = NULL;
}

/**
 * @brief Fonction de test de chargement
 */
void testCharge(void)
{
    int nbIut, nbMax;
    VilleIut ** tIut = chargeIutDon("../donnees/iut.don", &nbIut, &nbMax);
    fusionIut(tIut, &nbIut);

    for (int i = 0; i < nbIut; i++)
    {
        printf("\nVille : %s\n", tIut[i]->nom);
        afficherListe(tIut[i]->lDept);
    }
}

/**
 * @brief Fusionne la liste de département de toutes les villes du même nom de tIut
 * 
 * @param tIut Tableau de pointeur de VilleIut
 * @param nbIut [Taille Logique]
 */
void fusionIut(VilleIut ** tIut, int *nbIut)
{
    int indice;

    for (int i = 0; i < *nbIut; i++)
    {
        if(existe(tIut[i]->nom, tIut, *nbIut, i, &indice))
        {
            fusion(tIut, *nbIut, i, indice);
            (*nbIut)--;
            i--;
        }
    }
}

/**
 * @brief Verifie l'existance d'une VilleIut dans le tableau de pointeur de VilleIut
 * 
 * @param nom [CHAINE DE CARACTERES]
 * @param tIut Tableau de pointeur de VilleIut
 * @param nbIut [Taille Logique]
 * @param iDepart Indice à partir du quel rechercher
 * @param indice Indice de la valeur si trouvée
 * @return int 1 -> Trouvé | 0 -> Inexistante
 */
int existe(char * nom, VilleIut ** tIut, int nbIut, int iDepart, int * indice)
{
    for (int i = iDepart+1; i < nbIut; i++)
    {
        if (strcmp(nom, tIut[i]->nom) == 0)
        {
            *indice = i;
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Fusionne la liste de département de deux VilleIut du même nom
 * 
 * @param tIut Tableau de pointeur de VilleIut
 * @param nbIut [Taille Logique]
 * @param i Indice liste d'accueil
 * @param j Indice ville à supprimer
 */
void fusion(VilleIut ** tIut, int nbIut, int i, int j)
{
    ListeDept aux;
    aux = tIut[i]->lDept;
    tIut[i]->lDept = tIut[j]->lDept;
    tIut[i]->lDept->suiv = aux;

    supprimerIut(tIut, nbIut, j);
}

/**
 * @brief Supprime une ville du tableau de pointeur de VilleIut
 * 
 * @param tIut Tableau de pointeur de VilleIut
 * @param nbIut [Taille Logique]
 * @param j Indice ville à supprimer
 */
void supprimerIut(VilleIut ** tIut, int nbIut, int j)
{
    for (int i = j ; i < nbIut-1 ; i++)
    {
        tIut[i] = tIut[i+1];
    }
}

/*
==============================================
                Partie Candidat
==============================================
*/

ListeCandidats chargeCandidat(int * nbCandidat)
{
    MaillonCandidat * m;

    FILE * flot = fopen("../donnees/candidats.don", "r");
    if (flot == NULL)
    {
        printf("Error : Fichier non ouvert\n");
        exit(1);
    }

    if (!feof(flot))
    {

        fscanf(flot, "%d%*c", nbCandidat);

        m = NULL;
        
        for (int i = 0 ; i < *nbCandidat ; i++)
        {
            m = ajouteCandidat(m, lireCandidat(flot));
        }
    }

    MaillonCandidat * aux;
    aux = m;
    lChoix auxLis;

    printf("%d\n", *nbCandidat);
    for (int i = 0 ; i < *nbCandidat ; i++)
    {
        printf("%d\n", aux->candidat.numero);
        printf("%s\n", aux->candidat.nom);
        printf("%s\n", aux->candidat.prenom);

        for (int j = 0 ; j < 4 ; j++)
        {
            printf("%f\n", aux->candidat.notes[j]);
        }

        printf("%d\n", aux->candidat.nbChoix);



        for (int k  = 0 ; k < aux->candidat.nbChoix; k++)
        {
            auxLis = aux->candidat.lchoix;  
            printf("%s\n", auxLis->ville);
            printf("%s\n", auxLis->departement);
            printf("%d\n", auxLis->decisionDepartement);
            printf("%d\n", auxLis->validationCandidat);

            auxLis = auxLis->suiv;
        }

        aux = aux->suiv;

    }

    fclose(flot);

    return m;
}

ListeCandidats ajouteCandidat (ListeCandidats l, MaillonCandidat * nouv)
{
    ListeCandidats aux;

    if(l == NULL)
        l = nouv;
    else
    {
        aux = l;
        l = nouv;
        l->suiv = aux;
    }

    return l;
}

MaillonCandidat * lireCandidat(FILE * flot)
{
    MaillonCandidat * m;

    if (feof(flot)) 
    {
        printf("Error : fin de fichier\n");
        exit(1);
    }

    m = (MaillonCandidat *) malloc(sizeof(MaillonCandidat));
    if (m == NULL)
    {
        printf("Error : malloc candidat\n");
        exit(1);
    }

    // Lecture
    fscanf(flot, "%d%*c", &m->candidat.numero);
    
    fgets(m->candidat.nom, 50, flot);
    m->candidat.nom[strlen(m->candidat.nom)-1] = '\0';
    fgets(m->candidat.prenom, 50, flot);
    m->candidat.prenom[strlen(m->candidat.prenom)-1] = '\0';

    for (int i = 0; i < 4 ; i++)
        fscanf(flot, "%f", &m->candidat.notes[i]);

    fscanf(flot, "%d%*c", &m->candidat.nbChoix);

    m->candidat.lchoix = recupChoix(flot, m->candidat.nbChoix);

    return m;
}

lChoix recupChoix(FILE *flot, int nbChoix)
{

    lChoix l;

    if (feof(flot))
    {
        printf("Error : Fin de fichier\n");
        exit(1);
    }

    if (flot == NULL)
    {
        printf("Error : Erreur de fichier\n");
        exit(1);
    }

    l = NULL;

    // Récupération des choix
    for (int i = 0; i < nbChoix; i++)
    {
        l = ajouteChoix(l, lireChoix(flot));
    }

    return l;
}

lChoix ajouteChoix(lChoix l, lChoix nouv)
{
    lChoix aux;

    if (l == NULL)
        l = nouv;
    else
    {
        aux = l;
        l = nouv;
        l->suiv = aux;
    }

    return l;
}

lChoix lireChoix (FILE *flot)
{
    lChoix l;
    
    if ((flot == NULL) || (feof(flot)))
    {
        printf("Erreur de fichier\n");
        exit(1);
    }

    l = (lChoix) malloc(sizeof(Choix));
    if (l == NULL)
    {
        printf("Erreur de malloc\n");
        exit(1);
    }   

    fgets(l->ville, 50, flot);
    l->ville[strlen(l->ville)-1] = '\0';

    fgets(l->departement, 50, flot);
    l->departement[strlen(l->departement)-1] = '\0';

    fscanf(flot, "%d", &l->decisionDepartement);
    fscanf(flot, "%d%*c", &l->validationCandidat);

    return l;
}


/*
void testCandidat(void)
{
    return;
}

ListeCandidats chargeCandidat(void)
{
    FILE *flot;
    ListeCandidats lCand;
    int nbCandidat;

    flot = fopen("../donnees/candidats.don", "r");

    if (flot == NULL)
    {
        printf("Probleme d'ouverture de fichier\n");
        exit(1);
    }

    lCand = NULL;
    fscanf(flot, "%d", &nbCandidat);

    int i = 0;
    while (!feof(flot) && i < nbCandidat)
    {
        ajouteCandidat(lCand, flot);
        i++;
    }


    fclose(flot);
}

void ajouteCandidat(ListeCandidats lCand, FILE * flot)
{
    if (lCand == NULL)
        lCand = lireCandidat(flot);
    else
        ajouteCandidat(lCand->suiv, flot);
}

MaillonCandidat * lireCandidat(FILE *flot)
{
    MaillonCandidat * m;
    m = initialiseCandidat();

    fscanf(flot, "%d", &m->candidat.numero);
    fgets(m->candidat.nom, 50, flot);
    fgets(m->candidat.prenom, 50, flot);
    m->candidat.nom[strlen(m->candidat.nom)-1] = '\0';
    m->candidat.prenom[strlen(m->candidat.prenom)-1] = '\0';
    
    for (int i = 0; i < 4; i++) {
        fscanf(flot, "%f", &m->candidat.notes[i]);
    }

    fscanf(flot, "%d", &m->candidat.nbChoix);

    for (int i = 0; i < m->candidat.nbChoix-1; i++)
    {
        ajouteChoix(m->candidat.lchoix, lireChoix(flot));
    }

    return m;

}

void ajouteChoix(lChoix lchoix, Choix * choix)
{
    lChoix aux;

    if (lchoix == NULL)
        lchoix = choix;
    else 
    {
        aux = lchoix;
        lchoix = choix;
        choix->suiv = aux;
    }
}

lChoix lireChoix(FILE *flot)
{
    lChoix choix;
    choix = initialiseChoix();

    fscanf(flot, "%s %s %d %d", choix->ville, choix->departement, &choix->decisionDepartement, &choix->validationCandidat);

    return choix;
}

lChoix initialiseChoix(void)
{
    lChoix choix;

    choix = (lChoix) malloc(sizeof(Choix));
    if (choix == NULL)
    {
        printf("Probleme de malloc\n");
        exit(1);
    }

    return choix;

}


ListeCandidats initialiseCandidat(void)
{
    ListeCandidats candidat;

    candidat = (ListeCandidats) malloc(sizeof(MaillonCandidat));
    if (candidat == NULL)
    {
        printf("Probleme de malloc\n");
        exit(1);
    }

    return candidat;

}*/