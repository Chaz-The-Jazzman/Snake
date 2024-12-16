#include <stdio.h>
#include "myLib.h"
#include "SP_GESTION_JEU.h"
#include "mesTypes.h"

int main()
{
    setColor(RED) ;
    printf("Bienvenue dans le SNAKE!!!\n");

    setColor (GREEN) ;
    printf(" A vous de jouer !!!\n");
}

void Game_Loop(TYPE_PARAM_JEU param_Jeu)
{
    //Initialisation des flags de sortie
    boolean quit_flag = FALSE;
    boolean fin_jeu = FALSE;

    int direction = -1;

    //initialisation du jeu
    TYPE_SNAKE snek;
    TYPE_POMME pom;
    TYPE_JOUEUR player;

    placer_pomme(&pom, param_Jeu.H_stade, param_Jeu.L_stade);


    while (!quit_flag || !fin_jeu )
    {
        //afficher_Jeu(snek, pom);
        switch (param_Jeu.difficulte) 
        {
            case 1:
                direction = SP_Gestion_Clavier(1000);
                break;
            case 2:
                direction = SP_Gestion_Clavier(750);
                break;
            case 3:
                direction = SP_Gestion_Clavier(500);
                break;
            default:
                direction = SP_Gestion_Clavier(1000);
                break;
        }
        if (direction != -1)
        {
            snek.direction = direction;
        }        
        //Lecture
        snek.direction = SP_Gestion_Clavier(100);

        calc_NextSnekPos(&snek);

        test_pomme(&snek, &pom);
        fin_jeu = test_fin_jeu(snek, param_Jeu);
        //Gestion Jeu

    }

    if (quit_flag)
    {
        //jeu abandonné
    }
    else
    {
        //enregistrer score
    }

    
    
}