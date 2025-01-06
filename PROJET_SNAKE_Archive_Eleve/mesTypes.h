#ifndef MESTYPES_H_INCLUDED
#define MESTYPES_H_INCLUDED


//*********************
// structure POINT (x,y)
//*********************
typedef struct {
     int x;
     int y;
} ST_POINT;


//*********************
// PARAMETRES de JEU
//*********************
typedef struct {
     int couleur_stade;
     int couleur_snake;
     int difficulte;
     int H_stade;
     int L_stade;

} TYPE_PARAM_JEU;

//******************
// DONNEES JOUEUR
//******************
typedef struct {
     char nom[20];
     int score;
} TYPE_JOUEUR;

//******************
// DONNEES SNAKE
//******************
typedef struct {
   ST_POINT pos[30];
   ST_POINT tete;
   ST_POINT old_tail;
   ST_POINT old_head;
   int direction;
   int taille;
   int oldtaille;

} TYPE_SNAKE;

//******************
// DONNEES POMME
//******************
typedef struct {
   ST_POINT pos;
} TYPE_POMME;

typedef struct {
     int is_active;
     int has_been_eaten;
     ST_POINT pos;
     int speed_mod;
} TYPE_SPEED_APPLE;



#endif // MESTYPES_H_INCLUDED
