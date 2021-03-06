#include "constantes.h" // fichier contenant toutes les constantes du projet
#include <stdint.h>

#ifndef GLOBAL_H
#define GLOBAL_H

// mettez ici toutes les "extern" correspondant aux déclarations contenues dans globadec.h

////////// ===== AFFICHAGE ===== //////////
// buffer pour l'affichage sur le LCD
extern char chaine[30];
extern uint16_t touch_x, touch_y;
extern int flagtacheclavier;
extern int flagappuitactile;
extern int flagrepetitiontouche;
extern int flagchangecouleur;
extern int n;

////////// ===== MEMORY ===== //////////
extern int complete_M;

////////// ===== BUZZER ===== //////////
extern int etatSon;
extern int etatBuzzer;
extern int us_periodSound;
extern int us_noteDuration;
extern int microSeconds;
extern int microSeconds2;

extern int frequTouches[NB_TOUCHE];

extern const int NB_NOTES;
extern int notes[8];
extern int indiceCurrNote;

////////// ===== JEU ===== //////////
extern Touche courant;
extern int joueur1;
extern int joueur2;
extern int gagne;
extern int perdu;
extern uint16_t posJeu;
extern int seqLength;
extern int menu;
extern int unJoueur;
extern int deuxJoueurs;
extern int flag_lecture_touche;
extern int flag_lecture_seq;
extern int flag_jeu;
extern int no_touch;
#endif
