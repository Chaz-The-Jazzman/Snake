#include "mesTypes.h"
#ifndef SP_JEU_H_INCLUDED
#define SP_JEU_H_INCLUDED

int SP_Gestion_Clavier(TYPE_SNAKE snek);

void calc_NextSnekPos(TYPE_SNAKE *snek);

void test_pomme(TYPE_SNAKE *snek, TYPE_POMME * pom, TYPE_PARAM_JEU param_Jeu);

boolean test_fin_jeu(TYPE_SNAKE snek, TYPE_PARAM_JEU param_Jeu);
void saveplayerscore(TYPE_JOUEUR player);
int SP_Gestion_Clavier_with_buffer_time_2j(time_t buffer_time_ms, int *dir1, int *dir2, TYPE_SNAKE snek1, TYPE_SNAKE snek2);
void affichage(TYPE_PARAM_JEU param, TYPE_SNAKE snake, TYPE_POMME pomme, TYPE_SPEED_APPLE speed_apple,
               TYPE_INVISIBLE_APPLE invisible_apple, TYPE_EXPLOSIVE_APPLE explosive_apple, TYPE_TELEPORT_APPLE teleport_apple);
void gestion_special_apples(TYPE_SNAKE *snake, TYPE_EXPLOSIVE_APPLE *explosive_apple,
                            TYPE_TELEPORT_APPLE *teleport_apple, TYPE_INVISIBLE_APPLE *invisible_apple,
                            TYPE_PARAM_JEU param_Jeu);
void printgameover();
float adjust_speed(int direction);
void Game_Loop(TYPE_PARAM_JEU param_Jeu);
void Game_Loop_2j(TYPE_PARAM_JEU param_Jeu);
void printplayerscores();
#endif // SP_JEU_H_INCLUDED
