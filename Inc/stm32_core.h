//Platform dependant core functions
#ifndef _FERRASSUDER__ARDUINO_CORE_H_
#define _FERRASSUDER__ARDUINO_CORE_H_

#include "general_interface.h"
#include <stdlib.h>
#include <string.h>
#include "stm32f0xx_hal.h"

#undef FLASH_CONST
#define FLASH_CONST static const

void CORE_startup(){
}

uint32_t CORE_getMillis(){
    return HAL_GetTick();
}
uint32_t CORE_getRand(){
    return rand();
}
void CORE_delay(uint16_t ms){
	HAL_Delay(ms);
}

#endif // _FERRASSUDER__ARDUINO_IO_H_
