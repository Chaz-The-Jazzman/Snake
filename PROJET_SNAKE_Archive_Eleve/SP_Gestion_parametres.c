#include <stdio.h>
#include "mesTypes.h"
#include "myLib.h"
void init_global(TYPE_PARAM_JEU *param_jeu)
{
     param_jeu->couleur_stade = 10;
     param_jeu->couleur_snake = 5;
     param_jeu->difficulte = 3;
     param_jeu->H_stade = 30;
     param_jeu->L_stade = 80;
}

void init_jeu(TYPE_POMME* pomme, TYPE_SNAKE* snake, TYPE_SPEED_APPLE* speed_apple, TYPE_INVISIBLE_APPLE* invisible_apple, TYPE_EXPLOSIVE_APPLE* explosive_apple,
              TYPE_TELEPORT_APPLE* teleport_apple)
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

     //init speed apple
     speed_apple->is_active = FALSE;
     invisible_apple->is_active = FALSE;
     teleport_apple->is_active = FALSE;
     explosive_apple->is_active = FALSE;
}

void init_mario_kart(TYPE_SNAKE *snake, MarioKartGame *game, Circuit *circuit) {
    // Initialiser le serpent
    snake->direction = DROITE;
    snake->taille = 3;
    snake->oldtaille = 3;

    snake->tete.x = 20;
    snake->tete.y = 20;

    for (int i = 0; i < snake->taille; i++) {
        snake->pos[i].x = snake->tete.x - i; // Corps aligné horizontalement
        snake->pos[i].y = snake->tete.y;
    }

    // Initialiser les paramètres du jeu
    game->snake = *snake;
    game->speed_multiplier = 300;
    game->finished = FALSE;
    game->game_over = FALSE;

    // Charger le circuit
    charger_circuit(circuit, "mario.txt");
}



void init_jeu_2j(TYPE_POMME* pomme, TYPE_SNAKE* snake1, TYPE_SNAKE* snake2) {
    // Initialize pomme
    pomme->pos.x = 12;
    pomme->pos.y = 12;

    // Initialize Snake 1
    snake1->direction = DROITE;
    snake1->taille = 2;
    snake1->oldtaille = 2;
    snake1->pos[0].x = 9;
    snake1->pos[0].y = 10;
    snake1->pos[1].x = 8;
    snake1->pos[1].y = 10;
    snake1->tete.x = 10;
    snake1->tete.y = 10;

    // Initialize Snake 2
    snake2->direction = GAUCHE;
    snake2->taille = 2;
    snake2->oldtaille = 2;
    snake2->pos[0].x = 70;
    snake2->pos[0].y = 20;
    snake2->pos[1].x = 71;
    snake2->pos[1].y = 20;
    snake2->tete.x = 69;
    snake2->tete.y = 20;
}

void largeur_stade(int pos, TYPE_PARAM_JEU param_jeu)
{
    printf("Vous modifiez la variable 'Hauteur stade' \n\r");
    printf("Valeur actuelle : %dx%d\n\r", param_jeu.L_stade, param_jeu.H_stade);
    printf("Entrez votre choix de modification : \n\r");
    printf("Options possibles : \n");
    printf("%s 40x25 \n", (pos==0)? "->":" ");
    printf("%s 60x30 \n", (pos==1)? "->":" ");
    printf("%s 80x30 \n", (pos==2)? "->":" ");

}

void difficulte(int pos, TYPE_PARAM_JEU param_jeu)
{
     printf("Vous modifiez la variable 'Difficulte' \n\r");
     printf("Valeur actuelle : %d\n\r", param_jeu.difficulte);
     printf("Valeur possible : \n");
     printf("%s 1_EASY\n",(pos==0)? "->":" ");
     printf("%s 2_MEDIUM\n",(pos==1)? "->":" ");
     printf("%s 3_HARD\n",(pos==2)? "->":" ");

}
int select_param(TYPE_PARAM_JEU param_jeu, int nb_param, int funct)
{
    int pos = 0;
    int touche;
    do
    {
        if(funct == 0)
        {
            afficher_menu_principale(pos);
        }
        else if(funct == 1)
        {
            afficher_menu_parametres(pos, param_jeu);
        }
        else if(funct == 2)
        {
            difficulte(pos, param_jeu);
        }
        else if(funct == 3)
        {
            largeur_stade(pos, param_jeu);
        }
        else if(funct == 4)
        {
            afficher_menu_jouer(pos, param_jeu);
        }

        touche = _getch();
        if (touche==0xE0) // fleche : le code fleche renvoie 2 caracteres.
        {
            touche = _getch();
            if (touche==0x50 && pos<nb_param-1)  // fleche bas
                pos = pos+1;
            if (touche==0x48 && pos>0)  // fleche haut
                pos = pos -1;
        }
        system("cls");
    } while (touche!=0x0D && touche!=0x4D);

    return pos;
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
