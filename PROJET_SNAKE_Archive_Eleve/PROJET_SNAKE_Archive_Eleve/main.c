#include <stdio.h>
#include "myLib.h"
#include "SP_GESTION_JEU.h"

int main()
{
    int k;
    printf("Bienvenue dans le SNAKE!!!\n");

   //Test unitaire SP_GESTION_CLAVIER
    printf("Appuyez sur une direction... \n");
    while(1){
        k=SP_Gestion_Clavier();
        if (k!=-1){
            switch(k){
            case 3: printf("HAUT\n");
            break;
            case 2: printf("BAS\n");
            break;
            case 1: printf("GAUCHE\n");
            break;
            case 0: printf("DROITE\n");
            break;
            default: printf("Erreur\n");
            }
        }
    }

    return 0;
}
