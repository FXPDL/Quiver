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
#include "HEF.h"



typedef struct {
    char tap;
    unsigned int baseTapTime;
    char bypass;
    char subdivision;
    char waveForm;
    unsigned int volume;
    unsigned int frequency;
    unsigned int symmetry;
    unsigned int depth;
    char pedalMode;
} PedalState;

typedef struct {
    unsigned int modeBypassSubdivWave;
    unsigned int baseTapTime;
    unsigned int volume;
    unsigned int frequency;
    unsigned char symmetry;
    unsigned char depth;

} PedalStorage;


typedef struct {
    unsigned uint8_t tap_A;
    unsigned uint8_t tap_B;
    unsigned uint8_t tap_Aux;
        
    unsigned uint8_t bypass_A;
    unsigned uint8_t bypass_B;
    unsigned uint8_t bypass_Aux;
} LEDState;

/*
typedef struct {
    int fuzz;
    int boost;
} PedalState;



int getFuzzState(void);
int getBoostState(void);
void updateFuzzState(int);
void updateBoostState(int);
void saveState(void);
 */
void saveState(void);

void initStateManager(void);
PedalState getCurrentState(void);
void getCurrentLEDState(void);
void restoreLEDState(void);
void updateSwitchBypassState(char);
int getSwitchBypassState(void);
void updateSwitchTapState(int);
int getSwitchTapState(void);
void updatePedalMode(void);
char getPedalMode(void);


void updateVolume(int);
int getVolume(void);
void updateFrequency(int);
int getFrequency(void);
void updateSymmetry(int);
int getSymmetry(void);
void updateDepth(int);
int getDepth(void);



void updateTapTime(void);
long getTapTime(void);
void updateSubdivisionState(void);
int getSubdivisionState(void);
void updateWaveFormState(void);
int getWaveFormState(void);
void savePreset(char);
PedalState getPreset(char);
void readPresets(void);
PedalStorage setStorageState(PedalState);

int GetBitMask(unsigned int, char, char);
int SetBitMask(int, int, int, int);