#include <stdio.h>
#include <time.h>
#include "myLib.h"
#include "mesTypes.h"
#include "menu.h"
#include "SP_GESTION_JEU.h"
#include "SP_Gestion_parametres.h"
/*===================================================================================
/ Nom Sémantique : FONCTION SP_Gestion_Clavier

/ Sémantique : Gère la détection des évènements clavier sur les touches de direction

/ Paramètres :
/ direction (OUT) - entier : Contient la direction sollicitée par l'utilisateur
/ DROITE = 0 , GAUCHE = 1 , BAS = 2 , HAUT = 3 et -1 SINON
/ Pré-condition : AUCUNE
/ Post conditions : la direction vaut -1,0,1,2,3
/ ====================================================================================
/ Test : le chiffre renvoyé correspond à la direction appuyée
/ ====================================================================================*/
int SP_Gestion_Clavier(){
    char direction ;
    int dir;

    if ( kbhit()) {

    direction = getkey() ;

    switch (direction){

        case KEY_UP : dir = HAUT ; break;
        case KEY_DOWN : dir = BAS ; break;
        case KEY_LEFT : dir = GAUCHE ; break;
        case KEY_RIGHT: dir= DROITE ; break;
        }
    }
    else {dir=-1;}
    return dir;
}

void affichage_Jeu(TYPE_POMME pomme, TYPE_SNAKE snake, TYPE_PARAM_JEU param)
{
    system("cls");
    int x=1;
    int y=1;
    setColor(3);
    for(y=1;y<param.H_stade;y++)
    {

        for(x=1;x<param.L_stade;x++)
        {
            if(x==1 || x ==param.L_stade-1 || y == 1 || y == param.H_stade-1)
            {
                printStadeElement();
            }
            else if(x == snake.tete.x && y == snake.tete.y)
            {
                printSnakeHead();
            }
            else if(x == pomme.pos.x && y == pomme.pos.y)
            {
                printPomme();
            }
            else
            {
                printf(" ");
            }

        }
        printf("\n\r");
    }
    //for(s=1;)
   // system("pause");
}

int SP_Gestion_Clavier_with_buffer_time(time_t buffer_time_ms)
{
    char direction;
    int dir = -1;  // Default direction if no key is pressed
    boolean exit_flag = FALSE;

    clock_t start_time = clock();  // Record start time

    // Wait for buffer time before taking the last inputted key
    while (exit_flag == FALSE )
        {
        if ((clock() - start_time) > (buffer_time_ms * CLOCKS_PER_SEC) / 1000)
            exit_flag = TRUE;
        if (kbhit()) {
            //printf("key pressed\n");
            direction = (char)getkey();  // Get the last key pressed
        }
    }

    // After buffer time, process the last key pressed
    switch (direction)
    {
        case KEY_UP:
            dir = HAUT;
            break;
        case KEY_DOWN:
            dir = BAS;
            break;
        case KEY_LEFT:
            dir = GAUCHE;
            break;
        case KEY_RIGHT:
            dir = DROITE;
            break;
        default:
            dir = -1;  // If no key pressed or invalid key
            break;
    }

    return dir;  // Return the final direction
}


void calc_NextSnekPos(TYPE_SNAKE *snek)
{
    //save new old head
    snek->old_head = snek->tete;
    //save new "old tail"
    snek->old_tail = snek->pos[snek->taille-1];

    //move head position as function of direction
    switch (snek->direction)
    {
        case GAUCHE:
            snek->tete.x -= 1;
            break;
        case DROITE:
            snek->tete.x += 1;
            break;
        case HAUT:
            snek->tete.y -= 1;
            break;
        case BAS:
            snek->tete.y += 1;
            break;
        default:
            //problem
            break;
    }

    int i = 0;
    //loop through all snake positions
    for (i; i < snek->taille-1; i++)
    {
        //replace, from tail to neck, positions of each snake part
        snek->pos[snek->taille-i-1] = snek->pos[snek->taille-i-2];
        //for ex, start with end of tail pos[4], replace with coordinates of pos[3], etc etc up to pos[1]
    }
    //replace pos[0] with old snake head
    snek->pos[0] = snek->old_head;



}

void test_pomme(TYPE_SNAKE *snek, TYPE_POMME * pom, TYPE_PARAM_JEU param_Jeu)
{
    if ((snek->tete.x == pom->pos.x) && (snek->tete.y == pom->pos.y))
    {
        snek->taille += 1;
        snek->pos[snek->taille-1] = snek->old_tail;
        placer_pomme(pom, param_Jeu.H_stade, param_Jeu.L_stade);
    }

}

void placer_pomme(TYPE_POMME *pom, int largeur, int hauteur)
{
    pom->pos.x = generate_random_number(2,largeur);
    pom->pos.y = generate_random_number(2, hauteur);
}

boolean test_fin_jeu(TYPE_SNAKE snek, TYPE_PARAM_JEU param_Jeu)
{
    if ((snek.tete.x <= 1) || (snek.tete.x >= param_Jeu.L_stade) || (snek.tete.y <= 1) || (snek.tete.y >= param_Jeu.H_stade)  )
    {
        //out of bounds
        return TRUE;
    }

    //loop over all snake positions and check for collision
    size_t i = 0;
    for (i; i <= snek.taille; i++)
    {
        //if a snake body position is same as head position, return true (meaning end of game is logic true)
        if( (snek.tete.x) == (snek.pos[i].x) &&  (snek.tete.y) == (snek.pos[i].y) )
            return TRUE;
    }

    //otherwise return false
    return FALSE;
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

    init_param(&param_Jeu,&pom, &snek);

    placer_pomme(&pom, param_Jeu.H_stade, param_Jeu.L_stade);


    while (!quit_flag || !fin_jeu )
    {
        affichage_Jeu(pom, snek, param_Jeu);
        switch (param_Jeu.difficulte)
        {
            case 1:
                direction = SP_Gestion_Clavier_with_buffer_time(750);
                break;
            case 2:
                direction = SP_Gestion_Clavier_with_buffer_time(500);
                break;
            case 3:
                direction = SP_Gestion_Clavier_with_buffer_time(250);
                break;
            default:
                direction = SP_Gestion_Clavier_with_buffer_time(1000);
                break;
        }
        if (direction != -1)
        {
            snek.direction = direction;
        }

        //snek.direction = SP_Gestion_Clavier(100);

        calc_NextSnekPos(&snek);

        test_pomme(&snek, &pom, param_Jeu);
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
