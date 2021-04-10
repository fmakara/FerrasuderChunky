//Platform dependant IIC functions
#ifndef _FERRASSUDER__ARDUINO_EEPROM_H_
#define _FERRASSUDER__ARDUINO_EEPROM_H_

#include "general_interface.h"

#define EEPROM_MAGIC (0xB16B00B5UL)
#define EEPROM_IIC_ADDR 0x50

void EEPROM_writeByte(uint8_t addr, uint8_t data){
	uint8_t packet[2];
	packet[0] = addr;
	packet[1] = data;
	IIC_send(EEPROM_IIC_ADDR, packet, 2);
	CORE_delay(6);
}

void EEPROM_writeUint32(uint8_t addr, uint32_t data){
	uint8_t *serial = (uint8_t*)&data;
	for(uint8_t off=0; off<4; off++){
		EEPROM_writeByte(addr+off, serial[off]);
	}
}

void EEPROM_startup(){
	uint32_t magicCheck;
	uint8_t addr = 0;
	IIC_send(EEPROM_IIC_ADDR, &addr, 1);
	IIC_recv(EEPROM_IIC_ADDR, (uint8_t*)&magicCheck, 4);
	if(magicCheck!=EEPROM_MAGIC){
        OLED_clearScreen(0);
        DICT8_print("  EEPROM reset!",0,12,WHITE);
        OLED_display();
		for(uint8_t i=0; i<CFG_MAX; i++){
			EEPROM_save(i);
		}
		EEPROM_writeUint32(0, EEPROM_MAGIC);
        CORE_delay(500);
	} else {
		for(uint8_t i=0; i<CFG_MAX; i++){
			uint8_t trueaddr = 4*(1+i);
			IIC_send(EEPROM_IIC_ADDR, &trueaddr, 1);
			IIC_recv(EEPROM_IIC_ADDR, (uint8_t*)&APP_cfgs[i], 4);
		}
	}
}

void EEPROM_save(uint8_t cfg){
	int32_t current;
	uint8_t addr = 4*(1+cfg);
	IIC_send(EEPROM_IIC_ADDR, &addr, 1);
	IIC_recv(EEPROM_IIC_ADDR, (uint8_t*)&current, 4);
	if(current != APP_cfgs[cfg]){
		EEPROM_writeUint32(addr, APP_cfgs[cfg]);
	}
}

#endif // _FERRASSUDER__ARDUINO_IIC_H_
