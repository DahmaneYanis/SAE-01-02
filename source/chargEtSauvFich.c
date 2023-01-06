#include "../header/sae.h"

int chargIutDon(VilleIut *tVilleIut[], int nbMax, char nomFich[])
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
            ajouterDept(tVilleIut[indice]->lDept, nomDept, resp, nbP);
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

