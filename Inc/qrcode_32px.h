//Display functions
#ifndef _FERRASSUDER__QRCODE_32PX_H_
#define _FERRASSUDER__QRCODE_32PX_H_
// Feito com gerador de QRCode e Transformador de imagem em array C:
// https://www.the-qrcode-generator.com/
// https://lvgl.io/tools/imageconverter
#include "general_interface.h"
#include "oled_128x32.h"

FLASH_CONST uint32_t DICT32PX_qrcode[35]={
	0xffffffff, 0xffffffff, 0xffffffff,
	0x80ac2e03, 0xbea15afb, 0xa28a968b, 0xa2a1228b,
	0xa2c4168b, 0xbed8f6fb, 0x80aaaa03, 0xffd7dbff,
	0xa2ad49c3, 0xb15ac87f, 0xfafca8af, 0xe371aac7,
	0xecf6409f, 0xc1a3fe6f, 0xae905233, 0xf37b4b1b,
	0xb6406793, 0x9539f3bf, 0x84279977, 0xb118f2d3,
	0xac441013, 0xffb6938f, 0x80c57abf, 0xbec44ba7,
	0xa286381f, 0xa2bb9853, 0xa2a8c1af, 0xbeec1c33,
	0x8094fd8f,
	0xffffffff, 0xffffffff, 0xffffffff,
};

void DICT32_printQrcodeHelp(uint8_t x){
    uint32_t rambuf[35];
	memcpy_P(rambuf, DICT32PX_qrcode, 35*4);
	OLED_copySprite32(rambuf,35,x,0,WHITE);
}


#endif // _FERRASSUDER__QRCODE_32PX_H_

