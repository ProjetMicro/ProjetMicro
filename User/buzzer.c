#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_timer.h"

#include <stdio.h>
#include "buzzer.h"
#include "global.h"
#include <math.h>

/* Init */
void buzzer_init()
{
	// ===== port init ===== //
  PINSEL_CFG_Type speaker_init_cfg;	
	speaker_init_cfg.Funcnum = PINSEL_FUNC_0;	//AS GPIO
	speaker_init_cfg.OpenDrain = PINSEL_PINMODE_NORMAL;
	speaker_init_cfg.Pinmode = PINSEL_PINMODE_PULLUP;
	
	
	speaker_init_cfg.Pinnum = PINSEL_PIN_9;          
	speaker_init_cfg.Portnum = PINSEL_PORT_1; //P1.9 = speaker pin
  PINSEL_ConfigPin(&speaker_init_cfg);

	
	GPIO_SetDir (1,(1<<9),1);  // PORT1.9 defined as output   (port, pin, output)

  FIO_SetDir(1,(1<<9),1);
  FIO_SetValue(1,(1<<9));// ecrire 1 => P1.9


	// ===== timer init ===== //
	T0_Init();
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
	TIM_UpdateMatchValue(LPC_TIM0, 0, 10000);//match0 value to 50
	//start
	TIM_Cmd(LPC_TIM0, ENABLE);
}

void TIMER0_IRQHandler()
{
	signValue = !signValue;
	FIO_SetValue(1, (signValue<<9));

	//Acquittement
	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
}

int freqNote(int fb,int oc){
  return fb*pow(2,oc);
}