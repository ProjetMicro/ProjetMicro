#include "memory.h"

void init_i2c_eeprom(){
	// POWER déjà actif par défaut
	I2C_Init(LPC_I2C0, 1000000);
	I2C_Cmd(LPC_I2C0, ENABLE);
}

void i2c_eeprom_write(uint16_t addr, void* data, int length){
	Status res;
	// mise en place de la structure de configuration de transfert
	I2C_M_SETUP_Type transfer;
	uint8_t Tdata[10];
	//length = length + 1;
	Tdata[0] = (uint8_t) addr;
	Tdata[1] = 1;
	//*Tdata = ((uint8_t) addr) | ((*(uint8_t*)(data))<<8);
	transfer.sl_addr7bit = 0;
	transfer.sl_addr7bit |= (1<<6)|(1<<4)|(1<<0);
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
	I2C_M_SETUP_Type* transfer;
	transfer->sl_addr7bit=addr;
	transfer->tx_length = 0;
	transfer->rx_data = data;
	transfer->rx_length = length;
	transfer->retransmissions_max=1;
	// appel de la fonction qui permet l'écriture/lecture dans la mémoire
	I2C_MasterTransferData(LPC_I2C0, transfer, I2C_TRANSFER_POLLING);
}
