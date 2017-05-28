#include <stdint.h>
#ifndef CONSTANTE_H
#define CONSTANTE_H

// mettez dans ce fichier toutes les constantes et définitions 
// des nouveaux types que vous souhaitez

typedef enum {
		NOTOUCH,
		JAUNE,
		VERT,
		ROUGE,
		BLEU
} Touche;

#define NB_TOUCHE 4

/* Les constantes des fréquences de base (en Hertz) */
#define DO 262 // Do normal
#define DOD 277 // Do diese
#define RE 294  // Re normal
#define RED 311  // Re diese
#define MI 330  // ...
#define FA 349
#define FAD 370
#define SO 392
#define SOD 415
#define LA 440
#define LAD 466
#define SI 494

/* precision souhaitee sur frequence pour oreil normal */
#endif
