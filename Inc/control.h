//Control functions
#ifndef _FERRASSUDER__CONTROL_H_
#define _FERRASSUDER__CONTROL_H_

#include "general_interface.h"

void CONTROL_startup();
int16_t CONTROL_readFilterRawTemperature();
int16_t CONTROL_rawToC(int16_t raw);
int32_t CONTROL_calculateComand();
int16_t CONTROL_commandToPercent(int32_t command);
void CONTROL_generateHighPWM();
void CONTROL_generateLowPWM();
void CONTROL_waitUntilCanReadTemp();

int16_t CONTROL_targetTemp;
int16_t CONTROL_currentTemp;
int16_t CONTROL_currentCommand_percent;
// T[ºc] = alpha + beta*raw
int16_t CONTROL_rawCoeffAlpha;
int16_t CONTROL_rawCoeffBeta_x256;


uint64_t CONTROL_PWMnextHigh;
uint64_t CONTROL_PWMnextLow;

#define CONTROL_READ_AVG_PWR   (4)
#define CONTROL_READ_AVGS      (1<<CONTROL_READ_AVG_PWR)

#define CONTROL_PIDX1024_P     (10*1024)
#define CONTROL_PIDX1024_I     (100)
#define CONTROL_PIDX1024_D     (0)
#define CONTROL_PIDX1024_MAXI  (1024)

#define CONTROL_PWM_PERIODMUL  (500ULL)
#define CONTROL_PWM_MAXPC      (90ULL)
#define CONTROL_STABLE_MICROS  (CONTROL_PWM_PERIODMUL*5)


void CONTROL_startup(){
    CONTROL_targetTemp = 0;
    CONTROL_currentTemp = 0;
    CONTROL_currentCommand_percent = 0;
    CONTROL_rawCoeffAlpha = 20;
    CONTROL_rawCoeffBeta_x256 = 321; //(183-20)/130
    CONTROL_PWMnextHigh = 0;
    CONTROL_PWMnextLow = 0;
}

int16_t CONTROL_readFilterRawTemperature(){
    static int16_t lastValues[CONTROL_READ_AVGS]={0};
    static uint8_t currPos = 0;
    for(int i=0; i<4; i++){
        lastValues[currPos] = IO_getRawTemp();
        currPos = (currPos+1)&(CONTROL_READ_AVGS-1);
    }
    int32_t ret = 0;
    for(unsigned i=0; i<CONTROL_READ_AVGS; i++){
        ret+=lastValues[i];
    }
    return ret>>CONTROL_READ_AVG_PWR;
}

int16_t CONTROL_rawToC(int16_t raw){
    return (((int32_t)raw*(int32_t)CONTROL_rawCoeffBeta_x256)>>8)+CONTROL_rawCoeffAlpha;
    //return raw;
}

int32_t CONTROL_calculateComand(){
    static int32_t integrator=0, lastErr=0;
    int32_t err = CONTROL_targetTemp-CONTROL_currentTemp;
    integrator += err;
    if(integrator>CONTROL_PIDX1024_MAXI)integrator=CONTROL_PIDX1024_MAXI;
    if(integrator<-CONTROL_PIDX1024_MAXI)integrator=-CONTROL_PIDX1024_MAXI;
    int32_t c = ((CONTROL_PIDX1024_P*err)>>10);
    c += ((CONTROL_PIDX1024_I*integrator)>>10);
    c += ((CONTROL_PIDX1024_D*(lastErr-err))>>10);
    lastErr = err;
    return c;
}

int16_t CONTROL_commandToPercent(int32_t command){
    if(command<0)return 0;
    if(command>100)return 100;
    return command;
}
/*
void CONTROL_generateHighPWM(){
    if(CORE_getMicros()>CONTROL_PWMnextHigh){
      CONTROL_PWMnextHigh = CORE_getMicros();
    }
    CONTROL_PWMnextLow = CONTROL_PWMnextHigh+CONTROL_currentCommand_percent*CONTROL_PWM_PERIODMUL;
    while(CORE_getMicros()<CONTROL_PWMnextHigh);
    if(CONTROL_currentCommand_percent>0){
      IO_activateMosfet(1);
    }
    CONTROL_PWMnextHigh += 100*CONTROL_PWM_PERIODMUL;
}

void CONTROL_generateLowPWM(){
    while(CORE_getMicros()<CONTROL_PWMnextLow);
    IO_activateMosfet(0);
}

void CONTROL_waitUntilCanReadTemp(){
    while(CORE_getMicros()+CONTROL_STABLE_MICROS<CONTROL_PWMnextHigh);
}*/

#endif // _FERRASSUDER__CONTROL_H_
