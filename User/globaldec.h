#include "constantes.h" // fichier contenant toutes les constantes du projet
#include <stdint.h>
#include "lpc17xx_i2c.h" //Aucunne utilitée pour le moment, laisser au cas où

#ifndef GLOBALDEC_H
#define GLOBALDEC_H
// mettez ici toutes les déclarations de variables globales
////////// ===== AFFICHAGE ===== //////////
// buffer pour l'affichage sur le LCD
char chaine[30];
uint16_t touch_x, touch_y;
int flagtacheclavier = 0;
int flagappuitactile = 0;
int n;

////////// ===== MEMORY ===== //////////
int complete_M;

////////// ===== BUZZER ===== //////////
int modeMusique = 0;
int doubleNoteOn = 0;
int etatSon = 0;
int etatBuzzer = 0;

int us_periodSound = 0;
int us_periodDoubleNote = 0;
int us_noteDuration = 0;

int microSeconds = 0;
int microSeconds2 = 0;
int microSeconds3 = 0;
int microSecondsMusique = 0;

int musique[NB_NOTES_MAX][2];
int indiceCurrNote = 0;

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
int flagchange = 0;
int menu = 1;
int unJoueur = 0;
int deuxJoueurs = 0;
int flag_jeu = 0;
int no_touch = 0;
#endif
