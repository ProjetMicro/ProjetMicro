#ifndef BUZZER_H
#define BUZZER_H

#include "constantes.h"

// ===== Fonctions d'initialisation ===== //
void buzzer_init();
void T0_Init();
void initNotes();
void initKey1();

// ===== Fonctions d'emmition du son ===== //
int emettreSonTouche(Touche touche);
int demarerSon(int frequence);
int arreterSon();

// ===== Fonctions de calcule ===== //
void setMSPeriodeNote(int frequ);
int freqNoteOctave(int frequ,int octave);

#endif