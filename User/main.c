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
#include <string.h>

void pin_configuration(void);

//===========================================================//
// Function: Main
//===========================================================//
int main(void)
{
	pin_configuration();
	
	while(1)
	{
		if(menu)
		{
			if(flagtacheclavier)
			{
				tache_clavier_menu();
			}
		}
		else if(unJoueur)
		{
			if(flagtacheclavier)
			{
				tache_clavier();
				if(flagappuitactile && !flagchangecouleur)
				{
					modifier_ecran(courant, 0);
					flagchangecouleur = 1;
				}
			}
			else if(gagne)
			{
				joueur2 = 0;
				fin_seq_unJoueur();
				gagne = 0;
			}
			else if(perdu)
			{
				lcd_init_fin(2);
				fin();
			}
		}
		else if(deuxJoueurs)
		{
			if(flagtacheclavier)
			{
				tache_clavier();
				if(flagappuitactile && !flagchangecouleur)
				{
					modifier_ecran(courant, 0);
					flagchangecouleur = 1;
				}
			}
			else if(gagne)
			{
				fin();
				lcd_init_fin(1);
			}
			else if(perdu)
			{
				fin();
				lcd_init_fin(0);
			}
			else if(no_touch)
			{
				no_touch = 0;
				LCD_write_english_string(32, 15, "J2 : Repetez la sequence", Black, White);
				joueur1 = 0;
				joueur2 = 1;
				seqLength = posJeu;
				posJeu = 0;
			}
		}
		if(unJoueur || deuxJoueurs)
		{
			if(flagappuitactile)
			{
				emettreSonTouche(courant);
			}
			else
			{
				if(flagchangecouleur)
				{
					modifier_ecran(courant, 1);
					arreterSon();
					flagchangecouleur = 0;
				}
			}
		}
	}
}

void pin_configuration()
{
	lcd_Initializtion();
	lcd_init_menu();
	touch_init(); // init pinsel tactile et init tactile
	memory_init();
	buzzer_init();
	//Launch timer
	init_timer1();
}

//---------------------------------------------------------------------------------------------	
#ifdef	DEBUG
void check_failed(uint8_t *file, uint32_t line) {while(1);}
#endif
