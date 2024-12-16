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
   int direction;
   int taille;

} TYPE_SNAKE;

//******************
// DONNEES POMME
//******************
 typedef struct {
   ST_POINT pos;
} TYPE_POMME;


#endif // MESTYPES_H_INCLUDED
