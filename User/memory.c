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
	// POWER d�j� actif par d�faut
	I2C_Init(LPC_I2C0, 1000000);
	I2C_Cmd(LPC_I2C0, ENABLE);
}

void i2c_eeprom_write(uint16_t addr, void* data, int length){
	Status res;
	// mise en place de la structure de configuration de transfert
	I2C_M_SETUP_Type transfer;
	uint8_t Tdata[256];
	length = length + 1;
	Tdata[0] = (uint8_t) addr;
	memcpy(&Tdata[1], data, sizeof(data));
	transfer.sl_addr7bit = 0;
	transfer.sl_addr7bit |= (1<<6)|(1<<4)|(1<<0);
	transfer.tx_data = Tdata;
	transfer.tx_length = length;
	transfer.rx_data = NULL;
	transfer.rx_length = 0;
	transfer.retransmissions_max = 1;
	// appel de la fonction qui permet l'�criture/lecture dans la m�moire
	res = I2C_MasterTransferData(LPC_I2C0, &transfer, I2C_TRANSFER_POLLING);
}

void i2c_eeprom_read(uint16_t addr, void* data, int length){
	// mise en place de la structure de configuration de transfert
	I2C_M_SETUP_Type* transfer;
	transfer->sl_addr7bit=addr;
	transfer->tx_length = 0;
	transfer->rx_data = data;
	transfer->rx_length = length;
	transfer->retransmissions_max=1;
	// appel de la fonction qui permet l'�criture/lecture dans la m�moire
	I2C_MasterTransferData(LPC_I2C0, transfer, I2C_TRANSFER_POLLING);
}
