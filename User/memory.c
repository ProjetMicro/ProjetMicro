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
	I2C_Cmd(LPC_I2C0, ENABLE);
}

void i2c_eeprom_write(uint16_t addr, void* data, int length){
	Status res;
	// mise en place de la structure de configuration de transfert
	I2C_M_SETUP_Type transfer;
	// Tdata contient l'adresse du mot où il faut écrire et les mots à écrire
	uint8_t Tdata[256];
	Tdata[0] = (uint8_t) addr;
	memcpy(&Tdata[1], data, sizeof(data));
	// length + 1 pour la transmission de l'adresse du mot
	length = length + 1;
	transfer.sl_addr7bit = 0 | (1<<6)|(1<<4)|(1<<0);
	transfer.tx_data = Tdata;
	transfer.tx_length = length;
	transfer.rx_data = NULL;
	transfer.rx_length = 0;
	transfer.retransmissions_max = 1;
	// appel de la fonction qui permet l'écriture/lecture dans la mémoire
	res = I2C_MasterTransferData(LPC_I2C0, &transfer, I2C_TRANSFER_POLLING);
}

void i2c_eeprom_read(uint16_t addr, void* data, int length){
	// mise en place de la structure de configuration de transfert
	I2C_M_SETUP_Type receive;
	// Tdata contient l'adresse du mot où il faut lire
	uint8_t Tdata[] = {(uint8_t) addr};
	receive.sl_addr7bit = 0 | (1<<6)|(1<<4)|(1<<0);
	// tx_data et tx_length utilisés pour faire une sélection du mot à lire (écriture vide)
	receive.tx_data = Tdata;
	receive.tx_length = 1;
	receive.rx_data = data;
	receive.rx_length = length;
	receive.retransmissions_max = 1;
	// appel de la fonction qui permet l'écriture/lecture dans la mémoire
	I2C_MasterTransferData(LPC_I2C0, &receive, I2C_TRANSFER_POLLING);
}
