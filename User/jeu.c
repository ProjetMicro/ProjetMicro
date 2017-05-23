#include <stdio.h>
#include "jeu.h"


//Timer interruption
void TIMER2_IRQHandler(void)
{
		if (TIM_GetIntStatus(LPC_TIM2, TIM_MR0_INT))
		{
				TIM_ClearIntPending(LPC_TIM2, TIM_MR0_INT);
				no_touch = 1;
		}	
}

void init_timer_jeu(void)
{
	TIM_TIMERCFG_Type timerConf;
	TIM_MATCHCFG_Type matchConf;
	
		//Set up timer for LCD
		timerConf.PrescaleOption = TIM_PRESCALE_USVAL;
		//Precision 20ms
		timerConf.PrescaleValue = 20000;
		
		matchConf.MatchChannel = 0;
		matchConf.IntOnMatch = ENABLE;
		matchConf.ResetOnMatch = ENABLE;
		matchConf.StopOnMatch = DISABLE;
		matchConf.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
		matchConf.MatchValue = 200;
		
		//Init timer
		TIM_Init(LPC_TIM2, TIM_TIMER_MODE, &timerConf);
		//Init match
		TIM_ConfigMatch(LPC_TIM2, &matchConf);
		
		//Reset timer (in case of)
		TIM_ResetCounter(LPC_TIM2);
		
		//Set-up interruptions
		/* preemption = 1, sub-priority = 1 */
		NVIC_SetPriority(TIMER1_IRQn, ((0x01<<3)|0x01));
		/* Enable interrupt for timer 2 */
		NVIC_EnableIRQ(TIMER2_IRQn);
		
		//Start timer
		TIM_Cmd(LPC_TIM2, ENABLE);
}

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
