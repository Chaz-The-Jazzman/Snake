#include <stdio.h>
#include <time.h>
#include "myLib.h"
#include "mesTypes.h"
#include "SP_Gestion_parametres.h"
#include "SP_GESTION_JEU.h"

// Function to display and modify game parameters
void menu_parametres(TYPE_PARAM_JEU* param_jeu) {
    int choix = 0;
    int choix2 = 0;

    while (1) {
        system("cls");
        printf("Vous pouvez modifier les valeurs de parametres suivantes : \n");
        printf("1_Couleur stade : ");
        colorparam(param_jeu->couleur_stade, 1);
        printf("2_Couleur snake : ");
        colorparam(param_jeu->couleur_snake, 1);
        printf("3_Difficulte : %d\n", param_jeu->difficulte);
        printf("4_Hauteur stade : %d\n", param_jeu->H_stade);
        printf("5_Largeur stade : %d\n", param_jeu->L_stade);
        printf("6_RETOUR \n");
        printf("Entrez votre choix de modification : \n");

        if (scanf("%d", &choix) != 1) {
            printf("Entrée invalide. Veuillez réessayer.\n\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

        system("cls");
        switch (choix) {
            case 1:
                printf("Vous modifiez la variable 'Couleur stade' \n");
                printf("Valeur actuelle : ");
                colorparam(param_jeu->couleur_stade, 1);
                printf("Valeur possible : ");
                colorall();
                printf("Entrez votre choix de modification : \n");
                if (scanf("%d", &choix2) != 1) {
                    printf("Entrée invalide. Veuillez réessayer.\n\n");
                    while (getchar() != '\n'); // Clear the input buffer
                    continue;
                }
                param_jeu->couleur_stade = choix2;
                break;
            case 2:
                printf("Vous modifiez la variable 'Couleur snake' \n");
                printf("Valeur actuelle : ");
                colorparam(param_jeu->couleur_snake, 1);
                printf("Valeur possible : ");
                colorall();
                printf("Entrez votre choix de modification : \n");
                if (scanf("%d", &choix2) != 1) {
                    printf("Entrée invalide. Veuillez réessayer.\n\n");
                    while (getchar() != '\n'); // Clear the input buffer
                    continue;
                }
                param_jeu->couleur_snake = choix2;
                break;
            case 3:
                printf("Vous modifiez la variable 'Difficulte' \n");
                printf("Valeur actuelle : %d\n", param_jeu->difficulte);
                printf("Valeur possible : 1_EASY, 2_MEDIUM, 3_HARD\n");
                printf("Entrez votre choix de modification : \n");
                if (scanf("%d", &choix2) != 1) {
                    printf("Entrée invalide. Veuillez réessayer.\n\n");
                    while (getchar() != '\n'); // Clear the input buffer
                    continue;
                }
                param_jeu->difficulte = choix2;
                break;
            case 4:
                printf("Vous modifiez la variable 'Hauteur stade' \n");
                printf("Valeur actuelle : %d\n", param_jeu->H_stade);
                printf("Entrez votre choix de modification : \n");
                if (scanf("%d", &choix2) != 1) {
                    printf("Entrée invalide. Veuillez réessayer.\n\n");
                    while (getchar() != '\n'); // Clear the input buffer
                    continue;
                }
                param_jeu->H_stade = choix2;
                break;
            case 5:
                printf("Vous modifiez la variable 'Largeur stade' \n");
                printf("Valeur actuelle : %d\n", param_jeu->L_stade);
                printf("Entrez votre choix de modification : \n");
                if (scanf("%d", &choix2) != 1) {
                    printf("Entrée invalide. Veuillez réessayer.\n\n");
                    while (getchar() != '\n'); // Clear the input buffer
                    continue;
                }
                param_jeu->L_stade = choix2;
                break;
            case 6:
                system("cls");
                return; // Exit the parameter menu
            default:
                printf("Choix non valide. Veuillez réessayer.\n");
                break;
        }
    }
}

// Function to display the main menu
void menu_principale() {
    setColor(15);
    TYPE_PARAM_JEU param_jeu;
    TYPE_POMME pomme;
    TYPE_SNAKE snake;
    int choix = 0;

    init_param(&param_jeu, &pomme, &snake); // Initialize game parameters

    while (1) {
        printf("1_JOUER\n");
        printf("2_SCORE\n");
        printf("3_PARAMETRES\n");
        printf("4_QUITTER\n");
        printf("Entrez votre choix : \n");

        if (scanf("%d", &choix) != 1) {
            printf("Entrée invalide. Veuillez réessayer.\n\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

        switch (choix) {
            case 1:
                printf("jeu\n");
                Game_Loop(param_jeu); // Start the game loop
                break;
            case 2:
                printf("Affichage des scores.\n"); // Display scores
                break;
            case 3:
                printf("parametres\n");
                menu_parametres(&param_jeu); // Go to parameter menu
                break;
            case 4:
                printf("Au revoir !\n");
                exit(0); // Exit the program
            default:
                printf("Choix non valide. Veuillez réessayer.\n");
                break;
        }
    }
}
