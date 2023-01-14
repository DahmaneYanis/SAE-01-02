int menuAdmin(int phase)
{
    int choix;
    if (phase < 3)
    {
        afficherMenuAdmin();
        scanf("%d", &choix);
    }
    switch (choix)
    {
    case : 1
        return choix + 1;
        break;
    case : 2
        return choix;
        break;
    }
}

void afficherMenuAdmin(void)
{
    printf("1.Passer a la phase suivante (Attention, irréversible)\n");
    printf("2.Quitter")
}