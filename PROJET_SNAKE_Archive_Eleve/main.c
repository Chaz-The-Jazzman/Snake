#include <stdio.h>
#include <stdlib.h>
#include "myLib.h"
#include "SP_GESTION_JEU.h"
#include "menu.h"

int main()
{
FILE *f;
char ligne[256];
int i,j;

    f = fopen("Menu_ART.txt", "r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }
    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        printf("%s", ligne);
    }

    system("pause");
    fclose(f);

    system("cls");
    menu_principale();

    return 0;
}

