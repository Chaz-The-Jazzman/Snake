#include <stdio.h>
#include "mesTypes.h"
#include "myLib.h"

void affichage_stade(TYPE_PARAM_JEU param)
{
    int x=1;
    int y=1;
    setColor(param.couleur_stade);

    for(y=1;y<param.H_stade;y++)
    {

        for(x=1;x<param.L_stade;x++)
        {
            if(x==1 || x ==param.L_stade-1 || y == 1 || y == param.H_stade-1)
            {
                printStadeElement();
            }

            else
            {
               printf(" ");
            }

        }
        printf("\n\r");
    }

}
void affichage_Jeu(TYPE_SNAKE snake, TYPE_PARAM_JEU param)
{
    int i = 1;
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

void affichage_pomme(TYPE_POMME pomme)
{
    gotoxy(pomme.pos.x, pomme.pos.y);
    printPomme();
}

void Affichage_init_score()
{
    printf("**********************\n\r");
    printf("\t 0 \t\n\r");
    printf("**********************\n\r");
}

void Affichage_score(int longueur_snake, int *score)
{
    gotoxy(12,2);
    if(longueur_snake > 2)
    {
        *score = (*score+1)*30;
    }
    printf("\t %d \t\n\r",*score);
}
