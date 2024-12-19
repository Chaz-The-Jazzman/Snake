#include "mesTypes.h"
#ifndef SP_JEU_H_INCLUDED
#define SP_JEU_H_INCLUDED

int SP_Gestion_Clavier();

void affichage_Jeu(TYPE_POMME pomme, TYPE_SNAKE snake, TYPE_PARAM_JEU param);

void calc_NextSnekPos(TYPE_SNAKE *snek);

void test_pomme(TYPE_SNAKE *snek, TYPE_POMME * pom, TYPE_PARAM_JEU param_Jeu);

boolean test_fin_jeu(TYPE_SNAKE snek, TYPE_PARAM_JEU param_Jeu);

int SP_Gestion_Clavier_with_buffer_time(time_t buffer_time_ms);

void Game_Loop(TYPE_PARAM_JEU param_Jeu);
#endif // SP_JEU_H_INCLUDED
