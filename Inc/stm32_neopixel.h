//Platform dependant Neopixel functions
#ifndef _FERRASSUDER__NEOPIXEL_H_
#define _FERRASSUDER__NEOPIXEL_H_

#include "general_interface.h"
#include "stm32f0xx_hal_gpio.h"

#define PIN_NPXD       LEDDATA_Pin
#define PIN_NPXD_PORT  LEDDATA_GPIO_Port
#define NPXD_set() PIN_NPXD_PORT->BSRR=PIN_NPXD  //50ns
#define NPXD_reset() PIN_NPXD_PORT->BRR=PIN_NPXD  //50ns

void NPX_startup(){
	HAL_GPIO_WritePin(PIN_NPXD_PORT, PIN_NPXD, GPIO_PIN_RESET);
}

void NPX_shutdown(){
	// nothing to do yet
}

void NPX_sendPixel(uint8_t r, uint8_t g, uint8_t b){
	uint32_t color = (g<<16)|(r<<8)|(b<<0);
	// NOP 1=20n  5=105n
	for(uint32_t bit=1<<23; (bit&1)==0; bit>>=1){
		if(color&bit){  //referencia: 290ns
			asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
			NPXD_set();//total: 800 = 50set + 750NOP
			asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
			asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
			asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
			asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
			asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
			asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
			asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
			asm("NOP");asm("NOP");
			NPXD_reset(); //total: 450 = 50reset + 400loop
			asm("NOP");asm("NOP");

		} else { // +100ns -> ~~400ns
			NPXD_set(); //total: 400ns = 50set + 350NOP
			asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
			asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
			asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
			asm("NOP");asm("NOP");
			NPXD_reset();//total: 850 = 50set + 400loopp + 400NOP
			asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
			asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
			asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
			asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
			asm("NOP");asm("NOP");asm("NOP");asm("NOP");asm("NOP");
			asm("NOP");asm("NOP");asm("NOP");
		}
	}
}

#endif // _FERRASSUDER__NEOPIXEL_H_
