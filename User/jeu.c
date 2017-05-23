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
	
		t = get_touche();
	
		if(t == NOTOUCH)
		{
			flagappuitactile = 0;
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

void tache_clavier_menu(void)
{
		//On déclare une Touche t pour stocker l'appui
		int t;
	
		//Le flag appui clavier est à 1
		//On le reset
		flagtacheclavier = 0;
		
		//On met à jour les coordonnées
		touch_read();
	
		t = get_touche();
	
		flagappuitactile = 0;
		
		// Switch permettant de lancer le mode 1 joueur ou 2 joueurs
		switch (t)
		{
			case 1:
				//menu = 0;
				//unJoueur = 1;
				//lcd_init();
				break;
			
			case 2:
				menu = 0;
				lcd_init_deuxJoueurs();
				break;
			
			default:
				break;
		}
}

int get_touche_menu(void)
{
		int t;
		
		if(touch_y >= 800 && touch_y <= 2000)
		{
				if(touch_x >= 600 && touch_x <= 2000)
				{
						t = 1;
				}else if(touch_x >= 2100 && touch_x <= 3600)
				{
						t = 2;
				}
		}else{
			t = 0;
		}
		return t;
}
