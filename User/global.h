#include <stdint.h>
#include "constantes.h"

// mettez ici toutes les "extern" correspondant aux déclarations contenues dans globadec.h

////////// ===== AFFICHAGE ===== //////////
extern char chaine[30]; // buffer pour l'affichage sur le LCD
extern uint8_t touch_x, touch_y;

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

	
/* precision souhaitee sur frequence pour oreil normal */