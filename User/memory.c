#include "memory.h"
#include "global.h"

#include <string.h>

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


void init_i2c_eeprom(){
	// POWER déjà actif par défaut
	I2C_Init(LPC_I2C0, 1000000);
	// Active l'I2C
	I2C_Cmd(LPC_I2C0, ENABLE);
}

void i2c_eeprom_write(uint16_t addr, void* data, int length){
	// mise en place de la structure de configuration de transfert
	I2C_M_SETUP_Type transfer;
	// Tdata contient l'adresse du mot où il faut écrire et les mots à écrire
	uint8_t Tdata[256];
	Tdata[0] = (uint8_t) (addr & 0xFF);
	memcpy(&Tdata[1], data, sizeof(data));
	// length + 1 pour la transmission de l'adresse du mot
	length = length + 1;
	transfer.sl_addr7bit = 0|(1<<6)|(1<<4)|(addr>>8);
	transfer.tx_data = Tdata;
	transfer.tx_length = length;
	transfer.rx_data = NULL;
	transfer.rx_length = 0;
	transfer.retransmissions_max = 1;
	transfer.callback = I2C0_IRQHandler;
	// appel de la fonction qui permet l'écriture/lecture dans la mémoire
	complete_M = 0;
	I2C_MasterTransferData(LPC_I2C0, &transfer, I2C_TRANSFER_INTERRUPT);
}

void i2c_eeprom_read(uint16_t addr, void* data, int length){
	// mise en place de la structure de configuration de lecture
	I2C_M_SETUP_Type receive;
	// Tdata contient l'adresse du mot où il faut lire
	uint8_t Tdata[1];
	Tdata[0] = (uint8_t) (addr & 0xFF);
	receive.sl_addr7bit = 0|(1<<6)|(1<<4)|(addr>>8);
	// tx_data et tx_length utilisés pour faire une sélection du mot à lire (écriture vide)
	receive.tx_data = Tdata;
	receive.tx_length = 1;
	receive.rx_data = data;
	receive.rx_length = length;
	receive.retransmissions_max = 1;
	receive.callback = I2C0_IRQHandler;
	// appel de la fonction qui permet l'écriture/lecture dans la mémoire
	complete_M = 0;
	I2C_MasterTransferData(LPC_I2C0, &receive, I2C_TRANSFER_INTERRUPT);
}

void I2C0_IRQHandler(void){
	while(complete_M != 1){
		I2C_MasterHandler(LPC_I2C0);
		if(I2C_MasterTransferComplete(LPC_I2C0)){
			complete_M = 1;
		}
	}
}
