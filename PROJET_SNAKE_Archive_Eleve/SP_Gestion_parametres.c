#include <stdio.h>
#include "mesTypes.h"
#include "myLib.h"
void init_global(TYPE_PARAM_JEU *param_jeu)
{
     param_jeu->couleur_stade = 10;
     param_jeu->couleur_snake = 5;
     param_jeu->difficulte = 1;
     param_jeu->H_stade = 30;
     param_jeu->L_stade = 80;
}

void init_jeu(TYPE_POMME* pomme, TYPE_SNAKE* snake)
{
     pomme->pos.x = 12;
     pomme->pos.y = 12;
     snake->direction = DROITE;
     snake->taille = 2;
     snake->oldtaille = 2;
     snake->pos[0].x = 9;
     snake->pos[0].y = 10;
     snake->pos[1].x = 8;
     snake->pos[1].y = 10;
     snake->tete.x = 10;
     snake->tete.y = 10;
}
void largeur_stade(int pos)
{

    printf("Options possibles : \n");
    printf("%c 40x25 \n", (pos==1)? '->':' ');
    printf("%c 60x30 \n", (pos==2)? '->':' ');
    printf("%c 80x30 \n", (pos==2)? '->':' ');

   /* gotoxy(0, 6-pos);
    setBackgroundColor(WHITE);*/


}

int select_param()
{
    int curs = 0;
    int touche;
    do
    {
        largeur_stade(curs);
        touche = _getch();
        if (touche==0xE0) // fleche : le code fleche renvoie 2 caracteres.
        {
            touche = _getch();
            if (touche==0x50 && curs==0)  // fleche bas
                curs = 1;
            if (touche==0x48 && curs==1)  // fleche haut
                curs = 0;
        }
    } while (touche!=0x0D);  // enter
    return curs;
}
int select_param_ud(int pos)
{
    int c = getkey();
    if(c == KEY_UP)
    {
        return pos+1;
    }
    else if (c == KEY_DOWN)
    {
        return pos-1;
    }
    else if (c == KEY_ENTER)
    {
        return 9;
    }
}
int select_param_lr(int pos)
{
    int c = getkey();
    if (c == KEY_LEFT)
    {
        return pos+1;
    }
    else if (c == KEY_RIGHT)
    {
        return pos-1;
    }
    else if (c == KEY_ENTER)
    {
        return 9;
    }
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
