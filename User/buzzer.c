#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_timer.h"

#include <stdio.h>
#include <math.h>
#include "buzzer.h"
#include "global.h"

// ===== Fonctions d'initialisation ===== //
void buzzer_init()
{
	// ===== port init ===== //
  PINSEL_CFG_Type speaker_init_cfg;	

	speaker_init_cfg.Funcnum = PINSEL_FUNC_0;	//AS GPIO
	speaker_init_cfg.OpenDrain = PINSEL_PINMODE_NORMAL;
	//speaker_init_cfg.Pinmode = PINSEL_PINMODE_PULLUP;
	
	
	speaker_init_cfg.Pinnum = PINSEL_PIN_9;          
	speaker_init_cfg.Portnum = PINSEL_PORT_1; //P1.9 = speaker pin
  PINSEL_ConfigPin(&speaker_init_cfg);

  FIO_SetDir(1,(1<<9),1);
  FIO_SetValue(1,(1<<9));// ecrire 1 => P1.9

	T0_Init(); // timer init
	initNotes();
}

void T0_Init()
{
	TIM_TIMERCFG_Type timerConf;
	TIM_MATCHCFG_Type matchConf;

	timerConf.PrescaleOption = TIM_PRESCALE_USVAL; //prescale en microsecondes
	timerConf.PrescaleValue = 1; //precision de 1 us.

	matchConf.ResetOnMatch = ENABLE;
	matchConf.IntOnMatch = ENABLE;
	matchConf.ExtMatchOutputType = TIM_EXTMATCH_TOGGLE;

	NVIC_SetPriority(TIMER0_IRQn, ((0x01<<3)|0x01));
	NVIC_EnableIRQ(TIMER0_IRQn); //Enable interrupt for timer 0
	
	
	TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &timerConf); //TIMER0
	TIM_ConfigStructInit(TIM_TIMER_MODE, &timerConf);
	TIM_ConfigMatch(LPC_TIM0, &matchConf);
	TIM_UpdateMatchValue(LPC_TIM0, 0, 50);//match0 value to 50

	// lancer le timer
	TIM_Cmd(LPC_TIM0, ENABLE);
}

void initNotes()
{
	// initialiser une note a DO
	setMSPeriodeNote(DO);
	// initialiser la duree d'une note a 1 sec
	us_noteDuration = 1000000;
	
	/*notes[0] = DO;
	notes[1] = RE;
	notes[2] = MI;
	notes[3] = FA;
	notes[4] = SO;
	notes[5] = LA;
	notes[6] = SI;
	notes[7] = SI;*/
}

void initKey1()
{
	
}

////////// ===== Fonctions d'emmition du son ===== //////////
void emettreSonTouche(Touche touche)
{
	etatSon = 1;
	setMSPeriodeNote(frequTouches[touche]);
}

void demarerSon()
{
	etatSon = 1;
}

void arreterSon()
{
	etatSon = 0;
}

////////// ===== Fonctions d'interruption ===== //////////
void TIMER0_IRQHandler()
{
	microSeconds += 50;
	microSeconds2 += 50;

	/*if (microSeconds2 > 10000 *1000/50) {
		microSeconds2 = 0;
		indiceCurrNote++;
		if (indiceCurrNote >= NB_NOTES)
			indiceCurrNote = 0;
		setMSPeriodeNote(notes[indiceCurrNote]);
	}*/
	
	if (microSeconds2 > us_noteDuration) {
		etatSon = 0;
	}

	if (etatSon && microSeconds > us_periodSound / 2){
		microSeconds = 0;
		etatBuzzer = !etatBuzzer;

		if (etatBuzzer) {
			FIO_SetValue(1, (1<<9));
		} else {
			FIO_ClearValue(1, (1<<9));
		}
	}

	//Acquittement
	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
}

////////// ===== Fonctions de calcule ===== //////////

void setMSPeriodeNote(int frequ)
{
	us_periodSound = 1000000 / frequ;
}

int noteOctave(int frequ,int octave)
{
	return 1000000 / frequ;//(frequ * pow(2, octave));
}