#include <stdio.h>
#include <time.h>
#include "myLib.h"
#include "mesTypes.h"
#include "SP_Gestion_parametres.h"
#include "SP_GESTION_JEU.h"
#include "mini_jeux.h"
void menu_principale(TYPE_PARAM_JEU param_jeu);
void menu_parametres(TYPE_PARAM_JEU* param_jeu);

void menu_parametres(TYPE_PARAM_JEU* param_jeu)
{
    TYPE_PARAM_JEU* param = param_jeu;
    int choix = 0;
    int choix2 = 0;
    system("cls");
    choix = select_param(*param_jeu,5,1);
    system("cls");
    switch (choix) {
                case 0:
                    do
                    {
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
                    }
                    while(choix2 <0 || choix2 >16 );
                    param_jeu->couleur_stade = choix2;
                    menu_parametres(param_jeu);
                    break;
                case 1:
                    do
                    {
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
                    }
                    while(choix2 <0 || choix2 >16 );
                    param_jeu->couleur_snake = choix2;
                    menu_parametres(param_jeu);
                    break;
                case 2:

                    choix2 = select_param(*param_jeu, 3, 2);
                    param_jeu->difficulte = choix2+1;
                    menu_parametres(param_jeu);
                    break;
                case 3:
                    choix2 = select_param(*param_jeu, 3, 3);

                    if(choix2 == 0)
                    {
                        param_jeu->H_stade = 25;
                        param_jeu->L_stade = 40;
                    }
                    else if(choix2 == 1)
                    {
                        param_jeu->H_stade = 30;
                        param_jeu->L_stade = 60;
                    }
                    else
                    {
                        param_jeu->H_stade = 30;
                        param_jeu->L_stade = 80;
                    }
                    menu_parametres(param_jeu);
                    break;
                case 4:
                    system("cls");
                    menu_principale(*param_jeu);
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

void afficher_menu_parametres(int pos, TYPE_PARAM_JEU param_jeu)
{
    printf("Vous pouvez modifier les valeurs de parametres suivantes : \n\r");
    printf("%s 1_Couleur stade : ", (pos==0)? "->":" ");
    colorparam(param_jeu.couleur_stade, 1);
    printf("%s 2_Couleur snake : ", (pos==1)? "->":" ");
    colorparam(param_jeu.couleur_snake, 1);
    printf("%s 3_Difficulte : %d\n\r",(pos==2)? "->":" ", param_jeu.difficulte);
    printf("%s 4_Hauteur stade : %dx%d\n\r",(pos==3)? "->":" ", param_jeu.L_stade,param_jeu.H_stade);
    printf("%s 5_RETOUR \n\r", (pos==4)? "->":" ");
}
void afficher_menu_principale(int pos)
{
    printf("%s 1_JOUER\n\r", (pos==0)? "->":" ");
    printf("%s 2_SCORE\n\r", (pos==1)? "->":" ");
    printf("%s 3_PARAMETRES\n\r", (pos==2)? "->":" ");
    printf("%s 4_QUITTER\n\r", (pos==3)? "->":" ");
}

void afficher_menu_jouer(int pos, TYPE_PARAM_JEU param_jeu) {

    system("cls");
    printf("=== MENU JOUER ===\n\n");
    printf("%s 1_Mode 1 Joueur\n", (pos == 0) ? "->" : " ");
    printf("%s 2_Mode 2 Joueurs\n", (pos == 1) ? "->" : " ");
    printf("%s 3_Mode mario_kart\n", (pos == 2) ? "->" : " ");
    printf("%s Retour\n", (pos == 3) ? "->" : " ");

}

void afficher_menu_pomme(int pos, TYPE_PARAM_JEU param_jeu) {

    system("cls");
    printf("=== MENU POMME ===\n\n");
    printf("%s Pomme vitesse\n", (pos == 0) ? "->" : "  ");
    printf("%s Pomme téleportation\n", (pos == 1) ? "->" : "  ");
    printf("%s Pomme explosive\n", (pos == 2) ? "->" : "  ");
    printf("%s Pomme invisibilite\n", (pos == 3) ? "->" : "  ");
    printf("%s Retour\n", (pos == 4) ? "->" : "  ");

}


void menu_principale(TYPE_PARAM_JEU param_jeu)
{
    setColor(15);
    int choix = 0;
    int choix2 = 0;
    choix = select_param(param_jeu,4,0);

    switch (choix) {
                case 0:
                    printf("jeu\n\r");
                    choix2 = select_param(param_jeu,4,4);
                        switch (choix2) {
                            case 0: // Mode 1 Joueur
                                printf("Mode 1 Joueur sélectionné.\n");
                                system("cls");
                                Game_Loop(param_jeu);
                                break;
                            case 1: // Mode 2 Joueurs
                                printf("Mode 2 Joueurs sélectionné.\n");
                                system("cls");
                                Game_Loop_2j(param_jeu); // Implémentez cette fonction pour gérer le mode 2 joueurs
                                break;
                            case 2:
                                system("cls");
                                Circuit circuit;
                                charger_circuit(&circuit, "mario.txt");
                                Game_Loop_MarioKart(&circuit);
                                break;
                            case 3: // Retour
                                system("cls");
                                menu_principale(param_jeu);
                                break;
                            default:
                                printf("Erreur inattendue dans le menu.\n");
                                exit(1);
                        }
                    setBackgroundColor(16);
                    system("cls");
                    menu_principale(param_jeu);
                    break;
                case 1:
                    printf("Affichage des scores.\n");
                    printplayerscores();
                    menu_principale(param_jeu);
                    break;
                case 2:
                    printf("parametres\n\r");
                    menu_parametres(&param_jeu);
                    break;
                case 3:
                    printf("Au revoir !\n");
                    exit(0);
                    break;
                default:
                    printf("Choix non valide. Veuillez réessayer.\n");
                    system("cls");
                    menu_principale(param_jeu);
                    break;
            }

            system("cls");
}


