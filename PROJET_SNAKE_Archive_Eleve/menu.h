#include "mesTypes.h"

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

void menu_principale(TYPE_PARAM_JEU param_jeu); //appelle du menu
void menu_parametres(TYPE_PARAM_JEU* param_jeu);
void afficher_menu_principale(int pos);
void afficher_menu_parametres(int pos, TYPE_PARAM_JEU param_jeu);
void afficher_menu_jouer(int pos, TYPE_PARAM_JEU param_jeu);
#endif // MENU_H_INCLUDED
