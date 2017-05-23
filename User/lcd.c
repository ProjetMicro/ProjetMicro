#include <stdio.h>

#include "lcd.h"


//LCD Init
void lcd_init_menu(void)
{
		// affichage de l'écran menu
		lcd_clear(White);
		LCD_write_english_string(100, 90, "Simon", Black, White);
		dessiner_rect(10, 170, 110, 110, 1, 1, Black, Green);
		LCD_write_english_string(30, 215, "1 joueur", Black, Green);
		dessiner_rect(120, 170, 110, 110, 1, 1, Black, Red);
		LCD_write_english_string(140, 215, "2 joueurs", Black, Red);
}

//LCD Init
void lcd_init_deuxJoueurs(void)
{
		// affichage de l'écran de jeu
		n = sprintf(chaine, "J1 : Entrez une sequence");
		lcd_clear(White);
		LCD_write_english_string(32, 15, chaine, Black, White);
		dessiner_rect_yellow(1);
		dessiner_rect_green(1);
		dessiner_rect_red(1);
		dessiner_rect_blue(1);
		deuxJoueurs = 1;
}

//LCD Init
void lcd_init_fin(char res)
{
	menu = 1;
	lcd_init_menu();
	if(res) n = sprintf(chaine, "C'est gagne, rejouez !");
	else n = sprintf(chaine, "C'est perdu, rejouez !");
	LCD_write_english_string(32, 15, chaine, Black, White);
	joueur2 = 0;
	gagne = 0;
	unJoueur = 0;
	deuxJoueurs = 0;
	//TODO bouton retour menu
}

void modifier_ecran(Touche t, char sombre) {
	switch (t) {
			case JAUNE:
				dessiner_rect_yellow(sombre);
				break;
			
			case VERT:
				dessiner_rect_green(sombre);
				break;
			
			case ROUGE:
				dessiner_rect_red(sombre);
				break;
			
			case BLEU:
				dessiner_rect_blue(sombre);
				break;
			
			default:
				dessiner_rect_yellow(1);
				dessiner_rect_green(1);
				dessiner_rect_red(1);
				dessiner_rect_blue(1);
				break;
	}
}

void dessiner_rect_yellow(char sombre) {
	if (sombre)	dessiner_rect(10, 60, 110, 110, 1, 1, Black, Yellow);
	else dessiner_rect(10, 60, 110, 110, 1, 1, Black, Black);
}

void dessiner_rect_green(char sombre) {
	if (sombre) dessiner_rect(120, 60, 110, 110, 1, 1, Black, Green);
	else dessiner_rect(120, 60, 110, 110, 1, 1, Black, Black);
}

void dessiner_rect_blue(char sombre) {
	if (sombre) dessiner_rect(10, 170, 110, 110, 1, 1, Black, Blue);
	else dessiner_rect(10, 170, 110, 110, 1, 1, Black, Black);
}

void dessiner_rect_red(char sombre) {
	if (sombre) dessiner_rect(120, 170, 110, 110, 1, 1, Black, Red);
	else dessiner_rect(120, 170, 110, 110, 1, 1, Black, Black);
}

//Timer interruption
void TIMER1_IRQHandler(void)
{
		int value = 0;
		uint32_t status = 0;
		if (TIM_GetIntStatus(LPC_TIM1, TIM_MR0_INT))
		{
				TIM_ClearIntPending(LPC_TIM1, TIM_MR0_INT);
				//Get status of P0.19
				status = GPIO_ReadValue(0);
				value = (status >> 19) & 1;
				flagtacheclavier = !value;
				if (flagappuitactile){
						flagappuitactile = flagtacheclavier;
				}
				if (flagrepetitiontouche) {
					flagrepetitiontouche = flagtacheclavier;
				}
		}	
}

void init_timer1(void)
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
		matchConf.MatchValue = 5;
		
		//Init timer
		TIM_Init(LPC_TIM1, TIM_TIMER_MODE, &timerConf);
		//Init match
		TIM_ConfigMatch(LPC_TIM1, &matchConf);
		
		//Reset timer (in case of)
		TIM_ResetCounter(LPC_TIM1);
		
		//Set-up interruptions
		/* preemption = 1, sub-priority = 1 */
		NVIC_SetPriority(TIMER1_IRQn, ((0x01<<3)|0x01));
		/* Enable interrupt for timer 1 */
		NVIC_EnableIRQ(TIMER1_IRQn);
		
		//Start timer
		TIM_Cmd(LPC_TIM1, ENABLE);
}
