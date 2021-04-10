//Platform dependant I/O functions
#ifndef _FERRASSUDER__ARDUINO_IO_H_
#define _FERRASSUDER__ARDUINO_IO_H_

#include "general_interface.h"
#include "stm32f0xx_hal_gpio.h"
#include "main.h"

#define PIN_UP      BTN_UP_Pin
#define PIN_DOWN    BTN_DOWN_Pin
#define PIN_CMD     BTN_CENTER_Pin
#define PIN_UP_PORT    BTN_UP_GPIO_Port
#define PIN_DOWN_PORT  BTN_DOWN_GPIO_Port
#define PIN_CMD_PORT   BTN_CENTER_GPIO_Port
//#define PIN_MOSFET  GPIO_PIN_0
//#define PIN_TEMP    GPIO_PIN_0
//#define PIN_VOLT    GPIO_PIN_0

void IO_startup(){

	/*
    pinMode(PIN_UP,INPUT_PULLUP);
    pinMode(PIN_DOWN,INPUT_PULLUP);
    pinMode(PIN_CMD,INPUT_PULLUP);
    pinMode(PIN_MOSFET,OUTPUT);
    pinMode(A1,OUTPUT);
    pinMode(A2,OUTPUT);
    digitalWrite(PIN_MOSFET, LOW);
    digitalWrite(A1, LOW);
    digitalWrite(A2, HIGH);
    
    digitalWrite(A1, LOW);*/
}
uint8_t IO_getButtons(){
    static uint8_t lastUp=0, lastDwn=0, lastCmd=0;
    uint8_t ret=0;
    uint8_t currUp, currDwn, currCmd;


    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = PIN_UP|PIN_DOWN|PIN_CMD;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    HAL_GPIO_ReadPin(GPIOB, PIN_UP);

    if(APP_cfgs[CFG_USED_HAND]){
      currUp=HAL_GPIO_ReadPin(PIN_DOWN_PORT, PIN_DOWN)==GPIO_PIN_RESET;
      currDwn=HAL_GPIO_ReadPin(PIN_UP_PORT, PIN_UP)==GPIO_PIN_RESET;
      currCmd=HAL_GPIO_ReadPin(PIN_CMD_PORT, PIN_CMD)==GPIO_PIN_RESET;
    }else{
        currUp=HAL_GPIO_ReadPin(PIN_UP_PORT, PIN_UP)==GPIO_PIN_RESET;
        currDwn=HAL_GPIO_ReadPin(PIN_DOWN_PORT, PIN_DOWN)==GPIO_PIN_RESET;
        currCmd=HAL_GPIO_ReadPin(PIN_CMD_PORT, PIN_CMD)==GPIO_PIN_RESET;
    }
    if(currUp){
      ret |= BTN_HOLD_UP;
      if(!lastUp){
        ret |= BTN_UP;
      }
    }
    if(currDwn){
      ret |= BTN_HOLD_DOWN;
      if(!lastDwn){
        ret|=BTN_DOWN;
      }
    }
    if(currCmd){
      ret |= BTN_HOLD_CENTER;
      if(!lastCmd){
        ret|=BTN_CENTER;
      }
    }
    lastUp = currUp;
    lastDwn = currDwn;
    lastCmd = currCmd;
    return ret;
}
uint16_t IO_getRawTemp(){
    return 0;//analogRead(PIN_TEMP);
}
uint16_t IO_getRawVoltage(){
    return 0;//analogRead(PIN_VOLT);
}
void IO_pwmMosfet(uint8_t percent){
	/*
    uint16_t aw = percent<<8;
    aw /=100;
    if(aw>255)aw = 255;
    analogWrite(PIN_MOSFET, aw );*/
}
#endif // _FERRASSUDER__ARDUINO_IO_H_
