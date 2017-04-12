#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_timer.h"

#include <stdio.h>
#include "memory.h"
#include "global.h"

/* Init */
void memory_init()
{
	// ===== port init ===== //
	PINSEL_CFG_Type memory_SDA0_init_cfg;
	PINSEL_CFG_Type memory_SCL0_init_cfg;
	
	memory_SDA0_init_cfg.Funcnum = PINSEL_FUNC_1;	//AS SDA0
	memory_SDA0_init_cfg.OpenDrain = PINSEL_PINMODE_NORMAL;
	
	
	memory_SDA0_init_cfg.Pinnum = PINSEL_PIN_27;
	memory_SDA0_init_cfg.Portnum = PINSEL_PORT_0; //P0.27 = memory
  PINSEL_ConfigPin(&memory_SDA0_init_cfg);
	
	
	memory_SCL0_init_cfg.Funcnum = PINSEL_FUNC_1;	//AS SCL0
	memory_SCL0_init_cfg.OpenDrain = PINSEL_PINMODE_NORMAL;
	
	memory_SCL0_init_cfg.Pinnum = PINSEL_PIN_28;
	memory_SCL0_init_cfg.Portnum = PINSEL_PORT_0; //P0.28 = memory
  PINSEL_ConfigPin(&memory_SCL0_init_cfg);
}

