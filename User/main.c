//===========================================================//
// Projet Micro - INFO1 - ENSSAT - S2 2017               //
//===========================================================//
// File                : Programme de départ
// Hardware Environment: Open1768  
// Build Environment   : Keil µVision
//===========================================================//

#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_timer.h"
#include "touch\touch_panel.h"

#include "buzzer.h"
#include "memory.h"
#include "lcd.h"
#include "globaldec.h" // fichier contenant toutes les déclarations de variables globales
#include "global.h"

#include <stdio.h>

void pin_configuration();

//===========================================================//
// Function: Main
//===========================================================//
int main(void)
{
		uint8_t testEcriture[] = {20,25};
		flagtacheclavier = 0;
    pin_configuration();
		i2c_eeprom_write(1, testEcriture, 2);
	
    while(1)
		{
			if (flagtacheclavier == 1) {
					print_coords();
			}
		}
  // pour l'instant, le main fait juste quelques inits ...
}

void pin_configuration()
{
  buzzer_init();
  memory_init();
	lcd_init();
	touch_init(); // init pinsel tactile et init tactile
	//Launch timer
	init_timer1();
	init_i2c_eeprom();
}

//---------------------------------------------------------------------------------------------  
#ifdef  DEBUG
void check_failed(uint8_t *file, uint32_t line) {while(1);}
#endif
