#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "constants.h"      /* program constants */ 
#include "expressTap.h" 

void update_expressSwitchState(void) {
    if (exp_mode != expSwitchState) {
        //The switch has changed, so update the reading setting.
        expSwitchState = exp_mode;
        if (exp_mode == 0) { //Exp Mode 
            initExpModeState();
        } else { //Tap Mode 
            initTapeModeState();
        }
    }
}

void initExpModeState(void) {
    ANSELFbits.ANSF6 = 0; //set as ANALOG
    //may need a delay here to allow adc to stabilize before reading
    wait_ms(relay_delay);
}

void initTapeModeState(void) {
    ANSELFbits.ANSF6 = 0; //set as DIGITAL
}