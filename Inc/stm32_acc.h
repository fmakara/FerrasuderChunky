#ifndef _FERRASSUDER__ACCELEROMETER_H_
#define _FERRASSUDER__ACCELEROMETER_H_

#include <stdint.h>
#include "general_interface.h"

#define ACC_IIC_ADDR 0x12

#define PIN_ACCINT1       MOVINT1_Pin
#define PIN_ACCINT1_PORT  MOVINT1_GPIO_Port

void ACC_setCfg8(uint8_t addr, uint8_t data){
	uint8_t packet[2];
	packet[0] = addr;
	packet[1] = data;
    IIC_send(ACC_IIC_ADDR, packet, 2);
}
uint16_t ACC_getCfg16(uint8_t addr){
	uint8_t packet[2] = {0,0};
    IIC_send(ACC_IIC_ADDR, &addr, 1);
    IIC_recv(ACC_IIC_ADDR, packet, 2);
    return packet[0]|(packet[1]<<8);
}
uint16_t ACC_getCfg8(uint8_t addr){
	uint8_t ret = 0;
    IIC_send(ACC_IIC_ADDR, &addr, 1);
    IIC_recv(ACC_IIC_ADDR, &ret, 1);
    return ret;
}


void ACC_startup(){
	ACC_setCfg8(0x36, 0xB6);// soft-reset the acc just in case...
    CORE_delay(100);
	ACC_setCfg8(0x36, 0x00);

	//ACC_setCfg8(0x0F, 0xFF);// Lowest resolution
	ACC_setCfg8(0x0F, 0xF1);
	ACC_setCfg8(0x10, 0xE7);// Smaller bandwidth
	ACC_setCfg8(0x18, 0x1F);// Enable any axis interruption
	ACC_setCfg8(0x1A, 0x63);// Put any axis interruption on INT1
	ACC_setCfg8(0x21, 0x1D);// Interrupts are latched
	ACC_setMovementTh(127);// just in case....

	ACC_setCfg8(0x11, 0xC0); // Start operation
}

uint8_t ACC_isMoving(){
	if(HAL_GPIO_ReadPin(PIN_ACCINT1_PORT, PIN_ACCINT1)==GPIO_PIN_RESET){
		return 0;
	}
	ACC_getCfg8(0x09); // hopefully this resets the int pin
	return 1;
}

void ACC_setMovementTh(uint8_t sens){
	if(sens>10)sens = 10;
	sens = 10-sens;
	uint16_t th = 5+(sens*sens*5)/3;
	ACC_setCfg8(0x2E, th);
}


#endif // _FERRASSUDER__ACCELEROMETER_H_
