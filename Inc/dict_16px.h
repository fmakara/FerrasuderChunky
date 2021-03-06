//Display functions
#ifndef _FERRASSUDER__DICT_16PX_H_
#define _FERRASSUDER__DICT_16PX_H_

#include "general_interface.h"
#include "oled_128x32.h"

FLASH_CONST uint16_t DICT16PX_font[17][12]={
  {0x0000,0x0000,0x0000,0x0000,0x4000,0xE000,0xE000,0x4000,0x0000,0x0000,0x0000,0x0000},// .
  {0x0ff0,0x3ffc,0x700e,0xe006,0xc003,0xc003,0xc003,0xc003,0x6007,0x700e,0x3ffc,0x0ff0},// /
  {0x0ff0,0x3ffc,0x700e,0xe006,0xc003,0xc003,0xc003,0xc003,0x6007,0x700e,0x3ffc,0x0ff0},// 0
  {0x0000,0xc018,0xc01c,0xc00e,0xc006,0xffff,0xffff,0xc000,0xc000,0xc000,0xc000,0x0000},// 1
  {0xc006,0xe006,0xf003,0xd803,0xcc03,0xc603,0xc383,0xc1c7,0xc0fe,0xc03c,0xc000,0x0000},// 2
  {0x6006,0x6006,0xc183,0xc183,0xc183,0xc183,0xc183,0xe3c7,0x637e,0x3e3c,0x1c00,0x0000},// 3
  {0x0e00,0x0f00,0x0d80,0x0cc0,0x0c70,0x0c3c,0x0c0e,0x0c07,0xffff,0xffff,0x0c00,0x0c00},// 4
  {0x6000,0xe07f,0xc07f,0xc063,0xc063,0xc063,0xc063,0x60e3,0x70c3,0x3fc3,0x1f00,0x0000},// 5
  {0x0fe0,0x3ff8,0x731e,0xe186,0xc187,0xc183,0xc183,0xc183,0x6383,0x3f06,0x1e00,0x0000},// 6
  {0x0003,0x0003,0x8003,0xf003,0xfc03,0x1f03,0x07c3,0x01f3,0x007f,0x001f,0x0007,0x0000},// 7
  {0x3c00,0x7e1c,0x633e,0xc167,0xc1e3,0xc0c3,0xc0c3,0xc1c3,0xc1e7,0x633e,0x7e1c,0x3c00},// 8
  {0x6078,0xc0fe,0xc1c6,0xc183,0xc183,0xc183,0xe183,0x6187,0x38ce,0x1ffc,0x07f0,0x0000},// 9
  {0x003c,0x807e,0xe0c3,0x707e,0x1c3c,0x0f00,0x03c0,0x3c70,0x7e38,0xc31e,0x7e07,0x3c01},// %           -> ':'
  {0x001c,0x003e,0x0063,0x0063,0x1f3e,0x7f9c,0x71c0,0xc060,0xc060,0xc060,0x60e0,0x70c0},// ºc          -> ';'
  {0x0080,0x01c0,0x06b0,0x0490,0x0808,0x1ebc,0x0808,0x0490,0x06b0,0x01c0,0x0080,0x0000},// crosshair   -> '<'
  {0x0000,0x7000,0x8ffe,0xb001,0xbfc1,0xbfc1,0xb001,0x8ffe,0x7000,0x0554,0x0444,0x0000},// thermometer -> '='
  {0x8000,0xc100,0x7180,0x3de0,0x3ff8,0x1ffe,0x0fff,0x07ff,0x03ff,0x01df,0x00cf,0x0003},// Thunder     -> '>'
};

uint8_t DICT16_print(char* str, uint8_t x, uint8_t y, uint8_t mode){
    uint16_t rambuf[12];
    while(*str!=0 && x<SSD1306_WIDTH){
        char c=*str;
        if(c>=46 && c<63){
            memcpy(rambuf, DICT16PX_font[c-46], 12*2);
            OLED_copySprite16(rambuf,12,x,y,mode);
            x+=14;
        }else if(c==' '){
            x+=14;
        }
        str++;
    }
    return x;
}


#endif // _FERRASSUDER__DICT_16PX_H_
