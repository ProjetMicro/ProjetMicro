#ifndef CONSTANTES_H
#define CONSTANTES_H

typedef enum {jaune,vert,rouge,bleu} touche ;

// mettez dans ce fichier toutes les constantes et définitions 
// des nouveaux types que vous souhaitez

/* Les constantes des fréquences de base (en Hertz) */
const char DON = 65; // Do normal
const char DOD = 69; // Do diese
const char REN = 74; // Re normal
const char RED = 78; // Re diese
const char MIN = 83; // ...
const char FAN = 87;
const char FAD = 93;
const char SON = 98;
const char SOD = 104;
const char LAN = 110;
const char LAD = 117;
const char SIN = 123;

/* Frequence de la note associee a un bouton */
	const char JAUNE_FREQU = DON;
	const char VERT_FREQU = REN;
	const char ROUGE_FREQU = MIN;
	const char BLEU_FREQU = FAN;
	
/* precision souhaitee sur frequence pour oreil normal */

#endif