#include "lpc17xx_i2c.h"

/*
Fonction permettant de dessiner un rectangle de coordonnées (x,y)
de longueur lng, de largeur lrg, d'épaisseur de trait de bordure e,
plein ou vide, de couleur de bordure e_color et de fond bg_color
*/
void init_i2c_eeprom(void);
void i2c_eeprom_write(uint16_t, void*, int);
void i2c_eeprom_read(uint16_t, void*, int);
