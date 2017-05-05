#include "lpc17xx_gpio.h"
#include "lpc17xx_timer.h"
#include "touch\ili_lcd_general.h"
#include "touch\lcd_api.h"
#include "affichagelcd.h"
#include "touch\touch_panel.h"

#include <stdio.h>
#include "lcd.h"
#include "global.h"

//LCD Init
void lcd_init(void) {
    int n;
    lcd_Initializtion(); // init pinsel ecran et init LCD
    // affichage de l'écran maitre
    n = sprintf(chaine, "Entrez une sequence");
    lcd_clear(White);
    LCD_write_english_string(32, 15, chaine, Black, White);
    dessiner_rect(10, 60, 110, 110, 2, 1, Black, Yellow);
    dessiner_rect(120, 60, 110, 110, 2, 1, Black, Green);
    dessiner_rect(10, 170, 110, 110, 2, 1, Black, Blue);
    dessiner_rect(120, 170, 110, 110, 2, 1, Black, Red);
}

//Timer interruption
void TIMER1_IRQHandler(void) {
    int value = 0;
    uint32_t status = 0;
    if (TIM_GetIntStatus(LPC_TIM1, TIM_MR0_INT))
    {
        TIM_ClearIntPending(LPC_TIM1, TIM_MR0_INT);
        //Get status of P0.19
        status = GPIO_ReadValue(0);
        value = (status >> 19) & 1;
        flagtacheclavier = !value;
        //flagtacheclavier = 1;
    }  
}

void init_timer1(void) {
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

void print_coords(void) {
    int n;
    //Read touch coords
    touch_read();
    n = sprintf(chaine, "Touch coords X:%u Y:%u", touch_x, touch_y);
    LCD_write_english_string(10, 290, chaine, Black, White);
    
    if (touch_x >= 600 && touch_x <= 2000) {
        if (touch_y >= 2000 && touch_y <= 3000) {
          n = sprintf(chaine, "Jaune");
        } else if(touch_y >= 700 && touch_y <= 1800) {
          n = sprintf(chaine, "Bleu  ");
        }
    } else if (touch_x >= 2100 && touch_x <= 3600) {
      if (touch_y >= 2000 && touch_y <= 3000) {
        n = sprintf(chaine, "Vert  ");
        } else if(touch_y >= 700 && touch_y <= 1800) {
          n = sprintf(chaine, "Rouge");
        }
    }
		LCD_write_english_string(32, 30, chaine, Black, White);
    //reset flag
    flagtacheclavier = 0;
}