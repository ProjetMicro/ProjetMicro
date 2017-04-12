//===========================================================//
// Projet Micro - INFO1 - ENSSAT - S2 2017							 //
//===========================================================//
// File                : Programme de d�part
// Hardware Environment: Open1768	
// Build Environment   : Keil �Vision
//===========================================================//

#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_timer.h"
#include "touch\ili_lcd_general.h"
#include "touch\lcd_api.h"
#include "affichagelcd.h"
#include "touch\touch_panel.h"

#include "buzzer.h"
#include "memory.h"
#include "globaldec.h" // fichier contenant toutes les d�clarations de variables globales
#include <stdio.h>

void pin_configuration();


//===========================================================//
// Function: Main
//===========================================================//
int main(void)
{	  
	  int n; 
	
	  // Init(); // init variable globales et pinsel son et IR
	  lcd_Initializtion(); // init pinsel ecran et init LCD
		// affichage de l'�cran maitre
	  n=sprintf(chaine,"Entrez une sequence      ");
	  LCD_write_english_string (32,30,chaine,White,Blue);
	  dessiner_rect(10,60,110,110,2,1,Black,Yellow);
	  dessiner_rect(120,60,110,110,2,1,Black,Green);
	  dessiner_rect(10,170,110,110,2,1,Black,Blue);
	  dessiner_rect(120,170,110,110,2,1,Black,Red);
		
	  touch_init(); // init pinsel tactile et init tactile 
		pin_configuration();
	  
    while(1)  ; 
	// pour l'instant, le main fait juste quelques inits ...
	 
		
		
		
		
}

void pin_configuration()
{
	buzzer_port_init();
	memory_port_init();
}

//---------------------------------------------------------------------------------------------	
#ifdef  DEBUG
void check_failed(uint8_t *file, uint32_t line) {while(1);}
#endif