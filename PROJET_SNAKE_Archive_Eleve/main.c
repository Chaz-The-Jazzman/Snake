#include <stdio.h>
#include "myLib.h"
#include "SP_GESTION_JEU.h"

int main()
{
    setColor(RED) ;
    printf("Bienvenue dans le SNAKE!!!\n");

    setColor (GREEN) ;
    printf(" A vous de jouer !!!\n");

    Game_Loop();

    return 0;
}

void Game_Loop(void)
{
    //Initialisation des falgs de sortie
    boolean quit_flag = FALSE;
    boolean fin_jeu = FALSE;
    while (!quit_flag || !fin_jeu )
    {
        /* code */
    }
    if (quit_flag)
    {
        /* code */
    }
    else
    
    
    
}