//Display functions
#ifndef _FERRASSUDER__DICT_32PX_H_
#define _FERRASSUDER__DICT_32PX_H_

#include "general_interface.h"
#include "oled_128x32.h"

FLASH_CONST uint32_t DICT32PX_font[12][23]={
  {0x003ffc00,0x03ffff80,0x0fffffe0,0x1ffffff8,0x3fc003fc,0x7e00007c,0x7c00003e,0xf800001e,0xf000001f,0xf000000f,0xf000000f,0xf000000f,
   0xf000000f,0xf000000f,0xf800000f,0x7800001f,0x7c00003e,0x3e00007e,0x3fc003fc,0x1ffffff8,0x07fffff0,0x01ffffc0,0x003ffc00},// 0
  {0x00000000,0x00000000,0xf00001c0,0xf00001e0,0xf00000f0,0xf00000f0,0xf0000078,0xf000007c,0xf000003c,0xf000001e,0xffffffff,0xffffffff,
   0xffffffff,0xffffffff,0xf0000000,0xf0000000,0xf0000000,0xf0000000,0xf0000000,0xf0000000,0xf0000000,0x00000000,0x00000000},// 1
  {0x00000000,0xf8000078,0xfc00007c,0xfe00003c,0xff00001e,0xff80001e,0xf7c0000f,0xf3e0000f,0xf1f0000f,0xf0f8000f,0xf07c000f,0xf03e000f,
   0xf01f801f,0xf00fc01e,0xf007f87e,0xf001fffc,0xf000fffc,0xf0003ff8,0xf0000fe0,0xf0000000,0xf0000000,0x00000000,0x00000000},// 2
  {0x00000000,0x3c000000,0x3c000078,0x7800007c,0x7803c03c,0x7803c01e,0xf003c01e,0xf003c01f,0xf003c00f,0xf003c00f,0xf003c00f,0xf003c00f,
   0xf003e00f,0xf007e01f,0xf807701f,0x7807783e,0x7c0f3ffe,0x3e1e3ffc,0x3ffe1ff8,0x1ffc07e0,0x0ff80000,0x03e00000,0x00000000},// 3
  {0x00f80000,0x00fe0000,0x00ff0000,0x00ffc000,0x00f7e000,0x00f3f000,0x00f0f800,0x00f07e00,0x00f03f80,0x00f00fc0,0x00f007f0,0x00f001f8,
   0x00f000fe,0x00f0003f,0x00f0000f,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0x00f00000,0x00f00000,0x00f00000,0x00f00000},// 4
  {0x00000000,0x3c000000,0x7c000000,0x7800ffff,0x7800ffff,0xf800ffff,0xf000ffff,0xf000f00f,0xf000f00f,0xf000f00f,0xf000f00f,0xf000f00f,
   0xf000f00f,0xf800f00f,0x7801f00f,0x7801e00f,0x3c03e00f,0x3f0fe00f,0x1fffc00f,0x0fff800f,0x07ff0000,0x00fc0000,0x00000000},// 5
  {0x007ff000,0x07ffff00,0x0fffffc0,0x3ffffff0,0x3f8787f8,0x7e03c0fc,0x7803c07c,0xf803c03e,0xf001e01e,0xf001e01e,0xf001e00f,0xf001e00f,
   0xf001e00f,0xf001e00f,0xf801e00f,0x7803e00f,0x7c03c00f,0x3f0fc01e,0x1fff801e,0x0fff801e,0x07ff0000,0x01f80000,0x00000000},// 6
  {0x0000000f,0x0000000f,0x0000000f,0x0000000f,0x8000000f,0xf000000f,0xfc00000f,0xff00000f,0xffc0000f,0x3ff0000f,0x0ffc000f,0x03ff000f,
   0x00ffc00f,0x003ff00f,0x000ffc0f,0x0003ff0f,0x0000ffef,0x00003fff,0x000007ff,0x000001ff,0x0000007f,0x0000001f,0x00000000},// 7
  {0x07c00000,0x1fe007e0,0x3ff80ff0,0x3ff81ffc,0x7e3c3ffc,0x7c1e7c3e,0x780ef81e,0xf80ff01f,0xf007e00f,0xf007e00f,0xf003c00f,0xf003c00f,
   0xf003c00f,0xf007e00f,0xf007e00f,0xf00ff01f,0x780f781e,0x7c1e3c3e,0x7e3e3ffe,0x3ffc1ffc,0x1ff80ff8,0x0ff003e0,0x03c00000},// 8
  {0x00003f80,0x3800ffe0,0x7803fff8,0x7803fffc,0xf007e0fc,0xf007c03e,0xf00f801e,0xf00f001f,0xf00f000f,0xf00f000f,0xf00f000f,0xf00f000f,
   0x780f000f,0x780f000f,0x7c07001f,0x3e07803e,0x1f07807e,0x0fe3c1fc,0x07fffff8,0x03fffff0,0x00ffffc0,0x000ffe00,0x00000000},// 9
  {0xf0003ff0,0xf800fffc,0x7e00fffe,0x3f01e00f,0x0fc1c007,0x07e1e00f,0x01f0fffe,0x00fc7ffe,0x003e3ffc,0x001f8fe0,0x000fc000,0x0003f000,
   0x07f1f800,0x3ffc7c00,0x7ffe3f00,0x7fff0f80,0xf00787e0,0xe00383f0,0xf00780fc,0x7fff007e,0x3fff001f,0x1ffe000f,0x07f00007},// %  -> :
  {0x00000070,0x000001fc,0x000003fe,0x000007ce,0x00000707,0x00000707,0x00f80707,0x07ff03cf,0x1fff83fe,0x3fffc1fc,0x3f8fe070,0x7c01f000,
   0x7800f000,0xf800f800,0xf0007800,0xf0007800,0xf0007800,0xf0007800,0xf800f800,0x7800f000,0x7c01f000,0x3e03e000,0x1e03c000},// ºc -> ;

};

uint8_t DICT32_print(char* str, uint8_t x, uint8_t y, uint8_t mode){
    uint32_t rambuf[23];
    while(*str!=0 && x<SSD1306_WIDTH){
        char c=*str;
        if(c>=48 && c<60){
            memcpy_P(rambuf, DICT32PX_font[c-48], 23*4);
            OLED_copySprite32(rambuf,23,x,y,mode);
            x+=24;
        }
        str++;
    }
    return x;
}


#endif // _FERRASSUDER__DICT_32PX_H_

