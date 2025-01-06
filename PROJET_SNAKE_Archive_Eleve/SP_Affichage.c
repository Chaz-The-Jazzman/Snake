#include <stdio.h>
#include "mesTypes.h"
#include "myLib.h"

void affichage(TYPE_PARAM_JEU param, TYPE_SNAKE snake, TYPE_POMME pomme, TYPE_SPEED_APPLE speed_apple)
{
    affichage_Jeu(snake, param);
    affichage_pomme(pomme, param);
    affichage_speed_apple(speed_apple, param);
}

void affichage_stade(TYPE_PARAM_JEU param)
{
    int x=1;
    int y=1;

    for(y=1;y<param.H_stade;y++)
    {

        for(x=1;x<param.L_stade;x++)
        {
            if(x==1 || x ==param.L_stade-1 || y == 1 || y == param.H_stade-1)
            {
                setColor(1);
                printStadeElement();
            }

            else
            {
               setBackgroundColor(param.couleur_stade);
               printf(" ");
            }

        }
        printf("\n\r");
    }
    setBackgroundColor(BLACK);

}
void affichage_Jeu(TYPE_SNAKE snake, TYPE_PARAM_JEU param)
{
    int i = 1;
    setBackgroundColor(param.couleur_stade);

    setColor(param.couleur_snake);

    for (i=0;i<snake.taille;i++)
    {
        gotoxy(snake.pos[i].x, snake.pos[i].y);
        printSnakeBody();
    }


    gotoxy(snake.tete.x ,  snake.tete.y);
    printSnakeHead();

    gotoxy(snake.old_tail.x, snake.old_tail.y);
    printf(" ");
}

void affichage_pomme(TYPE_POMME pomme,TYPE_PARAM_JEU param)
{
    setBackgroundColor(param.couleur_stade);
    gotoxy(pomme.pos.x, pomme.pos.y);
    printPomme();
    setBackgroundColor(BLACK);
}

void affichage_speed_apple(TYPE_SPEED_APPLE speed_apple, TYPE_PARAM_JEU param)
{
    if(speed_apple.is_active)
    {
    setBackgroundColor(param.couleur_stade);
    gotoxy(speed_apple.pos.x, speed_apple.pos.y);
    setBackgroundColor(YELLOW);
    setColor(BLACK);
    printf("%c",157);
    setBackgroundColor(BLACK);
    }
}

void Affichage_init_score(TYPE_PARAM_JEU param)
{

   gotoxy(param.L_stade + 10,param.H_stade /2);
   printf("\t**********************\r");
   gotoxy(param.L_stade + 10,param.H_stade /2 +1);
   printf("\t\t   0 \t\n\r");
   gotoxy(param.L_stade + 10,param.H_stade /2 +2);
   printf("\t**********************\r");
}

void Affichage_score(TYPE_PARAM_JEU param, int longueur_snake, int *score)
{
    gotoxy(param.L_stade + 26,param.H_stade /2 +1);
    if(longueur_snake > 2)
    {
        *score = *score+1*30;
    }
    printf(" %d ",*score);
}
