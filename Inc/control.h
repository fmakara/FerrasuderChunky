//Control functions
#ifndef _FERRASSUDER__CONTROL_H_
#define _FERRASSUDER__CONTROL_H_

#include "general_interface.h"

void CONTROL_startup();
int16_t CONTROL_readFilterRawTemperature();
int16_t CONTROL_rawToC(int16_t raw);
int32_t CONTROL_calculateComand();
int16_t CONTROL_commandToPermil(int32_t command);
void CONTROL_generateHighPWM();
void CONTROL_generateLowPWM();
void CONTROL_waitUntilCanReadTemp();

int16_t CONTROL_targetTemp;
int16_t CONTROL_currentTemp;
int16_t CONTROL_currentCommand_permil;

#define CONTROL_READ_AVG_PWR   (4)
#define CONTROL_READ_AVGS      (1<<CONTROL_READ_AVG_PWR)

void CONTROL_startup(){
    CONTROL_targetTemp = 0;
    CONTROL_currentTemp = 0;
    CONTROL_currentCommand_permil = 0;
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
	// Piecewise correlation
	int32_t a, b, ta, tb;
	if (raw<APP_cfgs[CFG_CALIB_100]) {
		a = APP_cfgs[CFG_CALIB_0];
		b = APP_cfgs[CFG_CALIB_100];
		ta = 0;
		tb = 100;
	} else if(raw<APP_cfgs[CFG_CALIB_188]) {
		a = APP_cfgs[CFG_CALIB_100];
		b = APP_cfgs[CFG_CALIB_188];
		ta = 100;
		tb = 188;
	} else if(raw<APP_cfgs[CFG_CALIB_220]) {
		a = APP_cfgs[CFG_CALIB_188];
		b = APP_cfgs[CFG_CALIB_220];
		ta = 188;
		tb = 220;
	} else if(raw<APP_cfgs[CFG_CALIB_300]) {
		a = APP_cfgs[CFG_CALIB_220];
		b = APP_cfgs[CFG_CALIB_300];
		ta = 220;
		tb = 300;
	} else {
		a = APP_cfgs[CFG_CALIB_300];
		b = APP_cfgs[CFG_CALIB_400];
		ta = 300;
		tb = 400;
	}
	int32_t r = (((int32_t)raw-a)*1024)/(b-a);
	return ta + ((r*(tb-ta))/1024);
}

int32_t CONTROL_calculateComand(){
    static int32_t integrator=0, lastErr=0;
    int32_t err = CONTROL_targetTemp-CONTROL_currentTemp;
    integrator += err;
    if(integrator>APP_cfgs[CFG_PID_MAXI])integrator=APP_cfgs[CFG_PID_MAXI];
    if(integrator<(-APP_cfgs[CFG_PID_MAXI]/10))integrator=-APP_cfgs[CFG_PID_MAXI]/10;
    int32_t c = ((APP_cfgs[CFG_PID_P]*err)/1000);
    c += ((APP_cfgs[CFG_PID_I]*integrator)/1000);
    c += ((APP_cfgs[CFG_PID_D]*(lastErr-err))/1000);
    lastErr = err;
    return c;
}

int16_t CONTROL_commandToPermil(int32_t command){
    if(command<0)return 0;
    if(command>1000)return 1000;
    return command;
}

#endif // _FERRASSUDER__CONTROL_H_
