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
     int couleur_snake2;
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
   int is_invisible; // Nouveau : Flag d'invisibilit�
   int invisibility_timer;
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

typedef struct {
    int is_active;
    int has_appear;
    int has_exploded;
    int has_affected_snake;
    int timer; // Temps avant explosion
    int start_time;
    ST_POINT pos;
} TYPE_EXPLOSIVE_APPLE;

typedef struct {
    int is_active;
    int has_been_eaten;
    ST_POINT pos;
} TYPE_TELEPORT_APPLE;

typedef struct {
    int is_active;
    int has_been_eaten;
    int timer; // Dur�e d'invisibilit�
    ST_POINT pos;
} TYPE_INVISIBLE_APPLE;

typedef struct {
    char data[200][250]; // Circuit ASCII
    int width;          // Largeur du circuit
    int height;         // Hauteur du circuit
} Circuit;

typedef struct {
    TYPE_SNAKE snake;   // Le serpent
    int speed_multiplier; // Facteur de vitesse
    int finished;   // Le joueur a termin� le circuit
    int game_over;  // Le joueur a perdu
} MarioKartGame;

typedef struct {
    int x;
    int y;
} Position;

#endif // MESTYPES_H_INCLUDED
