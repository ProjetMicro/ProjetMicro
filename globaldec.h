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
int n;

////////// ===== MEMORY ===== //////////
int complete_M;

////////// ===== BUZZER ===== //////////
int etatSon = 0;
int etatBuzzer = 0;
int us_periodSound = 0;
int us_noteDuration = 0;
int microSeconds = 0; // compter pour arriver � us_periodSound
int microSeconds2 = 0; // compter pour arriver � us_noteDuration

/* Frequence de la note associee a un bouton */
int frequTouches[NB_TOUCHE] = {
	DO, //Son touche JAUNE
	MI, //Son touche VERT
	SO, //Son touche ROUGE
	SI, //Son touche BLEU
};

////////// ===== JEU ===== //////////
Touche jeu[10];
int posJeu = 0;
int flag_jeu = 0;
#endif
