#include <stdio.h>
#include <time.h>
#include "myLib.h"
#include "mesTypes.h"
#include "menu.h"
#include "SP_GESTION_JEU.h"
#include "SP_Gestion_parametres.h"
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
int SP_Gestion_Clavier(){
    char direction ;
    int dir;

    if ( kbhit()) {

    direction = (char)getkey() ;

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
    for (i = 0; i < snek->taille-1; i++)
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
    int i;
    for(i=0; i <= snek.taille; i++)
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

    //initialisation des structures
    TYPE_SNAKE snek;
    TYPE_POMME pom;
    TYPE_JOUEUR player;

    //conditions de depart
    init_param(&param_Jeu,&pom, &snek);
    placer_pomme(&pom, param_Jeu.H_stade, param_Jeu.L_stade);


    //boucle de jeu
    while (!quit_flag || !fin_jeu )
    {
        //affichage du jeu
        affichage_Jeu(pom, snek, param_Jeu);

        //gestion du clavier
        direction = SP_Gestion_Clavier_with_buffer_time((1/param_Jeu.difficulte)*500);
        if (direction != -1)
        {
            snek.direction = direction;
        }

        //calcul de la prochaine position du snake
        calc_NextSnekPos(&snek);

        //test de collision avec la pomme
        test_pomme(&snek, &pom, param_Jeu);

        //test de fin de jeu
        fin_jeu = test_fin_jeu(snek, param_Jeu);
    }

    
    if (quit_flag)
    {
        
    }
    else
    {
        //enregistrer score
        player.score = snek.taille;
        system("clc");
        //afficher score
        printf("Votre score est de %d\n", player.score);
        //enregistrer nom
        printf("Entrez votre nom: ");
        scanf("%s", player.nom);
        //ecrire score dans fichier scores.txt
        saveplayerscore(player);
    }
}

void saveplayerscore(TYPE_JOUEUR player)
{
    FILE *score_file = fopen("scores.txt", "a");
    if (score_file != NULL) {
        fprintf(score_file, "Score: %d\n", player.score);
        fclose(score_file);
    } else {
        printf("Erreur: Impossible d'ouvrir le fichier des scores.\n");
    }
}
