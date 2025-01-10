#include <stdio.h>
#include <string.h>
#include "myLib.h"
#include "mesTypes.h"
#include "menu.h"
#include "SP_GESTION_JEU.h"
#include "SP_Gestion_parametres.h"
#include "SP_Affichage.h"

#define WALL '#'//219
#define WALL2 '.'
#define ROAD ' '//176
#define FINISH 'F'

#include <stdlib.h>
#include <windows.h>

#include <windows.h>
#include <stdio.h>
#include <windows.h>
#include <stdio.h>

#include <windows.h>
#include <stdio.h>



void maximiser_console() {
    HWND console_window = GetConsoleWindow();
    if (!console_window) {
        printf("Erreur : Impossible d'obtenir la fenêtre de la console.\n");
        return;
    }

    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
    if (handle_out == INVALID_HANDLE_VALUE) {
        printf("Erreur : Impossible d'obtenir le handle de sortie.\n");
        return;
    }

    // Obtenir la taille maximale du terminal
    COORD largest_size = GetLargestConsoleWindowSize(handle_out);
    if (!largest_size.X || !largest_size.Y) {
        printf("Erreur : Impossible de déterminer la taille maximale.\n");
        return;
    }

    // Réduire légèrement pour éviter les dépassements
    largest_size.X--;
    largest_size.Y--;

    // Ajuster la taille du buffer à la taille maximale
    if (!SetConsoleScreenBufferSize(handle_out, largest_size)) {
        printf("Erreur : Impossible de redimensionner le buffer.\n");
        return;
    }

    // Maximiser la fenêtre du terminal
    if (!ShowWindow(console_window, SW_MAXIMIZE)) {
        printf("Erreur : Impossible de maximiser la fenêtre.\n");
        return;
    }

    printf("Console maximisee avec succes !\n");
}


void charger_circuit(Circuit *circuit, const char *fichier) {
    FILE *file = fopen("mario2.txt", "r");
    if (!file) {
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", fichier);
        return;
    }

    char ligne[200];
    int y = 0;

    while (fgets(ligne, sizeof(ligne), file) && y < 150) {
        strncpy(circuit->data[y], ligne, strlen(ligne));
        circuit->data[y][strlen(ligne) - 1] = '\0'; // Supprimer le saut de ligne
        y++;
    }
    circuit->height = y;
    circuit->width = strlen(circuit->data[0]);
    fclose(file);
}

void afficher_circuit(Circuit *circuit) {
    for (int y = 0; y < circuit->height; y++) {
        for (int x = 0; x < circuit->width; x++) {
            switch (circuit->data[y][x]) {
                case WALL: // Mur
                    setBackgroundColor(GREEN);
                    printf(" ");
                    break;
                case ROAD: // Route
                    setBackgroundColor(BLACK);
                    printf(" ");
                    break;
                case WALL2:
                    setBackgroundColor(LIGHTGREEN);
                    printf(" ");
                    break;
                case FINISH: // Ligne d’arrivée
                    setBackgroundColor(GREEN);
                    setColor(WHITE);
                    printf("F");
                    break;
                case 'B': // Bonus
                    setBackgroundColor(YELLOW);
                    setColor(BLACK);
                    printf("B");
                    break;
                case 'X': // Piège
                    setBackgroundColor(MAGENTA);
                    setColor(WHITE);
                    printf("X");
                    break;
                default:
                    setBackgroundColor(BLACK);
                    printf("%c", circuit->data[y][x]);
                    break;
            }
        }
        printf("\n");
    }
    setBackgroundColor(BLACK);
}


void calc_NextSnekPos_MarioKart(MarioKartGame *game, Circuit *circuit) {
    ST_POINT new_head = game->snake.tete;
    switch (game->snake.direction) {
        case GAUCHE: new_head.x--; break;
        case DROITE: new_head.x++; break;
        case HAUT: new_head.y--; break;
        case BAS: new_head.y++; break;
    }

    char case_type = circuit->data[new_head.y][new_head.x];
    if (case_type == 'X') {
        game->game_over = TRUE;
    } else if (case_type == 'F') {
        game->finished = TRUE;
    }

    if (!game->game_over && !game->finished) {
        game->snake.old_tail = game->snake.pos[game->snake.taille - 1];
        for (int i = game->snake.taille - 1; i > 0; i--) {
            game->snake.pos[i] = game->snake.pos[i - 1];
        }
        game->snake.pos[0] = game->snake.tete;
        game->snake.tete = new_head;
    }
}


void Game_Loop_MarioKart(Circuit *circuit) {

    //maximiser_console();
//    configurer_console(120, 100);
    system("pause");
    TYPE_SNAKE snake;
    MarioKartGame game;

    // Initialisation
    init_mario_kart(&snake, &game, circuit);

    // Afficher le circuit une seule fois
    system("cls");
    afficher_circuit(circuit);


    // Boucle principale
    while (!game.game_over && !game.finished) {
        // Afficher uniquement le serpent (mise à jour)
        affichage_Jeu(game.snake, (TYPE_PARAM_JEU) { .couleur_stade = 0, .couleur_snake = 5 });

        // Gestion des entrées clavier
        int direction = SP_Gestion_Clavier(game.snake);
        if (direction != -1) game.snake.direction = direction;

        // Calcul de la prochaine position
        calc_NextSnekPos_MarioKart(&game, circuit);

        // Pause ajustée par le multiplicateur de vitesse
        msleep(game.speed_multiplier);
    }

    // Résultat de la partie
    if (game.game_over) {
        printf("\nGame Over! Vous avez percuté un mur.\n");
    } else if (game.finished) {
        printf("\nFélicitations! Vous avez terminé le circuit.\n");
    }
}

