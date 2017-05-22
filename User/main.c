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
//	i2c_eeprom_write(addr, testEcriture, 2);
//	i2c_eeprom_read(addr, testLecture, 2);
	
	while(1)
	{
		if (flagtacheclavier == 1) {
			tache_clavier();
		}
		if (flag_jeu == 1) {
			emettreSonTouche(jeu[posJeu - 1]);
		}
	}
}

void pin_configuration()
{
	lcd_init(); //Là ça marche plus
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
