#include <stdio.h>
#include <time.h>
#include "myLib.h"
#include "SP_GESTION_JEU.h"

/*===================================================================================
/ Nom S�mantique : FONCTION SP_Gestion_Clavier

/ S�mantique : G�re la d�tection des �v�nements clavier sur les touches de direction

/ Param�tres :
/ direction (OUT) - entier : Contient la direction sollicit�e par l'utilisateur
/ DROITE = 0 , GAUCHE = 1 , BAS = 2 , HAUT = 3 et -1 SINON
/ Pr�-condition : AUCUNE
/ Post conditions : la direction vaut -1,0,1,2,3
/ ====================================================================================
/ Test : le chiffre renvoy� correspond � la direction appuy�e
/ ====================================================================================*/
int SP_Gestion_Clavier(time_t buffer_time_ms) {
    char direction;
    int dir = -1;  // Default direction if no key is pressed
    boolean exit_flag = FALSE;

    clock_t start_time = clock();  // Record start time

    // Wait for buffer time before taking the last inputted key
    while (exit_flag = FALSE )
        {
        if ((clock() - start_time) > (buffer_time_ms * CLOCKS_PER_SEC) / 1000)
            exit_flag = TRUE;
        if (kbhit()) {
            printf("key pressed\n");
            direction = (char)getkey();  // Get the last key pressed
        }
    }

    // After buffer time, process the last key pressed
    switch (direction) {
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
    switch (snek->direction) {
        case GAUCHE:
            snek->tete.x -= 1;
            break;
        case DROITE:
            snek->tete.x += 1;
            break;
        case HAUT:
            snek->tete.y += 1;
            break;
        case BAS:
            snek->tete.y -= 1;
            break;
        default:
            //problem
            break;

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

    //loop over all snake positions
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
