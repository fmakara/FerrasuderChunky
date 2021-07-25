//Declaration of the platform dependant interface
#ifndef _FERRASSUDER__GENERAL_INTERFACE_H_
#define _FERRASSUDER__GENERAL_INTERFACE_H_

#include <stdint.h>

#define BTN_UP      (1<<0)
#define BTN_DOWN    (1<<1)
#define BTN_CENTER  (1<<2)
#define BTN_MOVE    (1<<3)

#define BTN_HOLD_UP      (1<<4)
#define BTN_HOLD_DOWN    (1<<5)
#define BTN_HOLD_CENTER  (1<<6)

#ifndef FLASH_CONST
#define FLASH_CONST static const
#endif
#ifndef SSD1306_WIDTH
#define SSD1306_WIDTH 128
#endif

enum EepromConfigs {
    CFG_SLEEP_TIME_S=0,
    CFG_INITIAL_TEMP,
    CFG_USED_HAND,
    CFG_TEMP_STD,
    CFG_LED_STABLE,
    CFG_LED_UNSTABLE,
	CFG_MOV_SENSE,
	CFG_CALIB_OFFSET0,
    CFG_CALIB_0,
    CFG_CALIB_100,
    CFG_CALIB_188,
    CFG_CALIB_220,
    CFG_CALIB_300,
    CFG_CALIB_400,
	CFG_PID_P,
	CFG_PID_I,
	CFG_PID_D,
	CFG_PID_MAXI,
    CFG_MAX
};

#define VALUE_DEG_C (0)
#define VALUE_DEG_F (1)
#define VALUE_DEG_K (2)

#define VALUE_HAND_RIGHT (0)
#define VALUE_HAND_LEFT  (1)

extern int32_t APP_cfgs[CFG_MAX];

void CORE_startup();
uint32_t CORE_getMillis();
uint32_t CORE_getRand();
void CORE_delay(uint16_t ms);
void CORE_delayUs(uint16_t us);

void IO_startup();
uint8_t IO_getButtons();
uint16_t IO_getRawTemp();
uint16_t IO_getRawVoltage();
void IO_pwmMosfet(uint16_t permil);

void IIC_startup();
uint8_t IIC_send(uint8_t addr, uint8_t *bytes, uint16_t size);
uint8_t IIC_recv(uint8_t addr, uint8_t *bytes, uint16_t size);

void EEPROM_startup();
void EEPROM_save(uint8_t cfg);

void ACC_startup();
uint8_t ACC_isMoving();
void ACC_setMovementTh(uint8_t sens);

void NPX_startup();
void NPX_shutdown();
void NPX_sendPixel(uint8_t r, uint8_t g, uint8_t b);

void SLEDS_startup();
void SLEDS_sendPixel(uint32_t combo);

void memcpy_P(void* dest, const void* src, unsigned size);

#ifndef IIC_WRITE_BUFFER_MAX
#define IIC_WRITE_BUFFER_MAX 32
#endif


#endif // _FERRASSUDER__GENERAL_INTERFACE_H_
