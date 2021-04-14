//Platform dependant I/O functions
#ifndef _FERRASSUDER__ARDUINO_IO_H_
#define _FERRASSUDER__ARDUINO_IO_H_

#include "general_interface.h"
#include "stm32f0xx_hal_gpio.h"
#include "main.h"

#define PIN_A    BTN1_Pin
#define PIN_B    BTN2_Pin
#define PIN_C    BTNC_Pin
#define PIN_A_PORT  BTN1_GPIO_Port
#define PIN_B_PORT  BTN2_GPIO_Port
#define PIN_C_PORT  BTNC_GPIO_Port
//#define PIN_MOSFET  GPIO_PIN_0
//#define PIN_TEMP    GPIO_PIN_0
//#define PIN_VOLT    GPIO_PIN_0

void IO_startup(){
	// Already done by HAL
}
uint8_t IO_getButtons(){
    static uint8_t lastUp=0, lastDwn=0, lastCmd=0;
    uint8_t ret=0;
    uint8_t currUp, currDwn, currCmd;

    if(APP_cfgs[CFG_USED_HAND]){
      currUp=HAL_GPIO_ReadPin(PIN_A_PORT, PIN_A)==GPIO_PIN_RESET;
      currDwn=HAL_GPIO_ReadPin(PIN_B_PORT, PIN_B)==GPIO_PIN_RESET;
      currCmd=HAL_GPIO_ReadPin(PIN_C_PORT, PIN_C)==GPIO_PIN_RESET;
    }else{
        currUp=HAL_GPIO_ReadPin(PIN_B_PORT, PIN_B)==GPIO_PIN_RESET;
        currDwn=HAL_GPIO_ReadPin(PIN_A_PORT, PIN_A)==GPIO_PIN_RESET;
        currCmd=HAL_GPIO_ReadPin(PIN_C_PORT, PIN_C)==GPIO_PIN_RESET;
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

extern ADC_HandleTypeDef hadc;

uint16_t IO_getRawTemp(){
	HAL_ADC_Start(&hadc);
	HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);
	HAL_ADC_GetValue(&hadc);
	HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);
	uint16_t ret = HAL_ADC_GetValue(&hadc);
	HAL_ADC_Stop(&hadc);
	return ret;
}

uint16_t IO_getRawVoltage(){
	HAL_ADC_Start(&hadc);
	HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);
	uint16_t ret = HAL_ADC_GetValue(&hadc);
	HAL_ADC_Stop(&hadc);
	return ret;
}
void IO_pwmMosfet(uint16_t permil){
	if(permil>1000)permil = 1000;
	TIM14->CCR1 = permil;
}
#endif // _FERRASSUDER__ARDUINO_IO_H_
