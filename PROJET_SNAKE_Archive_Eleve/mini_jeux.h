#ifndef MINI_JEUX_H_INCLUDED
#define MINI_JEUX_H_INCLUDED

void charger_circuit(Circuit *circuit, const char *fichier);
void afficher_circuit(Circuit *circuit);
void calc_NextSnekPos_MarioKart(MarioKartGame *game, Circuit *circuit);
void Game_Loop_MarioKart(Circuit *circuit);
void redimensionner_terminal(int largeur, int hauteur);
#endif // MINI_JEUX_H_INCLUDED
