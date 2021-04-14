//Application functions
#ifndef _FERRASSUDER__APPLICATION_H_
#define _FERRASSUDER__APPLICATION_H_
#include <stdlib.h>
#include <string.h>
#include "general_interface.h"
#include "control.h"
#include "smart_leds.h"

#include "oled_128x32.h"
#include "dict_8px.h"
#include "dict_16px.h"
#include "qrcode_32px.h"

void APP_manageUI();
void APP_mainMenu();
void APP_calibrateTemperature();
void APP_calibrateControl();

int32_t APP_readColor(int32_t current);
int32_t APP_readInteger(int32_t current, int32_t min, int32_t max, int32_t step, uint8_t type);

uint32_t APP_bargraph[40];
int32_t APP_cfgs[CFG_MAX];
extern int16_t CONTROL_targetTemp, CONTROL_currentTemp, CONTROL_currentCommand_percent;

void APP_startup(){
    CORE_startup();
    IO_startup();
    CONTROL_startup();
    IO_pwmMosfet(0);
    SLEDS_startup();
    IIC_startup();
    OLED_startup();
    ACC_startup();

    memset(APP_bargraph, 0, sizeof(APP_bargraph));

    APP_cfgs[CFG_SLEEP_TIME_S] = 60;
    APP_cfgs[CFG_INITIAL_TEMP] = 190;
    APP_cfgs[CFG_USED_HAND] = VALUE_HAND_RIGHT;
    APP_cfgs[CFG_LED_STABLE] = (100<<16)|(100<<8)|(100<<0);
    APP_cfgs[CFG_LED_UNSTABLE] = (100<<0);
    APP_cfgs[CFG_TEMP_STD] = VALUE_DEG_C;
    APP_cfgs[CFG_SLEEP_TIME_S] = 120;
    APP_cfgs[CFG_MOV_SENSE] = 5;

    APP_cfgs[CFG_CALIB_0] = 64;
    APP_cfgs[CFG_CALIB_100] = 104;
    APP_cfgs[CFG_CALIB_188] = 144;
    APP_cfgs[CFG_CALIB_220] = 183;
    APP_cfgs[CFG_CALIB_300] = 223;
    APP_cfgs[CFG_CALIB_400] = 263;

    APP_cfgs[CFG_PID_P] = 1.0*(1<<16);
    APP_cfgs[CFG_PID_I] = 0.1*(1<<16);
    APP_cfgs[CFG_PID_D] = -1.0*(1<<16);

    EEPROM_startup();

    ACC_setMovementTh(APP_cfgs[CFG_MOV_SENSE]);

    CONTROL_targetTemp = APP_cfgs[CFG_INITIAL_TEMP];
    SLEDS_sendPixel(APP_cfgs[CFG_LED_UNSTABLE]);
}
#include "stm32f0xx_hal_gpio.h"
void APP_loop(){
    //Prepare to read the bimetalic
    IO_pwmMosfet(0);
    CORE_delayUs(500);
    //Calculate command
    int16_t raw = CONTROL_readFilterRawTemperature();
    CONTROL_currentTemp = CONTROL_rawToC(raw);
    int32_t command = CONTROL_calculateComand();
    CONTROL_currentCommand_permil = CONTROL_commandToPermil(command);
    //Activate PWM
    IO_pwmMosfet(CONTROL_currentCommand_permil);
    //Run PWM while updating screen
	APP_manageUI();
	CORE_delay(10);
}

void APP_degcToUser(int16_t temp, char* str){
    if(APP_cfgs[CFG_TEMP_STD] == VALUE_DEG_F){
        sprintf(str,"%3d;",((temp*4)>>2)+32);
    }else if(APP_cfgs[CFG_TEMP_STD] == VALUE_DEG_K){
        sprintf(str,"%3d;",temp+273);
    }else{
        sprintf(str,"%3d;",temp);
    }
}

void APP_manageUI(){
    static uint8_t wait=0, graphDivider=0;
    static uint32_t lastMovement = 0;
    uint8_t btn = IO_getButtons();
    uint8_t userSleep = 0;
    if(ACC_isMoving() || btn){
        lastMovement = CORE_getMillis();
    }
    if(btn & BTN_UP){
        CONTROL_targetTemp +=5;
        wait = 20;
        
    }else if(btn & BTN_DOWN){
        CONTROL_targetTemp -=5;
        wait = 20;
    }else if( (btn&BTN_HOLD_UP)&&(btn&BTN_HOLD_DOWN) ){
        userSleep = 1;
    }else if(btn & BTN_HOLD_UP){
        if(wait==0){
            CONTROL_targetTemp +=5;
            wait = 5;
        }else{
            wait--;
        }
    }else if(btn & BTN_HOLD_DOWN){
        if(wait==0){
            CONTROL_targetTemp -=5;
            wait = 5;
        }else{
            wait--;
        }
    }else if(btn & BTN_CENTER){
        IO_pwmMosfet(0);
        SLEDS_sendPixel(0);
        APP_mainMenu();
        lastMovement = CORE_getMillis();
        SLEDS_sendPixel(APP_cfgs[CFG_LED_STABLE]);
    }
    if(userSleep || lastMovement+APP_cfgs[CFG_SLEEP_TIME_S]*1000<CORE_getMillis()){
        //Sleep routine
        IO_pwmMosfet(0);
        SLEDS_sendPixel(0);
        int16_t *positionsX = (int16_t*)APP_bargraph;
        int16_t *positionsY = positionsX+10;
        int8_t *velocitiesX = (int8_t*)(positionsY+10);
        for(uint8_t i=0; i<10; i++){
            positionsX[i] = CORE_getRand()&(128*4-1);
            positionsY[i] = (CORE_getRand()%(4*(32+8)))-4*8;
            velocitiesX[i] = (CORE_getRand()&(4-1))-2;
        }
        do{ 
            OLED_clearScreen(0);
            for(uint8_t i=0; i<10; i++){
                positionsX[i] += velocitiesX[i];
                positionsY[i]--;
                if(positionsY[i]<-16){
                    positionsX[i] = CORE_getRand()&(128*8-1);
                    positionsY[i] = 32*4;
                    velocitiesX[i] = (CORE_getRand()&(4-1))-2;
                }
                DICT8_print("Z",positionsX[i]/8, positionsY[i]/4, WHITE);
            }
            OLED_display();
            btn = IO_getButtons();
            //Always wakeup with buttons, wakeup from shake only when user didnt press
        }while(!( (btn&(BTN_UP|BTN_DOWN|BTN_CENTER))||( ACC_isMoving()&&!userSleep ) ) );
        memset(APP_bargraph, 0, sizeof(APP_bargraph));
        lastMovement = CORE_getMillis();
    }
    
    if(CONTROL_targetTemp>400)CONTROL_targetTemp=400;
    if(CONTROL_targetTemp<100)CONTROL_targetTemp=100;
    
    OLED_clearScreen(0);
    
    char tempstr[10];
    DICT16_print("<",10,0,WHITE);
    DICT16_print("=",10,16,WHITE);
    DICT16_print(">",103,8,WHITE);
    
    APP_degcToUser(CONTROL_targetTemp, tempstr);
    DICT16_print(tempstr,24,0,WHITE);
    
    APP_degcToUser(CONTROL_currentTemp, tempstr);
    DICT16_print(tempstr,24,16,WHITE);

    graphDivider++;
    if(graphDivider==3){
        for(uint8_t i=0; i < (sizeof(APP_bargraph)/4)-1 ; i++){
            APP_bargraph[i] = APP_bargraph[i+1];
        }
        uint16_t bars = 32-((CONTROL_currentCommand_permil>>3)*32)/125;
        uint64_t lastBar = 0xFFFFFFFF-((1ULL<<bars)-1);
        APP_bargraph[(sizeof(APP_bargraph)/4)-1] = lastBar;
        graphDivider = 0;
    }
    OLED_copySprite32(APP_bargraph, sizeof(APP_bargraph)/4, 90, 0, INVERSE);

    OLED_display();
}

const char APP_MENU_STRINGS[13][19] = {
  "",
  "Voltar",
  "Tempo p/ dormir",
  "Temp. inicial",
  "M~o usada",
  "Sensib. movimento",
  "Cor LED est`vel",
  "Cor LED inst`vel",
  "Unidade Temp.",
  "Calib. Temperatura",
  "Calib. Controle",
  "Sobre",
  "",
};

void APP_mainMenu(){
    uint8_t menuIdx=0, btn;
    while(1){
        OLED_clearScreen(0);
        DICT8_print(APP_MENU_STRINGS[menuIdx],2,2,WHITE);
        DICT8_print(">>",0,12,WHITE);
        DICT8_print(APP_MENU_STRINGS[menuIdx+1],12,12,WHITE);
        DICT8_print(APP_MENU_STRINGS[menuIdx+2],2,22,WHITE);
        OLED_display();
        do{
           CORE_delay(50);
           btn = IO_getButtons()&(BTN_UP|BTN_DOWN|BTN_CENTER);
        }while(btn==0);
        if( (btn&BTN_DOWN) && (menuIdx<11) ){
            menuIdx++;
        }else if( (btn&BTN_UP) && (menuIdx>0) ){
            menuIdx--; 
        }else if(btn&BTN_CENTER){
            switch(menuIdx){
               case 1://"Tempo p/ dormir"
                  APP_cfgs[CFG_SLEEP_TIME_S] = APP_readInteger(APP_cfgs[CFG_SLEEP_TIME_S], 0, 900, 5, 1);
                  EEPROM_save(CFG_SLEEP_TIME_S);
                  break;
               case 2://"Temp. inicial"
                  APP_cfgs[CFG_INITIAL_TEMP] = APP_readInteger(APP_cfgs[CFG_INITIAL_TEMP], 100, 400, 5, 2);
                  EEPROM_save(CFG_INITIAL_TEMP);
                  break;
               case 3://"Mao usada"
                  OLED_clearScreen(0);
                  DICT8_print("  Selecao de m~o: ",2,2,WHITE);
                  DICT8_print("  Aperte o bot~o  ",2,12,WHITE);
                  DICT8_print("'cima' equivalente",2,22,WHITE);
                  OLED_display();
                  do{
                     CORE_delay(50);
                     btn = IO_getButtons()&(BTN_UP|BTN_DOWN);
                  }while(btn==0);
                  if(btn == BTN_DOWN){
                      APP_cfgs[CFG_USED_HAND] = !APP_cfgs[CFG_USED_HAND];
                      EEPROM_save(CFG_USED_HAND);
                  }
                  IO_getButtons();
                  IO_getButtons();
                  OLED_display();
                  break;

               case 4://"Sensibilidade"
                  APP_cfgs[CFG_MOV_SENSE] = APP_readInteger(APP_cfgs[CFG_MOV_SENSE], 0, 10, 1, 0);
                  EEPROM_save(CFG_MOV_SENSE);
                  ACC_setMovementTh(APP_cfgs[CFG_MOV_SENSE]);
                  break;
               case 5://"Cor LED estavel"
                  APP_cfgs[CFG_LED_STABLE] = APP_readColor(APP_cfgs[CFG_LED_STABLE]);
                  EEPROM_save(CFG_LED_STABLE);
                  break;
               case 6://"Cor LED instavel"
                  APP_cfgs[CFG_LED_UNSTABLE] = APP_readColor(APP_cfgs[CFG_LED_UNSTABLE]);
                  EEPROM_save(CFG_LED_UNSTABLE);
                  break;
               case 7://"Unidade Temp."
                  OLED_clearScreen(0);
                  DICT8_print(" Fahrenheit       ",2,2,WHITE);
                  DICT8_print("          Celcius ",2,12,WHITE);
                  DICT8_print(" Kelvin           ",2,22,WHITE);
                  OLED_display();
                  do{
                     CORE_delay(50);
                     btn = IO_getButtons()&(BTN_UP|BTN_DOWN|BTN_CENTER);
                  }while(btn==0);
                  if(btn & BTN_CENTER){
                      APP_cfgs[CFG_TEMP_STD] = VALUE_DEG_C;
                  }else if(btn & BTN_UP){
                      APP_cfgs[CFG_TEMP_STD] = VALUE_DEG_F;
                  }else{
                      APP_cfgs[CFG_TEMP_STD] = VALUE_DEG_K;
                  }
                  EEPROM_save(CFG_TEMP_STD);
                  break;
               case 8://"Calib. Temperatura"
            	  APP_calibrateTemperature();
                  break;
               case 9://"Calib. Controle"
             	  APP_calibrateControl();
                  break;
               case 10:// "Sobre"
                  OLED_clearScreen(0);
                  DICT8_print("Microesta{~o TS-12",2,2,WHITE);
                  DICT8_print("C.N. 'Ferrassuder'",2,12,WHITE);
                  DICT8_print("   FW. ver. 1.0   ",2,22,WHITE);
                  OLED_display();
                  do{
                     CORE_delay(50);
                     btn = IO_getButtons()&(BTN_UP|BTN_DOWN|BTN_CENTER);
                  }while(btn==0);
                  OLED_clearScreen(0);
                  DICT8_print(" Desenvolvida por ",2,2,WHITE);
                  DICT8_print(" Felipe & Eduardo ",2,12,WHITE);
                  DICT8_print(" Makara   Jagher  ",2,22,WHITE);
                  OLED_display();
                  do{
                     CORE_delay(50);
                     btn = IO_getButtons()&(BTN_UP|BTN_DOWN|BTN_CENTER);
                  }while(btn==0);
                  OLED_clearScreen(0);
                  //DICT8_print("                  ",2,2,WHITE);
                  DICT8_print("Ajuda/manual:     ",2,12,WHITE);
                  //DICT8_print("                  ",2,22,WHITE);
                  DICT32_printQrcodeHelp(128-36);
                  OLED_display();
                  do{
                      CORE_delay(50);
                      btn = IO_getButtons()&(BTN_UP|BTN_DOWN|BTN_CENTER);
                  }while(btn==0);

                  break;
               default://"Voltar" or error
                  return;
            }
        }
    }
}

int32_t APP_readInteger(int32_t current, int32_t min, int32_t max, int32_t step, uint8_t type){
    uint8_t wait=0, btn;
    while(1){
        OLED_clearScreen(0);
        if((current==0) && (type!=0)){
            DICT8_print("OFF",25,12,WHITE);
        }else{
            char str[5];
            if(type==2)APP_degcToUser(current, str);
            else sprintf(str,"%4d",(int)current);
            DICT16_print(str,16,8,WHITE);
            if(type==1)DICT8_print("S",75,16,WHITE);
        }
        OLED_display();
        
        btn = IO_getButtons();
        if(btn & BTN_UP){
            current += step;
            wait = 20;
        }else if(btn & BTN_DOWN){
            current -= step;
            wait = 20;
        }else if(btn & BTN_HOLD_UP){
            if(wait==0){
                current += step;
                wait = 5;
            }else{
                wait--;
            }
        }else if(btn & BTN_HOLD_DOWN){
            if(wait==0){
                current -= step;
                wait = 5;
            }else{
                wait--;
            }
        }else if(btn & BTN_CENTER){
            return current;
        }
        if(current<min)current = min;
        if(current>max)current = max;
    }
}

int32_t APP_readColor(int32_t current){
    int8_t wait=0, btn, idx=0, color[3];
    char temp[20];
    color[0] = (current>>0)&0xFF;
    color[1] = (current>>8)&0xFF;
    color[2] = (current>>16)&0xFF;
    while(1){
        OLED_clearScreen(0);
        sprintf(temp,"%3d %3d %3d",color[0],color[1],color[2]);
        DICT8_print(temp,10,12,WHITE);
        DICT8_print(" R   G   B",10,0,WHITE);
        OLED_fastHLine(10+idx*28, 22, 38+idx*28, 1);
        OLED_display();
        
        btn = IO_getButtons();
        if(btn & BTN_UP){
            color[idx] += 5;
            wait = 20;
        }else if(btn & BTN_DOWN){
            color[idx] -= 5;
            wait = 20;
        }else if(btn & BTN_HOLD_UP){
            if(wait==0){
                color[idx] += 5;
                wait = 5;
            }else{
                wait--;
            }
        }else if(btn & BTN_HOLD_DOWN){
            if(wait==0){
                color[idx] -= 5;
                wait = 5;
            }else{
                wait--;
            }
        }else if(btn & BTN_CENTER){
            idx++;
            if(idx>=3){
                return (color[0]<<0)|((int32_t)color[1]<<8)|((int32_t)color[2]<<16);
            }
        }
        if(color[idx]<0)color[idx] = 0;
        if(color[idx]>100)color[idx] = 100;
    }
}

void APP_calibrateTemperature() {
    int8_t btn;
	OLED_clearScreen(0);
    DICT8_print("Favor usar        ",2,2,WHITE);
    DICT8_print("manual p/         ",2,12,WHITE);
    DICT8_print("procedimento:     ",2,22,WHITE);
    DICT32_printQrcodeHelp(128-36);
    OLED_display();
    do{
        CORE_delay(50);
        btn = IO_getButtons()&(BTN_UP|BTN_DOWN|BTN_CENTER);
    }while(btn==0);




}

void APP_calibrateControl() {
	int8_t btn;
	OLED_clearScreen(0);
	DICT8_print("Favor usar        ",2,2,WHITE);
	DICT8_print("manual p/         ",2,12,WHITE);
	DICT8_print("procedimento:     ",2,22,WHITE);
	DICT32_printQrcodeHelp(128-36);
	OLED_display();
	do{
		CORE_delay(50);
		btn = IO_getButtons()&(BTN_UP|BTN_DOWN|BTN_CENTER);
	}while(btn==0);

}

#endif // _FERRASSUDER__APPLICATION_H_
