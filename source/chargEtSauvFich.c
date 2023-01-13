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
}

/**
 * @brief Fonction de test de chargement
 */
void testCharge(void)
{
    int nbIut, nbMax;
    VilleIut ** tIut = chargeIutDon("../donnees/iut.don", &nbIut, &nbMax);

    for (int i = 0; i < nbIut; i++)
    {
        printf("[ %s | %s | %d | %s ]\n", tIut[i]->nom, tIut[i]->lDept->nomDept, tIut[i]->lDept->nbP, tIut[i]->lDept->resp);
    }
}



/*int chargIutDon(VilleIut *tVilleIut[], int nbMax, char nomFich[])
{
    FILE *flot;
    int i=0, nbP, trouve, indice;
    char nom[30], nomDept[30], resp[30];

    flot = fopen(nomFich, "r");
    if(flot==NULL)
    {
        printf("Probleme d'ouverture du fichier\n");
        exit(1);
    }
    fscanf(flot, "%s", nom);
    lireDep(flot, nomDept, &nbP, resp);
    while(!feof(flot))
    {
        if(i==nbMax)
        {
            printf("Tableau plein\n");
            return -1;
        }
        indice = appartientIut(tVilleIut, i, nom, &trouve);
        if(trouve==0)
        {
            tVilleIut[i] = (VilleIut*)malloc(sizeof(VilleIut));
            if(tVilleIut[i]==NULL)
            {
                printf("Probleme malloc\n");
                fclose(flot);
                exit(1);
            }
            strcpy(tVilleIut[i]->nom, nom);
            tVilleIut[i]->lDept = listenouv();
            ajouterDept(tVilleIut[i]->lDept, nomDept, resp, nbP);
            i = i + 1;
        }
        if(trouve==1)
            tVilleIut[indice]->lDept = ajouterDept(tVilleIut[indice]->lDept, nomDept, resp, nbP);
        fscanf(flot, "%s", nom);
        lireDep(flot, nomDept, &nbP, resp);
    }
    return i;
}

void lireDep(FILE *flot, char nomDept[], int *nbP, char resp[])
{
    fscanf(flot,"%s%d\t", nomDept, nbP);
    fgets(resp, 30, flot);
    
    #ifdef _WIN32
    resp[strlen(resp) - 1] = '\0';
    #endif

    #ifdef __linux__
    resp[strlen(resp) - 2] = '\0';
    #endif
}

int appartientIut(VilleIut *tVilleIut[], int nb, char nom[], int *trouve)
{
    int i = 0;

    while(i < nb)
    {
        if(strcmp(tVilleIut[i]->nom, nom) == 0)
        {
            *trouve = 1;
            return i;
        }
        i = i + 1;
    }
    *trouve = 0;
    return i;
}

void sauvegarderFichierIutDon(VilleIut *tVilleIut[], int nbVille, char nomFich[])
{
    FILE *flot;
    int i=0;

    flot = fopen(nomFich, "w");
    if(flot==NULL)
    {
        printf("Probleme lors de l'ouverture du fichier\n");
        exit(1);
    }
    while(i<nbVille)
    {
        printf("%d\n", i);
        while(tVilleIut[i]->lDept != NULL)
        {    
            printf("%s %s %d %s", tVilleIut[i]->nom, tVilleIut[i]->lDept->nomDept, tVilleIut[i]->lDept->nbP, tVilleIut[i]->lDept->resp);
            fprintf(flot, "%s %s %d %s", tVilleIut[i]->nom, tVilleIut[i]->lDept->nomDept, tVilleIut[i]->lDept->nbP, tVilleIut[i]->lDept->resp);
            tVilleIut[i]->lDept = tVilleIut[i]->lDept->suiv;
        }
        i = i + 1;
    }
    fclose(flot);
}

*/

/*

*/