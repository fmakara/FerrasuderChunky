//Display functions
#ifndef _FERRASSUDER__OLED_128_32_H_
#define _FERRASSUDER__OLED_128_32_H_

#include "general_interface.h"

void OLED_startup();
void OLED_clearScreen(uint8_t color);
void OLED_display();
void OLED_drawPixel(uint8_t x, uint8_t y, uint8_t color);
void OLED_copySprite8(uint8_t *sprite, uint8_t width, int16_t x, int16_t y, uint8_t mode);
void OLED_copySprite16(uint16_t *sprite, uint8_t width, int16_t x, int16_t y, uint8_t mode);
void OLED_copySprite32(uint32_t *sprite, uint8_t width, int16_t x, int16_t y, uint8_t mode);
void OLED_fastHLine(uint8_t x0, uint8_t y, uint8_t x1, uint8_t color);
void OLED_fastHLine(uint8_t x, uint8_t y0, uint8_t y1, uint8_t color);
void OLED_fastBox(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);

#define OLED_IIC_ADDR 0x3C

#define BLACK                          0 ///< Draw 'off' pixels
#define WHITE                          1 ///< Draw 'on' pixels
#define INVERSE                        2 ///< Invert pixels

#define SSD1306_MEMORYMODE          0x20 ///< See datasheet
#define SSD1306_COLUMNADDR          0x21 ///< See datasheet
#define SSD1306_PAGEADDR            0x22 ///< See datasheet
#define SSD1306_SETCONTRAST         0x81 ///< See datasheet
#define SSD1306_CHARGEPUMP          0x8D ///< See datasheet
#define SSD1306_SEGREMAP            0xA0 ///< See datasheet
#define SSD1306_DISPLAYALLON_RESUME 0xA4 ///< See datasheet
#define SSD1306_DISPLAYALLON        0xA5 ///< Not currently used
#define SSD1306_NORMALDISPLAY       0xA6 ///< See datasheet
#define SSD1306_INVERTDISPLAY       0xA7 ///< See datasheet
#define SSD1306_SETMULTIPLEX        0xA8 ///< See datasheet
#define SSD1306_DISPLAYOFF          0xAE ///< See datasheet
#define SSD1306_DISPLAYON           0xAF ///< See datasheet
#define SSD1306_COMSCANINC          0xC0 ///< Not currently used
#define SSD1306_COMSCANDEC          0xC8 ///< See datasheet
#define SSD1306_SETDISPLAYOFFSET    0xD3 ///< See datasheet
#define SSD1306_SETDISPLAYCLOCKDIV  0xD5 ///< See datasheet
#define SSD1306_SETPRECHARGE        0xD9 ///< See datasheet
#define SSD1306_SETCOMPINS          0xDA ///< See datasheet
#define SSD1306_SETVCOMDETECT       0xDB ///< See datasheet

#define SSD1306_SETLOWCOLUMN        0x00 ///< Not currently used
#define SSD1306_SETHIGHCOLUMN       0x10 ///< Not currently used
#define SSD1306_SETSTARTLINE        0x40 ///< See datasheet

#define SSD1306_EXTERNALVCC         0x01 ///< External display voltage source
#define SSD1306_SWITCHCAPVCC        0x02 ///< Gen. display voltage from 3.3V

#define SSD1306_RIGHT_HORIZONTAL_SCROLL              0x26 ///< Init rt scroll
#define SSD1306_LEFT_HORIZONTAL_SCROLL               0x27 ///< Init left scroll
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29 ///< Init diag scroll
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL  0x2A ///< Init diag scroll
#define SSD1306_DEACTIVATE_SCROLL                    0x2E ///< Stop scroll
#define SSD1306_ACTIVATE_SCROLL                      0x2F ///< Start scroll
#define SSD1306_SET_VERTICAL_SCROLL_AREA             0xA3 ///< Set scroll range

#define SSD1306_WIDTH  128 ///< DEPRECATED: width w/SSD1306_128_32 defined
#define SSD1306_HEIGHT  32 ///< DEPRECATED: height w/SSD1306_128_32 defined

static const uint8_t SSD1306_init1[] = {
    SSD1306_DISPLAYOFF,                   // 0xAE
    SSD1306_SETDISPLAYCLOCKDIV,           // 0xD5
    0x80,                                 // the suggested ratio 0x80
    SSD1306_SETMULTIPLEX };               // 0xA8
static const uint8_t SSD1306_init2[] = {
    SSD1306_SETDISPLAYOFFSET,             // 0xD3
    0x0,                                  // no offset
    SSD1306_SETSTARTLINE | 0x0,           // line #0
    SSD1306_CHARGEPUMP };                 // 0x8D
static const uint8_t SSD1306_init3[] = {
    SSD1306_MEMORYMODE,                   // 0x20
    0x01,                                 // 0x0 Vertical adressing
    SSD1306_SEGREMAP | 0x1,
    SSD1306_COMSCANDEC };    
static const uint8_t SSD1306_init4a[] = {
    SSD1306_SETCOMPINS,                 // 0xDA
    0x02,
    SSD1306_SETCONTRAST,                // 0x81
    0x8F };
static const uint8_t SSD1306_init5[] = {
    SSD1306_SETVCOMDETECT,               // 0xDB
    0x40,
    SSD1306_DISPLAYALLON_RESUME,         // 0xA4
    SSD1306_NORMALDISPLAY,               // 0xA6
    SSD1306_DEACTIVATE_SCROLL,
    SSD1306_DISPLAYON };                 // Main screen turn on
static const uint8_t SSD1306_dlist1[] = {
    SSD1306_PAGEADDR,
    0,                         // Page start address
    3,                         // end
    SSD1306_COLUMNADDR,        // Col start and end
    0,                               
    127}; 

uint32_t SSD1306_buffer[SSD1306_WIDTH*SSD1306_HEIGHT/32];

void SSD1306_command1(const uint8_t c) {
    uint8_t data[2] = {0, c};
    IIC_send(OLED_IIC_ADDR, data, 2);
}
void SSD1306_transmitList(const uint8_t header, const uint8_t *c, uint16_t n) {
    uint16_t offset = 0, currSize;
    uint8_t buffer[IIC_WRITE_BUFFER_MAX];
    buffer[0] = header;
    while(offset<n){
        if(offset+IIC_WRITE_BUFFER_MAX<n+1){
            currSize = IIC_WRITE_BUFFER_MAX;
        }else{
            currSize = n+1-offset;
        }
        memcpy(buffer+1, c+offset, currSize-1);
        IIC_send(OLED_IIC_ADDR, buffer, currSize);
        offset += currSize-1;
    }
}

void OLED_startup(){
    SSD1306_transmitList(0,SSD1306_init1, sizeof(SSD1306_init1));
    SSD1306_command1(SSD1306_HEIGHT - 1);
    SSD1306_transmitList(0,SSD1306_init2, sizeof(SSD1306_init2));
    SSD1306_command1(0x14);
    SSD1306_transmitList(0,SSD1306_init3, sizeof(SSD1306_init3));
    SSD1306_transmitList(0,SSD1306_init4a, sizeof(SSD1306_init4a));
    SSD1306_command1(SSD1306_SETPRECHARGE); // 0xd9
    SSD1306_command1(0xF1);
    SSD1306_transmitList(0,SSD1306_init5, sizeof(SSD1306_init5));
    APP_cfgs[CFG_USED_HAND] = 0;

}

void OLED_clearScreen(uint8_t color){
    memset(SSD1306_buffer, (color)?0xFF:0x00, sizeof(SSD1306_buffer));
}

void OLED_display(){
    SSD1306_transmitList(0,SSD1306_dlist1, sizeof(SSD1306_dlist1));
    SSD1306_transmitList(0x40, (uint8_t*)SSD1306_buffer, sizeof(SSD1306_buffer));
    if(!APP_cfgs[CFG_USED_HAND]){
      SSD1306_command1(SSD1306_COMSCANINC);
      SSD1306_command1(SSD1306_SEGREMAP | 0x0);
    }else{
      SSD1306_command1(SSD1306_COMSCANDEC);
      SSD1306_command1(SSD1306_SEGREMAP | 0x1);
    }
}

void OLED_drawPixel(uint8_t x, uint8_t y, uint8_t color){
    switch(color) {
        case WHITE:   SSD1306_buffer[x] |=  (1UL << y); break;
        case BLACK:   SSD1306_buffer[x] &= ~(1UL << y); break;
        case INVERSE: SSD1306_buffer[x] ^=  (1UL << y); break;
    }
}

void OLED_copySprite8(uint8_t *sprite, uint8_t width, int16_t x, int16_t y, uint8_t mode){
    if(x+width<0 || x>SSD1306_WIDTH)return;
    if(y<-7 || y>31)return;
    for(uint8_t i=0; i<width; i++){
        if(x+i<0 || x+i>=SSD1306_WIDTH)continue;
        uint32_t col = (y>=0)?(((uint32_t)sprite[i])<<y):(((uint32_t)sprite[i])>>-y);
        switch(mode) {
            case WHITE:   SSD1306_buffer[x+i] |=  col; break;
            case BLACK:   SSD1306_buffer[x+i] &= ~col; break;
            case INVERSE: SSD1306_buffer[x+i] ^=  col; break;
        }
    }
}

void OLED_copySprite16(uint16_t *sprite, uint8_t width, int16_t x, int16_t y, uint8_t mode){
    if(x+width<0 || x>SSD1306_WIDTH)return;
    if(y<-15 || y>31)return;
    for(uint8_t i=0; i<width; i++){
        if(x+i<0 || x+i>=SSD1306_WIDTH)continue;
        uint32_t col = (y>=0)?(((uint32_t)sprite[i])<<y):(((uint32_t)sprite[i])>>-y);
        switch(mode) {
            case WHITE:   SSD1306_buffer[x+i] |=  col; break;
            case BLACK:   SSD1306_buffer[x+i] &= ~col; break;
            case INVERSE: SSD1306_buffer[x+i] ^=  col; break;
        }
    }
}

void OLED_copySprite32(uint32_t *sprite, uint8_t width, int16_t x, int16_t y, uint8_t mode){
    if(x+width<0 || x>SSD1306_WIDTH)return;
    if(y<-31 || y>31)return;
    for(uint8_t i=0; i<width; i++){
        if(x+i<0 || x+i>=SSD1306_WIDTH)continue;
        uint32_t col = (y>=0)?(sprite[i]<<y):(sprite[i]>>-y);
        switch(mode) {
            case WHITE:   SSD1306_buffer[x+i] |=  col; break;
            case BLACK:   SSD1306_buffer[x+i] &= ~col; break;
            case INVERSE: SSD1306_buffer[x+i] ^=  col; break;
        }
    }
}

void OLED_fastHLine(uint8_t x0, uint8_t y, uint8_t x1, uint8_t color){
    uint32_t pix = 1UL<<y;
    if(x1<x0){
        uint8_t sw=x0;x0=x1;x1=sw;
    }
    for(uint8_t i=x0; i<=x1; i++){
        switch(color) {
            case WHITE:   SSD1306_buffer[i] |=  pix; break;
            case BLACK:   SSD1306_buffer[i] &= ~pix; break;
            case INVERSE: SSD1306_buffer[i] ^=  pix; break;
        }
    }
}

void OLED_fastVLine(uint8_t x, uint8_t y0, uint8_t y1, uint8_t color){
    if(y1<y0){
        uint8_t sw=y0;y0=y1;y1=sw;
    }
    uint32_t pix = (1UL<<(y1+1))-1;
    pix -= (1UL<<(y0))-1;
    switch(color) {
        case WHITE:   SSD1306_buffer[x] |=  pix; break;
        case BLACK:   SSD1306_buffer[x] &= ~pix; break;
        case INVERSE: SSD1306_buffer[x] ^=  pix; break;
    }
}

void OLED_fastBox(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color){
    if(y1<y0){
        uint8_t sw=y0;y0=y1;y1=sw;
    }
    if(x1<x0){
        uint8_t sw=x0;x0=x1;x1=sw;
    }
    uint32_t pix = (1UL<<(y1+1))-1;
    pix -= (1UL<<(y0))-1; 
    for(uint8_t i=x0; i<=x1; i++){
        switch(color) {
            case WHITE:   SSD1306_buffer[i] |=  pix; break;
            case BLACK:   SSD1306_buffer[i] &= ~pix; break;
            case INVERSE: SSD1306_buffer[i] ^=  pix; break;
        }
    }
}

#endif // _FERRASSUDER__OLED_128_32_H_
