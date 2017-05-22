#include "lpc17xx_i2c.h"
#include "lpc17xx_pinsel.h"
#include "global.h"

#ifndef MEMORY_H
#define MEMORY_H
void memory_init(void);
void init_i2c_eeprom(void);
void i2c_eeprom_write(uint16_t, void*, int);
void i2c_eeprom_read(uint16_t, void*, int);
void I2C0_IRQHandler(void);
#endif
