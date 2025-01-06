#include "mesTypes.h"
#ifndef SP_AFFICHAGE_H_INCLUDED
#define SP_AFFICHAGE_H_INCLUDED

void affichage_stade(TYPE_PARAM_JEU param);
void affichage_Jeu(TYPE_SNAKE snake, TYPE_PARAM_JEU param);
void affichage_pomme(TYPE_POMME pomme,TYPE_PARAM_JEU param);
void Affichage_init_score(TYPE_PARAM_JEU param);
void Affichage_score(TYPE_PARAM_JEU param_jeu, int longueur_snake, int* score);
#endif // SP_AFFICHAGE_H_INCLUDED
