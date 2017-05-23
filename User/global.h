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
extern int n;

////////// ===== MEMORY ===== //////////
extern int complete_M;

////////// ===== BUZZER ===== //////////
extern int modeMusique;
extern int doubleNoteOn;
extern int etatSon;
extern int etatBuzzer;

extern int us_periodSound;
extern int us_periodDoubleNote;
extern int us_noteDuration;

extern int microSeconds;
extern int microSeconds2;
extern int microSeconds3;
extern int microSecondsMusique;

extern int musique[NB_NOTES_MAX][2];
extern int indiceCurrNote;

extern int frequTouches[NB_TOUCHE];

////////// ===== JEU ===== //////////
extern Touche jeu[10];
extern int posJeu;
extern int flagchange;
extern int menu;
extern int unJoueur;
extern int deuxJoueurs;
extern int flag_jeu;
extern int no_touch;
#endif
