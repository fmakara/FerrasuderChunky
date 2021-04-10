//Display functions
#ifndef _FERRASSUDER__DICT_8PX_H_
#define _FERRASSUDER__DICT_8PX_H_

#include "general_interface.h"
#include "oled_128x32.h"

FLASH_CONST uint8_t DICT8PX_font[96][6]={
  {0x00,0x00,0x00,0x00,0x00,0x00},// space
  {0x00,0x00,0xbf,0x00,0x00,0x00},// !
  {0x00,0x07,0x00,0x07,0x00,0x00},// "
  {0x20,0xf4,0x2f,0xf4,0x2f,0x04},// #
  {0x00,0xa4,0x4a,0x52,0x25,0x00},// $
  {0x06,0xc9,0x3e,0x64,0x93,0x60},// %
  {0x60,0x96,0x99,0xa6,0x40,0xb0},// &
  {0x00,0x00,0x03,0x00,0x00,0x00},// '
  {0x00,0x00,0x7e,0x81,0x00,0x00},// ( 
  {0x00,0x00,0x81,0x7e,0x00,0x00},// )
  {0x0a,0x04,0x1f,0x04,0x0a,0x00},// *
  {0x10,0x10,0x7c,0x10,0x10,0x00},// +
  {0x00,0x00,0x80,0x60,0x00,0x00},// ,
  {0x00,0x10,0x10,0x10,0x00,0x00},// -
  {0x00,0x00,0x80,0x00,0x00,0x00},// .
  {0x00,0xc0,0x38,0x06,0x01,0x00},// /
  {0x7e,0x81,0x81,0x81,0x7e,0x00},// 0
  {0x82,0x81,0xff,0x80,0x80,0x00},// 1
  {0x82,0xc1,0xa1,0x91,0x8e,0x00},// 2
  {0x42,0x89,0x89,0x89,0x76,0x00},// 3
  {0x30,0x2c,0x23,0xff,0x20,0x00},// 4
  {0x4f,0x89,0x89,0x89,0x71,0x00},// 5
  {0x7c,0x8a,0x89,0x89,0x71,0x00},// 6
  {0x01,0xc1,0x31,0x0d,0x03,0x00},// 7
  {0x76,0x89,0x89,0x89,0x76,0x00},// 8
  {0x8e,0x91,0x91,0x51,0x3e,0x00},// 9
  {0x00,0x00,0x24,0x00,0x00,0x00},// :
  {0x00,0x00,0x80,0x64,0x00,0x00},// ;
  {0x10,0x10,0x28,0x28,0x44,0x00},// <
  {0x24,0x24,0x24,0x24,0x24,0x00},// =
  {0x44,0x28,0x28,0x10,0x10,0x00},// >
  {0x00,0x02,0xb1,0x09,0x06,0x00},// ?
  {0x7e,0xb9,0x45,0x3d,0x41,0x3e},// @
  {0xf0,0x2c,0x23,0x2c,0xf0,0x00},// A
  {0xff,0x89,0x89,0x8e,0x70,0x00},// B
  {0x3c,0x42,0x81,0x81,0x81,0x42},// C
  {0xff,0x81,0x81,0x81,0x42,0x3c},// D
  {0x00,0xff,0x89,0x89,0x89,0x00},// E
  {0xff,0x09,0x09,0x09,0x00,0x00},// F
  {0x3c,0x42,0x81,0x91,0x91,0x72},// G
  {0xff,0x08,0x08,0x08,0x08,0xff},// H
  {0x00,0x00,0xff,0x00,0x00,0x00},// I
  {0x00,0x00,0x80,0x80,0x7f,0x00},// J
  {0xff,0x08,0x14,0x62,0x81,0x00},// K
  {0x00,0xff,0x80,0x80,0x80,0x00},// L
  {0xff,0x0c,0x30,0x0c,0xff,0x00},// M
  {0xff,0x03,0x0c,0x30,0xc0,0xff},// N
  {0x3c,0x42,0x81,0x81,0x42,0x3c},// O
  {0xff,0x11,0x11,0x11,0x0e,0x00},// P
  {0x3c,0x42,0x81,0xa1,0x42,0xbc},// Q
  {0xff,0x11,0x11,0x31,0xce,0x00},// R
  {0x00,0x46,0x89,0x91,0x62,0x00},// S
  {0x01,0x01,0xff,0x01,0x01,0x00},// T
  {0x7f,0x80,0x80,0x80,0x80,0x7f},// U
  {0x0f,0x30,0xc0,0x30,0x0f,0x00},// V
  {0x1f,0xe0,0x18,0xe0,0x1f,0x00},// W
  {0xc3,0x24,0x18,0x24,0xc3,0x00},// X
  {0x03,0x0c,0xf0,0x0c,0x03,0x00},// Y
  {0xc1,0xa1,0x91,0x89,0x85,0x83},// Z
  {0x00,0x00,0xff,0x81,0x00,0x00},// [
  {0x00,0x01,0x06,0x38,0xc0,0x00},// backslash
  {0x00,0x00,0x81,0xff,0x00,0x00},// ]
  {0x00,0x02,0x01,0x02,0x00,0x00},// ^
  {0x80,0x80,0x80,0x80,0x80,0x80},// _
  {0x48,0xa8,0xa8,0xaa,0xf1,0x00},// aacute  -> '`'
  {0x64,0x94,0x94,0x94,0xf8,0x00},// a
  {0xff,0x88,0x88,0x88,0x70,0x00},// b
  {0x00,0x78,0x84,0x84,0x84,0x00},// c
  {0x70,0x88,0x88,0x88,0xff,0x00},// d
  {0x00,0x78,0x94,0x94,0x98,0x00},// e
  {0x00,0x08,0xfe,0x09,0x09,0x00},// f
  {0xd6,0xa9,0xa9,0xa7,0x41,0x00},// g
  {0xff,0x10,0x08,0x08,0xf0,0x00},// h
  {0x00,0x00,0xfd,0x00,0x00,0x00},// i
  {0x00,0x80,0x80,0x7d,0x00,0x00},// j
  {0x00,0xff,0x10,0x68,0x84,0x00},// k
  {0x00,0x00,0xff,0x00,0x00,0x00},// l
  {0xfc,0x08,0x04,0xf8,0x04,0xf8},// m
  {0xfc,0x08,0x04,0x04,0xf8,0x00},// n
  {0x78,0x84,0x84,0x84,0x78,0x00},// o
  {0xfc,0x24,0x24,0x24,0x18,0x00},// p
  {0x18,0x24,0x24,0x24,0xfc,0x00},// q
  {0x00,0xfc,0x08,0x04,0x04,0x00},// r
  {0x00,0x98,0x94,0xa4,0x64,0x00},// s
  {0x00,0x04,0x7f,0x84,0x84,0x00},// t
  {0x7c,0x80,0x80,0x40,0xfc,0x00},// u
  {0x0c,0x30,0xc0,0x30,0x0c,0x00},// v
  {0x3c,0xc0,0x30,0x30,0xc0,0x3c},// w
  {0x84,0x48,0x30,0x48,0x84,0x00},// x
  {0x04,0xc8,0x30,0x08,0x04,0x00},// y
  {0x00,0xc4,0xb4,0x8c,0x00,0x00},// z
  {0x00,0x1c,0xa2,0x62,0x22,0x00},// ccedil -> '{'
  {0x00,0x00,0xff,0x00,0x00,0x00},// |
  {0x00,0x81,0x6e,0x10,0x00,0x00},// }
  {0x02,0x49,0xa9,0xaa,0xaa,0xf1},// atilde -> '~'
  {0x02,0x05,0x7a,0x84,0x84,0x84},// degc
};

uint8_t DICT8_print(const char* str, int8_t x, int8_t y, uint8_t mode){
    uint8_t rambuf[6];
    while(*str!=0 && x<SSD1306_WIDTH){
        char c=*str;
        if(c>=32 && c<128){
            CORE_flashMemcpy(rambuf, DICT8PX_font[c-32], 6);
            OLED_copySprite8(rambuf,6,x,y,mode);
            x+=7;
        }
        str++;
    }
    return x;
}


#endif // _FERRASSUDER__DICT_8PX_H_
