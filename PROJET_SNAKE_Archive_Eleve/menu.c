#include <stdio.h>
#include <time.h>
#include "myLib.h"
#include "mesTypes.h"
#include "SP_Gestion_parametres.h"
#include "SP_GESTION_JEU.h"

void menu_parametres(TYPE_PARAM_JEU* param_jeu)
{
    TYPE_PARAM_JEU* param = param_jeu;
    int choix = 0;
    int choix2 = 0;
    int i = 0;
    system("cls");
    printf("Vous pouvez modifier les valeurs de parametres suivantes : \n\r");
    printf("1_Couleur stade : ");
    colorparam(param_jeu->couleur_stade, 1);
    printf("2_Couleur snake : ", param_jeu->couleur_snake);
    colorparam(param_jeu->couleur_snake, 1);
    printf("3_Difficulte : %d\n\r", param_jeu->difficulte);
    printf("4_Hauteur stade : %d\n\r", param_jeu->H_stade);
    printf("5_Largeur stade : %d\n\r", param_jeu->L_stade);
    printf("6_RETOUR \n\r");
    printf("Entrez votre choix de modification : \n\r");

    if (scanf("%d", &choix) != 1) {
            printf("Entrée invalide. Veuillez réessayer.\n\n");
            while (getchar() != '\n');
            system("cls");
        }
    system("cls");
    switch (choix) {
                case 1:
                    printf("Vous modifiez la variable 'Couleur stade' \n\r");
                    printf("Valeur actuelle : ");
                    colorparam(param_jeu->couleur_stade, 1);
                    printf("Valeur possible : ");
                    colorall();
                    printf("Entrez votre choix de modification : \n\r");
                    if (scanf("%d", &choix2) != 1) {
                        printf("Entrée invalide. Veuillez réessayer.\n\n");
                        while (getchar() != '\n');
                        system("cls");
                    }
                    param_jeu->couleur_stade = choix2;
                    menu_parametres(param_jeu);
                    break;
                case 2:
                    printf("Vous modifiez la variable 'Couleur snake' \n\r");
                    printf("Valeur actuelle : ");
                    colorparam(param_jeu->couleur_snake, 1);
                    printf("Valeur possible : ");
                    colorall();
                    printf("Entrez votre choix de modification : \n\r");
                    if (scanf("%d", &choix2) != 1) {
                        printf("Entrée invalide. Veuillez réessayer.\n\n");
                        while (getchar() != '\n');
                        system("cls");
                    }
                    param_jeu->couleur_snake = choix2;
                    menu_parametres(param_jeu);
                    break;
                case 3:
                    printf("Vous modifiez la variable 'Difficulte' \n\r");
                    printf("Valeur actuelle : %d\n\r", param_jeu->difficulte);
                    printf("Valeur possible : 1_EASY, 2_MEDIUM, 3_HARD");
                    printf("Entrez votre choix de modification : \n\r");
                    if (scanf("%d", &choix2) != 1) {
                        printf("Entrée invalide. Veuillez réessayer.\n\n");
                        while (getchar() != '\n');
                        system("cls");
                    }
                    param_jeu->difficulte = choix2;
                    menu_parametres(param_jeu);
                    break;
                case 4:
                    printf("Vous modifiez la variable 'Hauteur stade' \n\r");
                    printf("Valeur actuelle : %d\n\r", param_jeu->H_stade);
                    printf("Entrez votre choix de modification : \n\r");
                    if (scanf("%d", &choix2) != 1) {
                        printf("Entrée invalide. Veuillez réessayer.\n\n");
                        while (getchar() != '\n');
                        system("cls");
                    }
                    param_jeu->H_stade = choix2;
                    menu_parametres(param_jeu);
                    break;
                case 5:
                    printf("Vous modifiez la variable 'Largeur stade' \n\r");
                    printf("Valeur actuelle : %d\n\r",param_jeu->L_stade);
                    printf("Entrez votre choix de modification : \n\r");
                    if (scanf("%d", &choix2) != 1) {
                        printf("Entrée invalide. Veuillez réessayer.\n\n");
                        while (getchar() != '\n');
                        system("cls");
                    }
                    param_jeu->L_stade = choix2;
                    menu_parametres(param_jeu);
                    break;
                case 6:
                    system("cls");
                    menu_principale();
                    break;
                default:
                    printf("Choix non valide. Veuillez réessayer.\n");
                    system("cls");
                    menu_parametres(param);
                    break;
            }
            param = param_jeu;
            system("cls");

}

void menu_principale()
{
    setColor(15);
    TYPE_PARAM_JEU param_jeu;
    TYPE_POMME pomme;
    TYPE_SNAKE snake;
    int choix = 0;

    init_param(&param_jeu,&pomme, &snake);

    printf("1_JOUER\n\r");
    printf("2_SCORE\n\r");
    printf("3_PARAMETRES\n\r");
    printf("4_QUITTER\n\r");
    printf("Entrez votre choix : \n\r");

    if (scanf("%d", &choix) != 1) {
            printf("Entree invalide. Veuillez reessayer.\n\n");
            while (getchar() != '\n');
            system("cls");
        }

    switch (choix) {
                case 1:
                    printf("jeu\n\r");
                    Game_Loop(param_jeu);
                    //affichage_Jeu(pomme, snake, param_jeu);
                    break;
                case 2:
                    printf("Affichage des scores.\n");
                    break;
                case 3:
                    printf("parametres\n\r");
                    menu_parametres(&param_jeu);
                    break;
                case 4:
                    printf("Au revoir !\n");
                    exit(0);
                    break;
                default:
                    printf("Choix non valide. Veuillez réessayer.\n");
                    system("cls");
                    menu_principale();
                    break;
            }

            system("cls");
}


