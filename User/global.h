#include "constantes.h" // fichier contenant toutes les constantes du projet
#include <stdint.h>

#ifndef GLOBAL_H
#define GLOBAL_H

// mettez ici toutes les "extern" correspondant aux déclarations contenues dans globadec.h

extern char chaine[30]; // buffer pour l'affichage sur le LCD
extern uint16_t touch_x, touch_y;
extern int flagtacheclavier;
extern int n;
#endif
