#include <math.h>
#include <stdio.h>

#include "buzzer.h"

// ===== Fonctions d'initialisation ===== //
void buzzer_init(void)
{
	// ===== port init ===== //
  PINSEL_CFG_Type speaker_init_cfg;	

	speaker_init_cfg.Funcnum = PINSEL_FUNC_0;	//AS GPIO
	speaker_init_cfg.OpenDrain = PINSEL_PINMODE_NORMAL;
	
	
	speaker_init_cfg.Pinnum = PINSEL_PIN_9;          
	speaker_init_cfg.Portnum = PINSEL_PORT_1; //P1.9 = speaker pin
  PINSEL_ConfigPin(&speaker_init_cfg);

  FIO_SetDir(1,(1<<9),1);
  FIO_SetValue(1,(1<<9));// ecrire 1 => P1.9

	T0_Init(); // timer init
	initNotes();
}

void T0_Init(void)
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

void initNotes(void)
{
	// initialiser une note a DO
	setMSPeriodeNote(DO);
	// initialiser la duree d'une note a 1 sec
	us_noteDuration = 1000000;
	// initialiser la periode d'une double note a 50 ms
	us_periodDoubleNote = 5000;
}

////////// ===== Fonctions d'emmition du son ===== //////////
void emettreREetFAD()
{
	doubleNoteOn = 1;
	setMSPeriodeNote(RE);
	demarerSon();
}

void demoNotes()
{
	int notes[50][2] = {
		DO, 100,
		DO, 100,
		DO, 100,
		SOD, 75,
		RED, 25,
		DO, 100,
		SOD, 75,
		RED, 25,
		DO, 200,
		SO, 100,
		SO, 100,
		SO, 100,
		SOD, 75,
		RED, 25,
		SI, 100,
		SOD, 75,
		RED, 25,
		DO, 200,
		DO, 100,
		DO, 100,
		DO, 25,
		SI, 25,
		DO, 25,
		NOSOUND, 75,
		SI, 50,
		LAD, 100,
		LAD, 100,
		SO, 25,
		FAD, 25,
		SO, 25,
		NOSOUND, 75,
		FAD, 50,
		FA, 100,
		SO, 100,
		LAD, 100,
		SO, 75,
		RED, 25,
		DO, 100,
		SOD, 75,
		RED, 25,
		DO, 200,
		-2 // code d'arret, ne pas oublier de l'ajouter dans le tableau de note
	};
	emettreMusique(musique);
}

void emettreMusique(int notes[NB_NOTES_MAX][2])
{
	int i = 0;
	do {
		musique[i][0] = notes[i][0];
		musique[i][1] = notes[i][1];
	} while (notes[i][0] == -2);

	modeMusique = 1;
	indiceCurrNote = 0;
}

void emettreSonTouche(Touche touche)
{
	etatSon = 1;
	if (touche != NOTOUCH) setMSPeriodeNote(frequTouches[touche - 1]);
}

void demarerSon(void)
{
	etatSon = 1;
}

void arreterSon(void)
{
	etatSon = 0;
}

////////// ===== Fonctions d'interruption ===== //////////
void TIMER0_IRQHandler()
{
	microSeconds += 50;
	microSeconds2 += 50;
	microSeconds3 += 50;
	microSecondsMusique += 50;

	if (modeMusique && microSecondsMusique > musique[indiceCurrNote][1] * 1000)
	{
		microSecondsMusique = 0;
		setMSPeriodeNote(musique[indiceCurrNote][0]);
		indiceCurrNote++;

		if (musique[indiceCurrNote][0] == -2) //si fin du tableau
			modeMusique = 0; // on stop la musique
	}
	
	if (doubleNoteOn && microSeconds3 > us_periodDoubleNote / 2) { //alternation des 2 notes (mode doubleNote)
		microSeconds3 = 0;
		if (us_periodSound == 1000000 / RE) { // note RE
			setMSPeriodeNote(FAD);
		} else {
			setMSPeriodeNote(RE);
		}
	}
	
	if (microSeconds2 > us_noteDuration) { // fin de la note
		etatSon = 0;
		microSeconds2 = 0;
	}

	//inversion de l'état du haut-parleur à chaque demi périodes
	if (etatSon && us_periodSound >= 0 && microSeconds > us_periodSound / 2) {
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

////////// ===== Fonctions de calcul ===== //////////

void setMSPeriodeNote(int frequ)
{
	us_periodSound = 1000000 / frequ;
}

