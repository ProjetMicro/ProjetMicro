//===========================================================//
// Projet Micro - INFO1 - ENSSAT - S2 2017							 //
//===========================================================//
// File								: Programme de départ
// Hardware Environment: Open1768	
// Build Environment	 : Keil µVision
//===========================================================//

#include "touch\touch_panel.h"

#include "buzzer.h"
#include "memory.h"
#include "lcd.h"
#include "jeu.h"
#include "globaldec.h" // fichier contenant toutes les déclarations de variables globales

#include <stdio.h>

void pin_configuration(void);

//===========================================================//
// Function: Main
//===========================================================//
int main(void)
{
//	uint8_t testEcriture[] = {20,25};
//	uint8_t testLecture[2];
//	// Adresse de : la page | du mot
//	uint16_t addr = 0|(1<<8)|(1<<0);
	pin_configuration();
	
	
	while(1)
	{
		if(flagtacheclavier == 1)
		{
			if(menu == 1)
			{
				tache_clavier_menu();
			}
			else if(unJoueur == 1)
			{
				// tache_clavier_unJoueur(); A DEFINIR
				tache_clavier();
				if (!flagchange) {
					modifier_ecran(jeu[posJeu - 1]);
					flagchange = 1;
				}
			}
			else if(deuxJoueurs == 1)
			{
				// tache_clavier_deuxJoueurs(); A DEFINIR
				tache_clavier();
				if (!flagchange) {
					modifier_ecran(jeu[posJeu - 1]);
					flagchange = 1;
				}
			}
		}
		if(flagappuitactile)
		{
			emettreSonTouche(jeu[posJeu - 1]);
		}
		else
		{
			if(flagchange)
			{
				modifier_ecran(NOTOUCH);
				arreterSon();
				flagchange = 0;
			}
		}
	}
}

void pin_configuration()
{
	lcd_init();
	touch_init(); // init pinsel tactile et init tactile
	memory_init();
	buzzer_init();
	//Launch timer
	init_timer1();
	init_i2c_eeprom();
}

//---------------------------------------------------------------------------------------------	
#ifdef	DEBUG
void check_failed(uint8_t *file, uint32_t line) {while(1);}
#endif
