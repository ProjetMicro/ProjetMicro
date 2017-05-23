#include "lpc17xx_gpio.h"
#include "lpc17xx_timer.h"
#include "affichagelcd.h"
#include "touch\ili_lcd_general.h"
#include "touch\lcd_api.h"

#include "global.h"

#ifndef LCD_H
#define LCD_H

void lcd_init(void);
void modifier_ecran(Touche);
void dessiner_rect_yellow(char);
void dessiner_rect_green(char);
void dessiner_rect_blue(char);
void dessiner_rect_red(char);
void TIMER1_IRQHandler(void);
void init_timer1(void);
void start_timer1(void);
void tache_clavier(void);
Touche get_touche(void);
#endif
