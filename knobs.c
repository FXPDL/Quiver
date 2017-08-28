

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */      
#include <stdbool.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "memory.h" 
#include "constants.h"          /* User funct/params, such as InitApp */
#include "user.h"          /* User funct/params, such as InitApp */
#include "state_manager.h"

extern char isInitialized; 
//extern signed int adjusted_pot_value;

void setVolume(int rawValue) {
    CCPR4 = scaleA10kPot(rawValue);
    CCPR5 = scaleiA10kPot(rawValue);
    if (isInitialized == 1) {updateVolume(rawValue);}
}

void setFrequency(int rawValue) {
    CCPR1 = scaleA100kPot(1023.0 - rawValue);  //Invert the direction of the knob, so subtract from max
    CCPR2 = scaleA100kPot(1023.0 - rawValue);
    if (isInitialized == 1) {updateFrequency(rawValue);}
}


void setSymmetry(int rawValue) {
    symmetry = (int) map(rawValue, 0, 1023, 45, 315);
    if (isInitialized == 1) {updateFrequency(rawValue);}
}

void setDepth(int rawValue) {
    //float rawVal = (float)rawValue;
    //adjusted_pot_value = 200; //map(rawVal, 0.0, 1023.0, 1275.0, 0.0);
    if (isInitialized == 1) {updateDepth(rawValue);}
}