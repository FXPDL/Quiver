#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "constants.h"      /* program constants */ 
#include "tap_exp_jack.h"

//From Curt: ExpJackState is used to determine (based on the slide switch) if the jack is in expression mode or tap mode

void readJackMode(void) { //add this function to main.c
    int ExpJackState = 1; //MOVE THIS TO THE CONSTANTS HEADER!!
    
    if (exp_mode == 0 && ExpJackState == 1) { //Exp Mode and Turned On
        setExpModeState();
    } else if (exp_mode == 1 && ExpJackState == 1){ //Tap Mode and Turned On
        setTapeModeState();
    }
}

void setExpModeState(void) {
    int extern_pot = 0;
    ANSELFbits.ANSF6 = 0; //set as ANALOG

    //may need a delay here to allow adc to stabilize before reading
    extern_pot = adc_convert(11);
    //use pot input to preform action here
}

void setTapeModeState(void) {
    #define ExpJackInput PORTFbits.RF6
    ANSELFbits.ANSF6 = 0; //set as DIGITAL
    
    if (ExpJackInput == 0) {
        //tap input code here
    }
}