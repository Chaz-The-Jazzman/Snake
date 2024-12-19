#include <stdio.h>
#include "mesTypes.h"
#include "myLib.h"
void init_global(TYPE_PARAM_JEU *param_jeu)
{
     param_jeu->couleur_stade = 10;
     param_jeu->couleur_snake = 5;
     param_jeu->difficulte = 1;
     param_jeu->H_stade = 25;
     param_jeu->L_stade = 40;
}

void init_jeu(TYPE_POMME* pomme, TYPE_SNAKE* snake)
{
     pomme->pos.x = 12;
     pomme->pos.y = 12;
     snake->direction = DROITE;
     snake->taille = 2;
     snake->pos[0].x = 9;
     snake->pos[0].y = 10;
     snake->pos[1].x = 8;
     snake->pos[1].y = 10;
     snake->tete.x = 10;
     snake->tete.y = 10;
}

void colorparam(int color, int ligne)
{
    if(color>=0 && color<16)
    {
        setColor(color);
        printf("%c  ", 254);
        if(ligne == 1)
        {
            printf("\n\r");
        }
        setColor(15);
    }
}

void colorall()
{
    int i;
    for(i=0;i<16;i++)
    {
        setBackgroundColor(i);
        printf(" %d ",i);
    }
    printf("\n\r");
    setBackgroundColor(0);
}
