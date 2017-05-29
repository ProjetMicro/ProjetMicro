#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jeu.h"
#include "memory.h"
#include "buzzer.h"

//Timer interruption
void TIMER2_IRQHandler()
{
		if (TIM_GetIntStatus(LPC_TIM2, TIM_MR0_INT))
		{
				TIM_ClearIntPending(LPC_TIM2, TIM_MR0_INT);
				if(unJoueur)
				{
					if(flag_lecture_seq) flag_lecture_seq = 0;
					if(flag_lecture_touche) flag_lecture_touche = 0;
				}
				else if(deuxJoueurs){
					no_touch = 1;
					TIM_Cmd(LPC_TIM2, DISABLE);
				}
		}
}

void init_timer_unJoueur()
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
		matchConf.MatchValue = 50;
		
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

void init_timer_deuxJoueurs()
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
		matchConf.MatchValue = 125;
		
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

void init_jeu_unJoueur()
{
	int i;
	uint16_t addr;
	uint8_t seq[1];
	for(i=0;i<254;i++){
		addr = 0|(1<<8)|i;
		seq[0] = (rand()%4) + 1;
		i2c_eeprom_write(addr, seq, 1);
	}
	seqLength = 4;
	lecture_seq();
}

void lecture_seq()
{
	uint16_t i;
	init_timer_unJoueur();
	for(i=0;i<seqLength;i++){
		lecture_touche(i);
	}
	TIM_Cmd(LPC_TIM2, DISABLE);
	n = sprintf(chaine, "Repetez la sequence     ");
	LCD_write_english_string(32, 15, chaine, Black, White);
	joueur2 = 1;
}

void lecture_touche(uint16_t i)
{
	uint16_t addr = 0|(1<<8)|i;
	uint8_t t[1];
	Touche touche;
	flag_lecture_touche = 1;
	i2c_eeprom_read(addr, t, 1);
	TIM_ResetCounter(LPC_TIM2);
	touche = (Touche) t[0];
	modifier_ecran(touche, 0);
	while(flag_lecture_touche)
	{
		emettreSonTouche(touche);
	}
	modifier_ecran(touche, 1);
	arreterSon();
}

void fin_seq_unJoueur()
{
	seqLength++;
	modifier_ecran(courant, 1);
	if(seqLength==254)
	{
		lcd_init_fin(3);
		fin();
	}
	else
	{
		posJeu = 0;
		n = sprintf(chaine, "Bravo !              ");
		LCD_write_english_string(32, 15, chaine, Black, White);
		flag_lecture_seq = 1;
		init_timer_unJoueur();
		while(flag_lecture_seq);
		TIM_Cmd(LPC_TIM2, DISABLE);
		n = sprintf(chaine, "Memorisez la sequence");
		LCD_write_english_string(32, 15, chaine, Black, White);
		lecture_seq();
	}
}

void joueurUn()
{
	uint16_t addr = 0|(1<<8);
	uint8_t data[1];
	if(flag_jeu == 0)
	{
		init_timer_deuxJoueurs();
		flag_jeu = 1;
		//Set pos of tab to 0
		posJeu = 0;
	}
	addr |= posJeu;
	data[0] = courant;
	if(!flagrepetitiontouche)
	{
		i2c_eeprom_write(addr, data, 1);
		posJeu++;
		flagrepetitiontouche = 1;
	}
}

void joueurDeux()
{
	uint8_t t[1];
	uint16_t addr = 0|(1<<8)|(posJeu);
	if(!flagrepetitiontouche)
	{
		i2c_eeprom_read(addr, t, 1);
		posJeu++;
		flagrepetitiontouche = 1;
		if(courant != t[0])
		{
			perdu = 1;
		}
		else if(posJeu == seqLength)
		{
			gagne = 1;
		}
	}
}

void fin()
{
	flag_jeu = 0;
	seqLength = 0;
	posJeu = 0;
	joueur1 = 0;
	joueur2 = 0;
	gagne = 0;
	perdu = 0;
	unJoueur = 0;
	deuxJoueurs = 0;
}

void tache_clavier()
{
		//Le flag appui clavier est à 1
		//On le reset
		flagtacheclavier = 0;
		
		//On met à jour les coordonnées
		touch_read();
	
		if (!flagrepetitiontouche) courant = get_touche();
	
		if(courant != NOTOUCH)
		{
			flagappuitactile = 1;
		}else{
			flagappuitactile = 0;
		}
	
		// test taille séquence + joueur qui joue => pour le reset du timer
		if(posJeu < 255 && courant != NOTOUCH)
		{
				if(joueur1)
				{
					joueurUn();
					TIM_ResetCounter(LPC_TIM2);
				}
				else if(joueur2)
				{
					joueurDeux();
				}
		}
}

Touche get_touche()
{
		Touche t = NOTOUCH;
		
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
		}else{
			t = NOTOUCH;
		}
		
		return t;
}

void tache_clavier_menu()
{
		//On déclare une Touche t pour stocker l'appui
		int t;
	
		//Le flag appui clavier est à 1
		//On le reset
		flagtacheclavier = 0;
		
		//On met à jour les coordonnées
		touch_read();
	
		t = get_touche_menu();
	
		flagappuitactile = 0;
		
		// Switch permettant de lancer le mode 1 joueur ou 2 joueurs
		switch (t)
		{
			case 1:
				menu = 0;
				unJoueur = 1;
				lcd_init_unJoueur();
				init_jeu_unJoueur();
				break;
			
			case 2:
				menu = 0;
				joueur1 = 1;
				deuxJoueurs = 1;
				lcd_init_deuxJoueurs();
				break;
			
			default:
				break;
		}
}

int get_touche_menu()
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
