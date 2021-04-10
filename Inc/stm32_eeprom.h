//Platform dependant IIC functions
#ifndef _FERRASSUDER__ARDUINO_EEPROM_H_
#define _FERRASSUDER__ARDUINO_EEPROM_H_

#include "general_interface.h"

#define EEPROM_MAGIC (0xB16B00B5)

void EEPROM_startup(){
    //uint32_t check;
    //EEPROM.get(0, check);
    //if(check!=EEPROM_MAGIC){
    //    for(uint8_t i=0; i<CFG_MAX; i++){
    //        EEPROM.put((i+1)*4, APP_cfgs[i]);
    //    }
    //    check = EEPROM_MAGIC;
    //    EEPROM.put(0, check);
    //}else{
    //    for(uint8_t i=0; i<CFG_MAX; i++){
    //        EEPROM.get((i+1)*4, APP_cfgs[i]);
    //    }
    //}
}

void EEPROM_save(uint8_t cfg){
    //int32_t current;
    //EEPROM.get((cfg+1)*4, current);
    //if(current != APP_cfgs[cfg]){
    //    EEPROM.put((cfg+1)*4, APP_cfgs[cfg]);
    //}
}

#endif // _FERRASSUDER__ARDUINO_IIC_H_
