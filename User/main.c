//===========================================================//
// Projet Micro - INFO1 - ENSSAT - S2 2017							 //
//===========================================================//
// File                : Programme de départ
// Hardware Environment: Open1768	
// Build Environment   : Keil µVision
//===========================================================//

#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_timer.h"
#include "touch\ili_lcd_general.h"
#include "touch\lcd_api.h"
#include "affichagelcd.h"
#include "touch\touch_panel.h"


#include "globaldec.h" // fichier contenant toutes les déclarations de variables globales
#include <stdio.h>

void spi_init();
void pin_Configuration();


//===========================================================//
// Function: Main
//===========================================================//
int main(void)
{	  
	  int n; 
	
	  // Init(); // init variable globales et pinsel son et IR
	  lcd_Initializtion(); // init pinsel ecran et init LCD
		// affichage de l'écran maitre
	  n=sprintf(chaine,"Entrez une sequence      ");
	  LCD_write_english_string (32,30,chaine,White,Blue);
	  dessiner_rect(10,60,110,110,2,1,Black,Yellow);
	  dessiner_rect(120,60,110,110,2,1,Black,Green);
	  dessiner_rect(10,170,110,110,2,1,Black,Blue);
	  dessiner_rect(120,170,110,110,2,1,Black,Red);
		
	  touch_init(); // init pinsel tactile et init tactile 
		pin_Configuration();
	  
    while(1)  ; 
	// pour l'instant, le main fait juste quelques inits ...
	 
		
		
		
		
}

void pin_Configuration()
{
	/*
	 * Initialize pin connect
	 */
  PINSEL_CFG_Type speaker_init_cfg;
	PINSEL_CFG_Type memory_init_cfg;
	PINSEL_CFG_Type memory_init_cfg2;
	
	
	///// SPEAKER /////
	speaker_init_cfg.Funcnum = PINSEL_FUNC_0;	//AS GPIO
	speaker_init_cfg.OpenDrain = PINSEL_PINMODE_NORMAL;
	speaker_init_cfg.Pinmode = PINSEL_PINMODE_PULLUP;
	
	
	speaker_init_cfg.Pinnum = PINSEL_PIN_9;          
	speaker_init_cfg.Portnum = PINSEL_PORT_1; //P1.9 = speaker pin
  PINSEL_ConfigPin(&speaker_init_cfg);

	
	GPIO_SetDir (1,(1<<9),1);  // PORT1.9 defined as output   (port, pin, output)

  FIO_SetDir(1,(1<<9),1);
  FIO_SetValue(1,(1<<9));// ecrire 1 => P1.9
	
	
	///// MEMORY /////
	memory_init_cfg.Funcnum = PINSEL_FUNC_1;	//AS GPIO
	memory_init_cfg.OpenDrain = PINSEL_PINMODE_NORMAL;
	memory_init_cfg.Pinmode = PINSEL_PINMODE_PULLUP;
	
	
	memory_init_cfg.Pinnum = PINSEL_PIN_27;
	memory_init_cfg.Portnum = PINSEL_PORT_0; //P0.27 = memory
  PINSEL_ConfigPin(&memory_init_cfg);
	
	
	memory_init_cfg2.Funcnum = PINSEL_FUNC_1;	//AS GPIO
	memory_init_cfg2.OpenDrain = PINSEL_PINMODE_NORMAL;
	memory_init_cfg2.Pinmode = PINSEL_PINMODE_PULLUP;
	
	memory_init_cfg2.Pinnum = PINSEL_PIN_28;
	memory_init_cfg2.Portnum = PINSEL_PORT_0; //P0.28 = memory
  PINSEL_ConfigPin(&memory_init_cfg2);
}

//---------------------------------------------------------------------------------------------	
#ifdef  DEBUG
void check_failed(uint8_t *file, uint32_t line) {while(1);}
#endif
