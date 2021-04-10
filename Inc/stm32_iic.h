//Platform dependant IIC functions
#ifndef _FERRASSUDER__ARDUINO_IIC_H_
#define _FERRASSUDER__ARDUINO_IIC_H_

#include "general_interface.h"
#include "stm32f0xx_hal_i2c.h"

extern I2C_HandleTypeDef hi2c1;

void IIC_startup(){
    //Already started by main code
}

uint8_t IIC_send(uint8_t addr, uint8_t *bytes, uint16_t size){
	return HAL_I2C_Master_Transmit(&hi2c1, addr<<1, bytes, size, 100)==HAL_OK;
}

uint8_t IIC_recv(uint8_t addr, uint8_t *bytes, uint16_t size){
	return HAL_I2C_Master_Receive(&hi2c1, (addr<<1)|1, bytes, size, 100)==HAL_OK;
}

#endif // _FERRASSUDER__ARDUINO_IIC_H_
