#include "mesTypes.h"
#ifndef SP_JEU_H_INCLUDED
#define SP_JEU_H_INCLUDED

int SP_Gestion_Clavier();

void calc_NextSnekPos(TYPE_SNAKE *snek);

void test_pomme(TYPE_SNAKE *snek, TYPE_POMME * pom, TYPE_PARAM_JEU param_Jeu);

boolean test_fin_jeu(TYPE_SNAKE snek, TYPE_PARAM_JEU param_Jeu);

void saveplayerscore(TYPE_JOUEUR player);

void printgameover();

void Game_Loop(TYPE_PARAM_JEU param_Jeu);

void printplayerscores();

void gestion_speed_apple(int * speed_multiplyer, TYPE_SPEED_APPLE * speed_apple, TYPE_SNAKE * snake, TYPE_PARAM_JEU param_Jeu);

#endif // SP_JEU_H_INCLUDED
