#include <stdio.h>
#include "mesTypes.h"
#include "myLib.h"

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



void affichage_Jeu_2j(TYPE_SNAKE snake1, TYPE_SNAKE snake2, TYPE_PARAM_JEU *param) {
    int i;

    setBackgroundColor(param->couleur_stade);

    // Draw Snake 1
    setColor(param->couleur_snake);
    for (i = 0; i < snake1.taille; i++) {
        gotoxy(snake1.pos[i].x, snake1.pos[i].y);
        printSnakeBody();
    }
    gotoxy(snake1.tete.x, snake1.tete.y);
    printSnakeHead();

    // Clear Snake 1's old tail
    gotoxy(snake1.old_tail.x, snake1.old_tail.y);
    printf(" ");

    // Draw Snake 2
    param->couleur_snake2 = RED; // Example color for Snake 2
    setColor(param->couleur_snake2); 
    for (i = 0; i < snake2.taille; i++) {
        gotoxy(snake2.pos[i].x, snake2.pos[i].y);
        printSnakeBody();
    }
    gotoxy(snake2.tete.x, snake2.tete.y);
    printSnakeHead();

    // Clear Snake 2's old tail
    gotoxy(snake2.old_tail.x, snake2.old_tail.y);
    printf(" ");
}

void affichage_Jeu(TYPE_SNAKE snake, TYPE_PARAM_JEU param) {
    setBackgroundColor(param.couleur_stade);
    setColor(param.couleur_snake);

    // Afficher tous les segments du serpent
    for (int i = 0; i < snake.taille; i++) {
        gotoxy(snake.pos[i].x, snake.pos[i].y);
        printSnakeBody();
    }

    // Afficher la t�te
    gotoxy(snake.tete.x, snake.tete.y);
    printSnakeHead();

    // Effacer l'ancienne position de la queue
    gotoxy(snake.old_tail.x, snake.old_tail.y);
    printf(" ");
}

void affichage_pomme(TYPE_POMME pomme,TYPE_PARAM_JEU param)
{
    setBackgroundColor(param.couleur_stade);
    gotoxy(pomme.pos.x, pomme.pos.y);
    printPomme();
}

void affichage_speed_apple(TYPE_SPEED_APPLE speed_apple, TYPE_PARAM_JEU param)
{
    if(speed_apple.is_active)
    {
    setBackgroundColor(param.couleur_stade);
    gotoxy(speed_apple.pos.x, speed_apple.pos.y);
    setColor(YELLOW);
    printf("S");
    }
}

void affichage_Jeu_Invisible(TYPE_SNAKE snake, TYPE_PARAM_JEU param) {
    // Remplir la position actuelle du serpent avec le fond

    for (int i = 0; i < snake.taille; i++) {
        gotoxy(snake.pos[i].x, snake.pos[i].y);
        setBackgroundColor(param.couleur_stade);
        printf(" ");
    }
    gotoxy(snake.old_tail.x, snake.old_tail.y);
    printf(" ");
}

void affichage_explosive_apple(TYPE_EXPLOSIVE_APPLE explosive_apple) {

    if (explosive_apple.is_active) {
        gotoxy(explosive_apple.pos.x, explosive_apple.pos.y);
        setColor(RED);
        printf("E"); // Une pomme explosive repr�sent�e par 'E'
    }
}

void affichage_teleport_apple(TYPE_SNAKE snake, TYPE_TELEPORT_APPLE teleport_apple) {
    if (teleport_apple.is_active) {
        gotoxy(teleport_apple.pos.x, teleport_apple.pos.y);
        setColor(BLUE);
        printf("T"); // Une pomme t�l�porteuse repr�sent�e par 'T'
    }
}

void affichage_invisible_apple(TYPE_INVISIBLE_APPLE invisible_apple) {
    if (invisible_apple.is_active) {
        gotoxy(invisible_apple.pos.x, invisible_apple.pos.y);
        setColor(GREEN);
        printf("I"); // Une pomme d'invisibilit� repr�sent�e par 'I'
    }
}

void affichage(TYPE_PARAM_JEU param, TYPE_SNAKE snake, TYPE_POMME pomme, TYPE_SPEED_APPLE speed_apple,
               TYPE_INVISIBLE_APPLE invisible_apple, TYPE_EXPLOSIVE_APPLE explosive_apple, TYPE_TELEPORT_APPLE teleport_apple)
{
    affichage_pomme(pomme, param);
    affichage_speed_apple(speed_apple, param);
    affichage_invisible_apple(invisible_apple);
    affichage_teleport_apple(snake, teleport_apple);
    affichage_explosive_apple(explosive_apple);
    affichage_Jeu(snake, param);
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

void affichage_321GO(void)
{
    unsigned int mstime_interval = 1000;
    FILE *file;
    char line[256];
    int line_number = 0;

    system("cls");
    setColor(RED);
    file = fopen("go321go_art.txt", "r");
    if (file != NULL) {
        while (fgets(line, sizeof(line), file)) {
            line_number++;
            if (line_number >= 1 && line_number <= 10-1) {
                gotoxy(40, 10 + (line_number - 1));
                printf("%s", line);
            }
        }
        fclose(file);
    }
    msleep(mstime_interval);

    system("cls");
    setColor(YELLOW);
    line_number = 0;
    file = fopen("go321go_art.txt", "r");
    if (file != NULL) {
        while (fgets(line, sizeof(line), file)) {
            line_number++;
            if (line_number >= 10 && line_number <= 20-1) {
                gotoxy(40, 10 + (line_number - 10));
                printf("%s", line);
            }
        }
        fclose(file);
    }
    msleep(mstime_interval);

    system("cls");
    setColor(GREEN);
    line_number = 0;
    file = fopen("go321go_art.txt", "r");
    if (file != NULL) {
        while (fgets(line, sizeof(line), file)) {
            line_number++;
            if (line_number >= 20 && line_number <= 30-1) {
                gotoxy(40, 10 + (line_number - 20));
                printf("%s", line);
            }
        }
        fclose(file);
    }
    msleep(mstime_interval);

    system("cls");
    setColor(LIGHTBLUE);
    line_number = 0;
    file = fopen("go321go_art.txt", "r");
    if (file != NULL) {
        while (fgets(line, sizeof(line), file)) {
            line_number++;
            if (line_number >= 30 && line_number <= 40-1) {
                gotoxy(40, 10 + (line_number - 30));
                printf("%s", line);
            }
        }
        fclose(file);
    }
    msleep(mstime_interval);

    system("cls");
    setColor(WHITE);
}
