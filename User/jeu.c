#include <stdio.h>
#include "jeu.h"


void tache_clavier(void) {
		//On déclare une Touche t pour stocker l'appui
		Touche t;
	
		//Le flag appui clavier est à 1
		//On le reset
		flagtacheclavier = 0;
		
		//On met à jour les coordonnées
		touch_read();
		
		//On écrit les coords à l'écran (temp)
		n = sprintf(chaine, "Touch coords X:%u  Y:%u  ", touch_x, touch_y);
		LCD_write_english_string(10, 290, chaine, Black, White);
	
		t = get_touche();
		
		//Switch pour afficher (temp)
		switch (t)
		{
			case NOTOUCH:
				n = sprintf(chaine, "Rien   ");
				LCD_write_english_string(32, 30, chaine, Black, White);
				flagappuitactile = 0;
				break;
			
			case JAUNE:
				n = sprintf(chaine, "Jaune  ");
				LCD_write_english_string(32, 30, chaine, Black, Yellow);
				break;
			
			case VERT:
				n = sprintf(chaine, "Vert   ");
				LCD_write_english_string(32, 30, chaine, Black, Green);
				break;
			
			case ROUGE:
				n = sprintf(chaine, "Rouge  ");
				LCD_write_english_string(32, 30, chaine, Black, Red);
				break;
			
			case BLEU:
				n = sprintf(chaine, "Bleu   ");
				LCD_write_english_string(32, 30, chaine, Black, Blue);
				break;
			
			default:
				flagappuitactile = 0;
				break;
		}
	
		//Mise à jour du tableau de jeu
		if (flag_jeu == 0)
		{
				flag_jeu = 1;
				//Set pos of tab to 0
				posJeu = 0;
		}
		
		if (t != jeu[posJeu - 1] && t != NOTOUCH) {
				jeu[posJeu] = t;
				posJeu++;
		}
}

Touche get_touche(void)
{
		Touche t;
		
		if (touch_x >= 600 && touch_x <= 2000)
		{
				if (touch_y >= 2000 && touch_y <= 3200)
				{
						t = JAUNE;
				}
				else if(touch_y >= 800 && touch_y <= 2000)
				{
						t = BLEU;
				}
		}
		else if (touch_x >= 2100 && touch_x <= 3600)
		{
				if (touch_y >= 2000 && touch_y <= 3200)
				{
						t = VERT;
				}
				else if(touch_y >= 800 && touch_y <= 2000)
				{
						t = ROUGE;
				}
		}
		return t;
}
