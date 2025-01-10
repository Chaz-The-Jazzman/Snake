#ifndef SP_GESTION_PARAMETRES_H_INCLUDED
#define SP_GESTION_PARAMETRES_H_INCLUDED

void init_global(TYPE_PARAM_JEU *param_jeu);
void init_jeu(TYPE_POMME* pomme, TYPE_SNAKE* snake, TYPE_SPEED_APPLE* speed_apple, TYPE_INVISIBLE_APPLE* invisible_apple, TYPE_EXPLOSIVE_APPLE* explosive_apple,
              TYPE_TELEPORT_APPLE* teleport_apple);
void init_jeu_2j(TYPE_POMME* pomme, TYPE_SNAKE* snake1, TYPE_SNAKE* snake2);
void init_mario_kart(TYPE_SNAKE *snake, MarioKartGame *game, Circuit *circuit);
void colorparam(int color, int ligne);
void colorall();
void largeur_stade(int pos, TYPE_PARAM_JEU param_jeu);
int select_param_ud(int pos);
int select_param_lr(int pos);
int select_param(TYPE_PARAM_JEU param_jeu, int nb_param, int funct);

#endif // SP_GESTION_PARAMETRES_H_INCLUDED
