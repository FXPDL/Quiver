/* 
 * File:   state_manager.h
 * Author: Nancy
 *
 * Created on August 7, 2016, 6:45 PM
 */

#ifndef STATE_MANAGER_H
#define	STATE_MANAGER_H

#ifdef	__cplusplus
extern "C" {
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* STATE_MANAGER_H */

#include <stdint.h>        /* For uint8_t definition */
//#include "HEF.h"



typedef struct {
    unsigned uint8_t tap_A;
    unsigned uint8_t tap_B;
    unsigned uint8_t bypass_A;
    unsigned uint8_t bypass_B;
} LEDState;

/*
typedef struct {
    int fuzz;
    int boost;
} PedalState;

void initStateManager(void);
PedalState getCurrentState(void);
int getFuzzState(void);
int getBoostState(void);
void updateFuzzState(int);
void updateBoostState(int);
void saveState(void);
 */

void getCurrentLEDState(void);
void restoreLEDState(void);
void updateSwitchBypassState(int);
int getSwitchBypassState(void);
void updateSwitchTapState(int);
int getSwitchTapState(void);