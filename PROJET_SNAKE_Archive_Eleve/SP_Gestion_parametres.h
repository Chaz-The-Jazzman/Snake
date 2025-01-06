#ifndef SP_GESTION_PARAMETRES_H_INCLUDED
#define SP_GESTION_PARAMETRES_H_INCLUDED

void init_global(TYPE_PARAM_JEU *param_jeu);
void init_jeu( TYPE_POMME *pomme, TYPE_SNAKE *snake, TYPE_SPEED_APPLE *speed_apple);
void colorparam(int color, int ligne);
void colorall();
void largeur_stade(int a);
int select_param_ud(int pos);
int select_param_lr(int pos);
#endif // SP_GESTION_PARAMETRES_H_INCLUDED
