#include <stdio.h>
#include <time.h>
#include "myLib.h"
#include "mesTypes.h"
#include "menu.h"
#include "SP_GESTION_JEU.h"
#include "SP_Gestion_parametres.h"
#include "SP_Affichage.h"

int SP_Gestion_Clavier(TYPE_SNAKE snek){
    char direction ;
    int dir;

    if ( kbhit()) {

    direction = (char)getkey() ;
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
    char direction2;
    char direction1;
    boolean exit_flag = FALSE;

    clock_t start_time = clock();

    // Wait for buffer time
    while (!exit_flag) {
        if ((clock() - start_time) > (buffer_time_ms * CLOCKS_PER_SEC) / 1000) {
            exit_flag = TRUE;
        }
        if (kbhit()) {
            direction2 = direction1;
            direction1 = (char)getkey();
        }
    }

    // Player 1 controls
    switch (direction1) {
        case KEY_UP:    *dir1 = HAUT; break;
        case KEY_DOWN:  *dir1 = BAS; break;
        case KEY_LEFT:  *dir1 = GAUCHE; break;
        case KEY_RIGHT: *dir1 = DROITE; break;
        case 'z': *dir2 = HAUT; break;
        case 's': *dir2 = BAS; break;
        case 'q': *dir2 = GAUCHE; break;
        case 'd': *dir2 = DROITE; break;
    }

    // Player 2 controls
    switch (direction2) {
        case KEY_UP:    *dir1 = HAUT; break;
        case KEY_DOWN:  *dir1 = BAS; break;
        case KEY_LEFT:  *dir1 = GAUCHE; break;
        case KEY_RIGHT: *dir1 = DROITE; break;
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
    // Si la taille du serpent n'est pas un multiple de 3, d�sactiver la pomme
    if (snake->taille % 3 != 0 && !invisible_apple->is_active) {
        invisible_apple->is_active = FALSE;
        invisible_apple->has_been_eaten = FALSE;
    }

    // Activer une nouvelle pomme si les conditions sont r�unies
    if (snake->taille % 3 == 0 && !invisible_apple->is_active && !invisible_apple->has_been_eaten) {
        invisible_apple->is_active = TRUE;
        invisible_apple->has_been_eaten = FALSE;
        invisible_apple->timer = generate_random_number(20, 40); // Dur�e d'invisibilit� en it�rations
        invisible_apple->pos.x = generate_random_number(2, param_Jeu.L_stade - 2);
        invisible_apple->pos.y = generate_random_number(2, param_Jeu.H_stade - 2);
    }

    // Si le serpent mange la pomme d'invisibilit�
    if (invisible_apple->is_active &&
        snake->tete.x == invisible_apple->pos.x &&
        snake->tete.y == invisible_apple->pos.y) {

        invisible_apple->is_active = FALSE;
        invisible_apple->has_been_eaten = TRUE;

        // Activer l'invisibilit�
        snake->is_invisible = TRUE;
        snake->invisibility_timer = invisible_apple->timer;
    }

    // G�rer l'invisibilit� active
    if (snake->is_invisible) {
        if (snake->invisibility_timer > 0) {
            snake->invisibility_timer--;
        } else {
            snake->is_invisible = FALSE; // Fin de l'invisibilit�
        }
    }
}


void gestion_teleport_apple(TYPE_SNAKE *snake, TYPE_TELEPORT_APPLE *teleport_apple, TYPE_PARAM_JEU param_Jeu) {
    // Si la taille du serpent n'est pas un multiple de 2, d�sactiver la pomme
    if (snake->taille %2 != 0 && !teleport_apple->is_active) {
        teleport_apple->is_active = FALSE;
        teleport_apple->has_been_eaten = FALSE;
    }

    // Activer une nouvelle pomme si les conditions sont r�unies
    if (snake->taille % 2 == 0 && !teleport_apple->is_active && !teleport_apple->has_been_eaten ) {
        teleport_apple->is_active = TRUE;
        teleport_apple->has_been_eaten = FALSE;
        teleport_apple->pos.x = generate_random_number(2, param_Jeu.L_stade - 2);
        teleport_apple->pos.y = generate_random_number(2, param_Jeu.H_stade - 2);
    }

    // Si le serpent mange la pomme t�l�porteuse
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

        // T�l�porte la t�te � une position al�atoire non égal à une position de la queue     
        int new_x = -1;
        int new_y = -1;
        while (new_x == -1 || new_y == -1) {
            new_x = generate_random_number(2, param_Jeu.L_stade - 2);
            new_y = generate_random_number(2, param_Jeu.H_stade - 2);
            for (int i = 0; i < snake->taille; i++) {
                if (new_x == snake->pos[i].x && new_y == snake->pos[i].y) {
                    new_x = -1;
                    new_y = -1;
                    break;
                }
            }
        }
        snake->tete.x = new_x;
        snake->tete.y = new_y;

        // // R�initialise tous les segments du serpent � la nouvelle position
        // for (int i = 0; i < snake->taille; i++) {
        //     snake->pos[i].x = new_x;
        //     snake->pos[i].y = new_y-i;
        // }

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
        // Effacer la bombe de l'�cran
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
            // Effacer la bombe de l'�cran
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
        // D�cr�menter le timer et v�rifier l'explosion
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
                msleep(70); // Pause entre les �tapes de l'explosion
            }

            // V�rifier si le serpent est � proximit�
            if (abs(snake->tete.x - explosive_apple->pos.x) <= 2 &&
                abs(snake->tete.y - explosive_apple->pos.y) <= 2) {
                snake->taille = (snake->taille > 2) ? snake->taille -2 : -1; // R�duire la taille
            }

            explosive_apple->is_active = FALSE;
        }
    }
    // Si la bombe a explos�, g�rer l'effet sur le serpent
    if (explosive_apple->has_exploded) {
        setBackgroundColor(param_Jeu.couleur_stade);
        int in_radius = abs(snake->tete.x - explosive_apple->pos.x) <= 2 &&
                        abs(snake->tete.y - explosive_apple->pos.y) <= 2;

        if (in_radius) {
            // R�duire la taille du serpent de 1 segment pour chaque entr�e dans le rayon
            if (snake->taille > 1) {
                // Effacer la queue du serpent
                gotoxy(snake->pos[snake->taille - 1].x, snake->pos[snake->taille - 1].y);
                printf(" ");
                snake->taille--; // R�duire la taille
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
    for (size_t i=0; i <= (size_t)snek.taille; i++)
    {
        //if a snake body position is same as head position, return true (meaning end of game is logic true)
        if( (snek.tete.x) == (snek.pos[i].x) &&  (snek.tete.y) == (snek.pos[i].y) )
            return TRUE;
    }

    //otherwise return false
    return FALSE;
}

int test_fin_jeu_2j(TYPE_SNAKE snake1, TYPE_SNAKE snake2, TYPE_PARAM_JEU param_Jeu, int *snake1_lose, int *snake2lose)
{
    if ((snake1.tete.x <= 1) || (snake1.tete.x >= param_Jeu.L_stade) || (snake1.tete.y <= 1) || (snake1.tete.y >= param_Jeu.H_stade)  )
    {
        //out of bounds
        *snake1_lose = TRUE;
        return TRUE;
    }

    //loop over all snake positions and check for collision
    for (size_t i=0; i <= (size_t)snake1.taille; i++)
    {
        //if a snake body position is same as head position, return true (meaning end of game is logic true)
        if( (snake1.tete.x) == (snake1.pos[i].x) &&  (snake1.tete.y) == (snake1.pos[i].y) )
        {
            *snake1_lose = TRUE;
            return TRUE;
        }
    }

    if ((snake2.tete.x <= 1) || (snake2.tete.x >= param_Jeu.L_stade) || (snake2.tete.y <= 1) || (snake2.tete.y >= param_Jeu.H_stade)  )
    {
        //out of bounds
        *snake2lose = TRUE;
        return TRUE;
    }

    //loop over all snake positions and check for collision
    for (size_t i=0; i <= (size_t)snake2.taille; i++)
    {
        //if a snake body position is same as head position, return true (meaning end of game is logic true)
        if( (snake2.tete.x) == (snake2.pos[i].x) &&  (snake2.tete.y) == (snake2.pos[i].y) )
        {
            *snake2lose = TRUE;
            return TRUE;
        }
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
    affichage_321GO();

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
        msleep((unsigned int)((2*speed*(float)speed_multiplyer/(float)param_Jeu.difficulte)));
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
        //jeu abandonn�
    }
    else
    {
        printgameover();
        //enregistrer score
        player.score = score;
        //afficher score
        printf("\n\nVotre score est de %d\n", player.score);
        //enregistrer nom
        ShowCursor(TRUE);
        printf("Entrez votre nom (ou appuyez sur Entrer pour ignorer): ");
        fgets(player.nom, sizeof(player.nom), stdin);
        ShowCursor(FALSE);
        // Vérifier si un nom a été entré
        if (player.nom[0] != '\n') {
            // Retirer le caractère de nouvelle ligne
            player.nom[strcspn(player.nom, "\n")] = 0;
            //ecrire score dans fichier scores.txt
            saveplayerscore(player);
        } else {
            printf("Score non enregistré.\n");
        }
    }
}

void Game_Loop_2j(TYPE_PARAM_JEU param_Jeu) {

    int fin_jeu = FALSE;

    int direction1 = DROITE, direction2 = GAUCHE;

    int snake1_lose = 0;
    int snake2_lose = 0;

    // Initialize snakes and pomme
    TYPE_SNAKE snek1, snek2;
    TYPE_POMME pom;
    TYPE_POMME pom2;
    TYPE_JOUEUR player1, player2;

    // Ask for player names
    ShowCursor(TRUE);
    printf("Entrez le nom du joueur 1: ");
    fgets(player1.nom, sizeof(player1.nom), stdin);
    player1.nom[strcspn(player1.nom, "\n")] = 0; // Remove newline character

    printf("Entrez le nom du joueur 2: ");
    fgets(player2.nom, sizeof(player2.nom), stdin);
    player2.nom[strcspn(player2.nom, "\n")] = 0; // Remove newline character
    ShowCursor(FALSE);

    system("cls");

    
    init_jeu_2j(&pom, &snek1, &snek2);
    init_pom_2(&pom2);

    affichage_stade(param_Jeu);

    while (!fin_jeu) {
        affichage_pomme(pom, param_Jeu);
        affichage_pomme(pom2, param_Jeu);

        affichage_Jeu_2j(snek1, snek2, &param_Jeu);

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
        test_pomme(&snek1, &pom2, param_Jeu);
        test_pomme(&snek2, &pom2, param_Jeu);

        // Check collisions for both snakes
        fin_jeu = test_fin_jeu_2j(snek1, snek2, param_Jeu, &snake1_lose, &snake2_lose);
    }
    printWinner(snake1_lose, param_Jeu);
    // add winner screen
    if (snake1_lose) {
        printf("VICTOIRE POUR %s\n\n", player2.nom);
    } else if (snake2_lose) {
        printf("VICTOIRE POUR %s!\n\n", player1.nom);
    }

    msleep(2000);
    system("pause");
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
    int line_number = 0;
    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        line_number++;
        if (line_number >= 1 && line_number <= 8) {
            printf("%s", ligne);
        }
    }
    printf("\n\n");
    fclose(f);
    system("pause");
}

void printWinner(int snake1lose, TYPE_PARAM_JEU param_Jeu)
{
    int line_min = 0;
    int line_max = 0;
    int color;
    if (snake1lose == 1) {
        line_min = 8;
        line_max = 32;
        color = param_Jeu.couleur_snake2;
    } else {
        line_min = 32;
        line_max = 56;
        color = param_Jeu.couleur_snake;
    }

    setBackgroundColor(BLACK);
    gotoxy(0,0);
    system("cls");
    
    setColor(color);

    char ligne[256];
    FILE *f;
    f = fopen("Game_Over_Art.txt", "r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
    int line_number = 0;
    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        line_number++;
        if (line_number >= line_min && line_number <= line_max) {
            printf("%s", ligne);
        }
    }
    printf("\n\n");
    fclose(f);
}
