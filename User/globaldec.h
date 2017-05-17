#ifndef GLOBALDEC_H
#define GLOBALDEC_H

#include "constantes.h" // fichier contenant toutes les constantes du projet
#include <stdint.h>
#include "lpc17xx_i2c.h"

// mettez ici toutes les déclarations de variables globales

////////// ===== AFFICHAGE ===== //////////
char chaine[30]; // buffer pour l'affichage sur le LCD
uint16_t touch_x, touch_y ;

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

#endif