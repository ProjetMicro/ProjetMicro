#include "constantes.h" // fichier contenant toutes les constantes du projet
#include <stdint.h>
#include "lpc17xx_i2c.h" //Aucunne utilit�e pour le moment, laisser au cas o�

#ifndef GLOBALDEC_H
#define GLOBALDEC_H
// mettez ici toutes les d�clarations de variables globales
////////// ===== AFFICHAGE ===== //////////
// buffer pour l'affichage sur le LCD
char chaine[30];
uint16_t touch_x, touch_y;
int flagtacheclavier = 0;
int flagappuitactile = 0;
int flagrepetitiontouche = 0;
int flagchangecouleur = 0;
int n;

////////// ===== MEMORY ===== //////////
int complete_M;

////////// ===== BUZZER ===== //////////
int etatSon = 0;
int etatBuzzer = 0;
int us_periodSound = 0;
int us_noteDuration = 0;
int microSeconds = 0;
int microSeconds2 = 0;

/* Frequence de la note associee a un bouton */
int frequTouches[NB_TOUCHE] = {
	DO, //Son touche JAUNE
	MI, //Son touche VERT
	SO, //Son touche ROUGE
	SI, //Son touche BLEU
};

const int NB_NOTES = 8;
int notes[8];
int indiceCurrNote = 0;

////////// ===== JEU ===== //////////
Touche courant = NOTOUCH;
int joueur1 = 0;
int joueur2 = 0;
int gagne = 0;
int perdu = 0;
uint16_t posJeu = 0;
int seqLength = 0;
int menu = 1;
int unJoueur = 0;
int deuxJoueurs = 0;
int flag_lecture_touche = 0;
int flag_lecture_seq = 0;
int flag_jeu = 0;
int no_touch = 0;
#endif
