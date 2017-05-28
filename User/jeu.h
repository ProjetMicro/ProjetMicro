#include "touch\ili_lcd_general.h"
#include "touch\lcd_api.h"
#include "touch\touch_panel.h"

#include "global.h"
#include "lcd.h"

#ifndef JEU_H
#define JEU_H
void TIMER2_IRQHandler(void);
void init_timer_jeu(void);
void joueurUn(void);
void joueurDeux(void);
void fin(void);
void tache_clavier(void);
Touche get_touche(void);
void tache_clavier_menu(void);
int get_touche_menu(void);
#endif
