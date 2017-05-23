#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_timer.h"
#include "global.h"

#ifndef BUZZER_H
#define BUZZER_H

// ===== Fonctions d'initialisation ===== //
void buzzer_init(void);
void T0_Init(void);
void initNotes(void);

// ===== Fonctions d'emmition du son ===== //
void emettreREetFAD();
void emettreSonTouche(Touche touche);
void demarerSon(void);
void arreterSon(void);

// ===== Fonctions de calcul ===== //
void setMSPeriodeNote(int frequ);

#endif
