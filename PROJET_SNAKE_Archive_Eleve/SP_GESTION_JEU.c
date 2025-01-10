#include <stdio.h>
#include <time.h>
#include "myLib.h"
#include "mesTypes.h"
#include "menu.h"
#include "SP_GESTION_JEU.h"
#include "SP_Gestion_parametres.h"
#include "SP_Affichage.h"
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

// Fonction de pause pour simuler un délai en millisecondes
void pause(int milliseconds) {
    clock_t start_time = clock(); // Temps de début
    while (clock() < start_time + milliseconds * CLOCKS_PER_SEC / 1000);
}


int SP_Gestion_Clavier(TYPE_SNAKE snek){
    char direction ;
    int dir;

    if ( kbhit()) {

    direction = getkey() ;
    while (kbhit()) getkey();

    switch (direction){

        case KEY_UP : dir = HAUT ; break;
        case KEY_DOWN : dir = BAS ; break;
        case KEY_LEFT : dir = GAUCHE ; break;
        case KEY_RIGHT: dir= DROITE ; break;
        }
    }
    else {dir=-1;}

    if ((snek.direction == HAUT && dir ==BAS) || (snek.direction == BAS && dir == HAUT))
    {
        dir = snek.direction;
    }
    else if ((snek.direction == GAUCHE && dir ==DROITE) || (snek.direction == DROITE && dir == GAUCHE))
    {
        dir = snek.direction;
    }
    return dir;
}

float adjust_speed(int direction) {
    // Ajuster la vitesse en fonction de la direction
    if (direction == HAUT || direction == BAS) {
        return 4/2; // Augmente la vitesse (ralentit le jeu)
    } else {
        return 1; // Pas de changement pour gauche/droite
    }
}

int SP_Gestion_Clavier_with_buffer_time_2j(time_t buffer_time_ms, int *dir1, int *dir2, TYPE_SNAKE snek1,  TYPE_SNAKE snek2) {
    char direction;
    boolean exit_flag = FALSE;

    clock_t start_time = clock();

    // Wait for buffer time
    while (!exit_flag) {
        if ((clock() - start_time) > (buffer_time_ms * CLOCKS_PER_SEC) / 1000) {
            exit_flag = TRUE;
        }
        if (kbhit()) {
            direction = (char)getkey();
        }
    }

    // Player 1 controls
    switch (direction) {
        case KEY_UP:    *dir1 = HAUT; break;
        case KEY_DOWN:  *dir1 = BAS; break;
        case KEY_LEFT:  *dir1 = GAUCHE; break;
        case KEY_RIGHT: *dir1 = DROITE; break;
    }

    // Player 2 controls
    switch (direction) {
        case 'z': *dir2 = HAUT; break;
        case 's': *dir2 = BAS; break;
        case 'q': *dir2 = GAUCHE; break;
        case 'd': *dir2 = DROITE; break;
    }

    if ((snek1.direction == HAUT && *dir1 ==BAS) || (snek1.direction == BAS && *dir1 == HAUT))
    {
        *dir1 = snek1.direction;
    }
    else if ((snek1.direction == GAUCHE && *dir1 ==DROITE) || (snek1.direction == DROITE && *dir1 == GAUCHE))
    {
        *dir1 = snek1.direction;
    }

    if ((snek2.direction == HAUT && *dir2 ==BAS) || (snek2.direction == BAS && *dir2 == HAUT))
    {
        *dir2 = snek2.direction;
    }
    else if ((snek2.direction == GAUCHE && *dir2 ==DROITE) || (snek2.direction == DROITE && *dir2 == GAUCHE))
    {
        *dir2 = snek2.direction;
    }
    return 0;
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
            break;
    }

    int i = 0;
    //loop through all snake positions
    for (i=0; i < snek->taille-1; i++)
    {
        //replace, from tail to neck, positions of each snake part
        snek->pos[snek->taille-i-1] = snek->pos[snek->taille-i-2];
        //for ex, start with end of tail pos[4], replace with coordinates of pos[3], etc etc up to pos[1]
    }
    //replace pos[0] with old snake head
    snek->pos[0] = snek->old_head;
}
void placer_pomme(TYPE_POMME *pom, int hauteur, int largeur)
{
    pom->pos.x = generate_random_number(2,largeur-2);
    pom->pos.y = generate_random_number(2,hauteur-2);
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

void gestion_speed_apple(int * speed_multiplyer, TYPE_SPEED_APPLE * speed_apple, TYPE_SNAKE * snake, TYPE_PARAM_JEU param_Jeu)
{
    //reset has_been_eaten flag if snake has grown
    if (snake->taille % 5 != 0) speed_apple->has_been_eaten = FALSE;

    //if snake has grown and speed apple is not active, activate speed apple at random position
    if (snake->taille % 5 == 0 && !speed_apple->is_active && !speed_apple->has_been_eaten)
    {
        speed_apple->is_active = TRUE;
        speed_apple->has_been_eaten = FALSE;
        speed_apple->pos.x = generate_random_number(2, param_Jeu.L_stade-2);
        speed_apple->pos.y = generate_random_number(2, param_Jeu.H_stade-2);
        speed_apple->speed_mod = 50 * generate_random_number(1,5);
    }

    //if snake has eaten speed apple, set speed multiplyer to speed mod and disable speed apple
    if (speed_apple->pos.x == snake->tete.x && speed_apple->pos.y == snake->tete.y && speed_apple->is_active)
    {
        *speed_multiplyer = speed_apple->speed_mod;
        speed_apple->is_active = FALSE;
        speed_apple->has_been_eaten = TRUE;
    }

}

void gestion_invisible_apple(TYPE_SNAKE *snake, TYPE_INVISIBLE_APPLE *invisible_apple, TYPE_PARAM_JEU param_Jeu) {
    // Si la taille du serpent n'est pas un multiple de 3, désactiver la pomme
    if (snake->taille % 3 != 0 && !invisible_apple->is_active) {
        invisible_apple->is_active = FALSE;
        invisible_apple->has_been_eaten = FALSE;
    }

    // Activer une nouvelle pomme si les conditions sont réunies
    if (snake->taille % 3 == 0 && !invisible_apple->is_active && !invisible_apple->has_been_eaten) {
        invisible_apple->is_active = TRUE;
        invisible_apple->has_been_eaten = FALSE;
        invisible_apple->timer = generate_random_number(20, 40); // Durée d'invisibilité en itérations
        invisible_apple->pos.x = generate_random_number(2, param_Jeu.L_stade - 2);
        invisible_apple->pos.y = generate_random_number(2, param_Jeu.H_stade - 2);
    }

    // Si le serpent mange la pomme d'invisibilité
    if (invisible_apple->is_active &&
        snake->tete.x == invisible_apple->pos.x &&
        snake->tete.y == invisible_apple->pos.y) {

        invisible_apple->is_active = FALSE;
        invisible_apple->has_been_eaten = TRUE;

        // Activer l'invisibilité
        snake->is_invisible = TRUE;
        snake->invisibility_timer = invisible_apple->timer;
    }

    // Gérer l'invisibilité active
    if (snake->is_invisible) {
        if (snake->invisibility_timer > 0) {
            snake->invisibility_timer--;
        } else {
            snake->is_invisible = FALSE; // Fin de l'invisibilité
        }
    }
}


void gestion_teleport_apple(TYPE_SNAKE *snake, TYPE_TELEPORT_APPLE *teleport_apple, TYPE_PARAM_JEU param_Jeu) {
    // Si la taille du serpent n'est pas un multiple de 5, désactiver la pomme
    if (snake->taille %2 != 0 && !teleport_apple->is_active) {
        teleport_apple->is_active = FALSE;
        teleport_apple->has_been_eaten = FALSE;
    }

    // Activer une nouvelle pomme si les conditions sont réunies
    if (snake->taille % 2 == 0 && !teleport_apple->is_active && !teleport_apple->has_been_eaten ) {
        teleport_apple->is_active = TRUE;
        teleport_apple->has_been_eaten = FALSE;
        teleport_apple->pos.x = generate_random_number(2, param_Jeu.L_stade - 2);
        teleport_apple->pos.y = generate_random_number(2, param_Jeu.H_stade - 2);
    }

    // Si le serpent mange la pomme téléporteuse
    if (teleport_apple->is_active &&
        snake->tete.x == teleport_apple->pos.x &&
        snake->tete.y == teleport_apple->pos.y) {
        setBackgroundColor(param_Jeu.couleur_stade);
        for (int i = 0; i < snake->taille; i++) {
        gotoxy(snake->pos[i].x, snake->pos[i].y);
        printf(" ");  // Effacer chaque segment du serpent
    }

        // Effacer l'ancienne position de la queue
        gotoxy(snake->old_tail.x, snake->old_tail.y);
        printf(" ");  // Effacer l'ancienne queue
        gotoxy(snake->old_head.x, snake->old_head.y);
        printf(" ");

        gotoxy(teleport_apple->pos.x, teleport_apple->pos.y);
        printf(" ");

        // Téléporte la tête à une position aléatoire
        int new_x = generate_random_number(10, param_Jeu.L_stade - 10);
        int new_y = generate_random_number(10, param_Jeu.H_stade - 10);
        snake->tete.x = new_x;
        snake->tete.y = new_y;

        // Réinitialise tous les segments du serpent à la nouvelle position
        for (int i = 0; i < snake->taille; i++) {
            snake->pos[i].x = new_x;
            snake->pos[i].y = new_y-i;
        }

        teleport_apple->is_active = FALSE;
        teleport_apple->has_been_eaten = TRUE;


    }
}


void gestion_explosive_apple(TYPE_SNAKE *snake, TYPE_EXPLOSIVE_APPLE *explosive_apple, TYPE_PARAM_JEU param_Jeu) {

    if (snake->taille % 3 != 0 && !explosive_apple->is_active) {
        explosive_apple->has_appear = FALSE;
        explosive_apple->is_active = FALSE;
    }

    if (snake->taille % 3 == 0 && !explosive_apple->is_active && !explosive_apple->has_appear) {
        // Effacer la bombe de l'écran
            gotoxy(explosive_apple->pos.x, explosive_apple->pos.y);
            printf(" ");
            explosive_apple->is_active = FALSE;
            for (int radius = 0; radius <= 2; radius++) {
                setBackgroundColor(LIGHTGREEN);
                for (int dx = -radius; dx <= radius; dx++) {
                    for (int dy = -radius; dy <= radius; dy++) {
                        gotoxy(explosive_apple->pos.x + dx, explosive_apple->pos.y + dy);
                        printf(" ");
                    }
                }
            }
        explosive_apple->is_active = TRUE;
        explosive_apple->has_exploded = FALSE;
        explosive_apple->timer = generate_random_number(10, 20); // Explosion dans 5-10s
        explosive_apple->pos.x = generate_random_number(3, param_Jeu.L_stade - 3);
        explosive_apple->pos.y = generate_random_number(3, param_Jeu.H_stade - 4);
        explosive_apple->has_appear = TRUE;
      //  explosive_apple->start_time = 20;
    }

    /*if (explosive_apple->is_active && !explosive_apple->has_exploded) {
        if (explosive_apple->start_time > 1) {
            explosive_apple->start_time = explosive_apple->start_time - 1;
        }
        else
        {
            // Effacer la bombe de l'écran
            gotoxy(explosive_apple->pos.x, explosive_apple->pos.y);
            printf(" ");
            explosive_apple->is_active = FALSE;
            for (int radius = 0; radius <= 2; radius++) {
                setBackgroundColor(LIGHTGREEN);
                for (int dx = -radius; dx <= radius; dx++) {
                    for (int dy = -radius; dy <= radius; dy++) {
                        gotoxy(explosive_apple->pos.x + dx, explosive_apple->pos.y + dy);
                        printf(" ");
                    }
                }
            }
        }
    }*/
    if (explosive_apple->is_active) {
        // Décrémenter le timer et vérifier l'explosion
        if (--explosive_apple->timer <= 0 && !explosive_apple->has_exploded) {
            explosive_apple->has_exploded = TRUE;

            // Afficher un effet visuel pour l'explosion
            for (int radius = 0; radius <= 2; radius++) {
                setColor(RED);
                for (int dx = -radius; dx <= radius; dx++) {
                    for (int dy = -radius; dy <= radius; dy++) {
                         int x = explosive_apple->pos.x + dx;
                         int y = explosive_apple->pos.y + dy;
                         if (x >= 1 && x < param_Jeu.L_stade - 2 && y >= 1 && y < param_Jeu.H_stade - 2) {
                        gotoxy(x, y);
                        printf("*");
                    }
                    }
                }
                pause(70); // Pause entre les étapes de l'explosion
            }

            // Vérifier si le serpent est à proximité
            if (abs(snake->tete.x - explosive_apple->pos.x) <= 2 &&
                abs(snake->tete.y - explosive_apple->pos.y) <= 2) {
                snake->taille = (snake->taille > 2) ? snake->taille -2 : -1; // Réduire la taille
            }

            explosive_apple->is_active = FALSE;
        }
    }
    // Si la bombe a explosé, gérer l'effet sur le serpent
    if (explosive_apple->has_exploded) {
        setBackgroundColor(param_Jeu.couleur_stade);
        int in_radius = abs(snake->tete.x - explosive_apple->pos.x) <= 2 &&
                        abs(snake->tete.y - explosive_apple->pos.y) <= 2;

        if (in_radius) {
            // Réduire la taille du serpent de 1 segment pour chaque entrée dans le rayon
            if (snake->taille > 1) {
                // Effacer la queue du serpent
                gotoxy(snake->pos[snake->taille - 1].x, snake->pos[snake->taille - 1].y);
                printf(" ");
                snake->taille--; // Réduire la taille
            }
        }
    }
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
    for (i=0; i <= snek.taille; i++)
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
    boolean quit_flag = FALSE, fin_jeu = FALSE;
    int score = 0;
    int speed_multiplyer = 100;
    int direction = -1;
    system("cls");

    //initialisation du jeu
    TYPE_SNAKE snek;
    TYPE_POMME pom;
    TYPE_JOUEUR player;
    TYPE_SPEED_APPLE speed_apple;
    TYPE_EXPLOSIVE_APPLE explosive_apple;
    TYPE_INVISIBLE_APPLE invisible_apple;
    TYPE_TELEPORT_APPLE teleport_apple;

    init_jeu(&pom, &snek, &speed_apple, &invisible_apple, &explosive_apple, &teleport_apple);
    affichage_stade(param_Jeu);
    setBackgroundColor(16);
    Affichage_init_score(param_Jeu);
    while (!quit_flag && !fin_jeu )
    {
        if (snek.is_invisible) {
            affichage_Jeu_Invisible(snek, param_Jeu);
        } else {
            affichage(param_Jeu, snek, pom, speed_apple, invisible_apple, explosive_apple, teleport_apple);
        }

        //affichage(param_Jeu, snek, pom, speed_apple, invisible_apple, explosive_apple, teleport_apple);
        if(snek.taille != snek.oldtaille)
        {
            setBackgroundColor(16);
            Affichage_score(param_Jeu, snek.taille, &score);
            snek.oldtaille = snek.taille;
        }
        float speed = adjust_speed(snek.direction);
        msleep((time_t)((2*speed*speed_multiplyer/(float)param_Jeu.difficulte)));
        direction = SP_Gestion_Clavier(snek);

        if (direction != -1)  snek.direction = direction;
        calc_NextSnekPos(&snek);

        test_pomme(&snek, &pom, param_Jeu);
        gestion_speed_apple(&speed_multiplyer, &speed_apple, &snek, param_Jeu);
        gestion_explosive_apple(&snek, &explosive_apple, param_Jeu);
        gestion_teleport_apple(&snek, &teleport_apple, param_Jeu);
        gestion_invisible_apple(&snek, &invisible_apple, param_Jeu);

        fin_jeu = test_fin_jeu(snek, param_Jeu);
    }
    if (quit_flag)
    {
        //jeu abandonné
    }
    else
    {
        printgameover();
        //enregistrer score
        player.score = score;
        //afficher score
        printf("\n\nVotre score est de %d\n", player.score);
        //enregistrer nom
        printf("Entrez votre nom: ");
        scanf("%s", player.nom);
        //ecrire score dans fichier scores.txt
        saveplayerscore(player);
    }
}

void Game_Loop_2j(TYPE_PARAM_JEU param_Jeu) {
    int score1 = 0, score2 = 0;
    boolean quit_flag = FALSE, fin_jeu = FALSE;

    int direction1 = DROITE, direction2 = GAUCHE;

    // Initialize snakes and pomme
    TYPE_SNAKE snek1, snek2;
    TYPE_POMME pom;
    init_jeu_2j(&pom, &snek1, &snek2);

    affichage_stade(param_Jeu);

    while (!quit_flag && !fin_jeu) {
        affichage_pomme(pom, param_Jeu);
        affichage_Jeu_2j(snek1, snek2, param_Jeu);

        // Get inputs for both players
        SP_Gestion_Clavier_with_buffer_time_2j((time_t)((1/(float)param_Jeu.difficulte)*200), &direction1, &direction2, snek1, snek2);

        if (direction1 != -1) snek1.direction = direction1;
        if (direction2 != -1) snek2.direction = direction2;

        // Move both snakes
        calc_NextSnekPos(&snek1);
        calc_NextSnekPos(&snek2);

        // Check collisions with pomme
        test_pomme(&snek1, &pom, param_Jeu);
        test_pomme(&snek2, &pom, param_Jeu);

        // Check collisions for both snakes
        fin_jeu = test_fin_jeu(snek1, param_Jeu) || test_fin_jeu(snek2, param_Jeu);

        // Collision detection between snakes
        for (int i = 0; i < snek2.taille; i++) {
            if (snek1.tete.x == snek2.pos[i].x && snek1.tete.y == snek2.pos[i].y) {
                fin_jeu = TRUE;
            }
        }
        for (int i = 0; i < snek1.taille; i++) {
            if (snek2.tete.x == snek1.pos[i].x && snek2.tete.y == snek1.pos[i].y) {
                fin_jeu = TRUE;
            }
        }
    }
    printgameover();
    printf("Player 1 Score: %d\n", score1);
    printf("Player 2 Score: %d\n", score2);
}

/**
 * @brief Sauvegarde le score du joueur dans un fichier.
 *
 * @param player - Structure du joueur contenant le nom et le score.
 */
void saveplayerscore(TYPE_JOUEUR player)
{

    FILE *score_file = fopen("scores.txt", "a");
    if (score_file != NULL) {
        fprintf(score_file, "Nom: %s  ", player.nom);
        fprintf(score_file, "Score: %d\n", player.score);
        fclose(score_file);
    } else {
        printf("Erreur: Impossible d'ouvrir le fichier des scores.\n");
    }
}

void printplayerscores()
{
    system("cls");
    FILE *score_file = fopen("scores.txt", "r");
    if (score_file != NULL)
    {
        char line[256];
        while (fgets(line, sizeof(line), score_file) != NULL)
        {
            printf("%s", line);
        }
        fclose(score_file);
    } else
    {
        printf("Erreur: Impossible d'ouvrir le fichier des scores.\n");
    }
    system("pause");
    system("cls");
}

void printgameover()
{
    setBackgroundColor(BLACK);
    gotoxy(0,0);
    system("cls");
    ShowCursor(TRUE);
    setColor(RED);
    char ligne[256];
    FILE *f;
    f = fopen("Game_Over_Art.txt", "r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        printf("%s", ligne);
    }
    printf("\n\n");
    system("pause");
    fclose(f);
}
