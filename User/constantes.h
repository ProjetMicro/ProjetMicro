#ifndef CONSTANTE_H
#define CONSTANTE_H

typedef enum {
		JAUNE,
		VERT,
		ROUGE,
		BLEU
} Touche;

// mettez dans ce fichier toutes les constantes et définitions 
// des nouveaux types que vous souhaitez

/* Les constantes des fréquences de base (en Hertz) */
#define DO		65 // Do normal
#define DOD 	69 // Do diese
#define RE 		74 // Re normal
#define RED 	78 // Re diese
#define MI 		83 // ...
#define FA 		87
#define FAD 	93
#define SO 		98
#define SOD 	104
#define LA 		110
#define LAD 	117
#define SI 		123

/* Frequence de la note associee a un bouton */
#define JAUNE_FREQU 	DON
#define VERT_FREQU 		REN
#define ROUGE_FREQU 	MIN
#define BLEU_FREQU 		FAN
	
/* precision souhaitee sur frequence pour oreil normal */
#endif
