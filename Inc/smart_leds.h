//Platform dependant Neopixel functions
#ifndef _FERRASSUDER__SMART_LEDS_H_
#define _FERRASSUDER__SMART_LEDS_H_

#include "general_interface.h"

void SLEDS_startup(){
	NPX_startup(); // currently only one option for smart led
}

void SLEDS_sendPixel(uint32_t combo){
	uint8_t r = (((combo>>0)&0xFF)*5)>>1;
	uint8_t g = (((combo>>8)&0xFF)*5)>>1;
	uint8_t b = (((combo>>16)&0xFF)*5)>>1;
	NPX_sendPixel(r, g, b); // this seems to be trashed :P
	NPX_sendPixel(r, g, b);
	NPX_sendPixel(r, g, b); // Just in case the pixels are plugged in series
}

#endif // _FERRASSUDER__SMART_LEDS_H_
