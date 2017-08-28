
/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#endif

 
#include "state_manager.h"
#include "constants.h" 

PedalState pedalState = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


LEDState ledState = {0, 0, 0, 0, 0, 0};

int isStateInitialized = 0;

void initStateManager(void) {
    isStateInitialized = 0;
    getCurrentState();
}

PedalState getCurrentState(void) {
    
    pedalState = getPreset(0);
    isStateInitialized = 1;
    return pedalState;
}


/*
PedalState getCurrentState(void) {
    if (!isStateInitialized) {
        uint8_t r;

        // read HEF Memory contents
        r = HEF_ByteArrayRead((void *) &pedalState, 1, sizeof (pedalState));

        if (pedalState.tap != 1) {
            pedalState.tap = 0; //fail safe
        }

        if (pedalState.bypass != 1) {
            pedalState.bypass = 0; //fail safe
        }
        isStateInitialized = 1;
    }    
    return pedalState;
}


int getFuzzState() {
    getCurrentState();
    return pedalState.fuzz;
    
}


int getBoostState() {
    if (!isInitialized) {
        initStateManager();
    }
    return pedalState.boost;
    
}

void updateFuzzState(int state) {
    if (state != 1) {state = 0;}
    
    pedalState.fuzz = state;
    saveState();
}


void updateBoostState(int state) {
    if (state != 1) {state = 0;}
    
    pedalState.boost = state;
    saveState();
}
*/

void savePreset(char presetChannel) {
    //0 is current state (not preset, presets are 1 - 10)
    //Bank 0 - 0, 1, 2
    //Bank 1 - 3, 4, 5
    //Bank 2 - 6, 7, 8
    //Bank 3 - 9, 10
    uint8_t r;
    PedalStorage presets[3];  
    
    char bankID = (char) (presetChannel / 3); //truncate down to bank id
    char bankChannel = (char)(presetChannel - (bankID * 3));  //the slot (0 - 2) in the bank
    
    r = HEF_ByteArrayRead((void *) presets, bankID, sizeof (presets));
    //presets[bankChannel] = setStorageState(pedalState);

    presets[bankChannel].modeBypassSubdivWave = SetBitMask(0, pedalState.pedalMode, 0, 4);  //tap state (initially will be zero before first value is added)
    presets[bankChannel].modeBypassSubdivWave = SetBitMask(presets[bankChannel].modeBypassSubdivWave, pedalState.bypass, 1, 4);  //bypass state
    presets[bankChannel].modeBypassSubdivWave = SetBitMask(presets[bankChannel].modeBypassSubdivWave, pedalState.subdivision, 2, 4);  //subdivision
    presets[bankChannel].modeBypassSubdivWave = SetBitMask(presets[bankChannel].modeBypassSubdivWave, pedalState.waveForm, 3, 4); //wave form

    presets[bankChannel].baseTapTime = pedalState.baseTapTime;

    presets[bankChannel].volume = pedalState.volume;
    presets[bankChannel].frequency = pedalState.frequency;

    /*if (pedalState.depth > 700) {
        LED_tap_Aux = 1;
    } else {
        LED_tap_Aux = 0;
    }*/
    
    unsigned char symm = (unsigned char)(pedalState.symmetry/4);
    unsigned char dep = (unsigned char)(pedalState.depth/4);
    presets[bankChannel].symmetry = symm; 
    presets[bankChannel].depth = dep; 
    
    HEF_ByteArrayWrite(bankID, (void *) &presets, sizeof (presets));

}


void saveState(void) {
    if (isStateInitialized) {
        //Don't save before everything is initialized
        savePreset(0);
    }
   // PedalState tmp = getPreset(0);
   // char x =1;
}


PedalState getPreset(char presetChannel) {
    PedalStorage presets[3];
    uint8_t r;
    
    char bankID = presetChannel / 3; //truncate down to bank id
    char bankChannel = presetChannel - (bankID * 3);  //the slot (0 - 2) in the bank
       
    // read HEF Memory contents
    r = HEF_ByteArrayRead((void *) &presets, bankID, sizeof (presets));
    
    PedalState pedalPreset;
     
    pedalPreset.pedalMode = GetBitMask(presets[bankChannel].modeBypassSubdivWave, 0, 4);
    pedalPreset.bypass = GetBitMask(presets[bankChannel].modeBypassSubdivWave, 1, 4);
    pedalPreset.subdivision = GetBitMask(presets[bankChannel].modeBypassSubdivWave, 2, 4);
    pedalPreset.waveForm = GetBitMask(presets[bankChannel].modeBypassSubdivWave, 3, 4);
    
    pedalPreset.baseTapTime = presets[bankChannel].baseTapTime;

    pedalPreset.volume = presets[bankChannel].volume;
    pedalPreset.frequency = presets[bankChannel].frequency;

    pedalPreset.symmetry = (int)presets[bankChannel].symmetry * 4; //(GetBitMask(presets[bankChannel].symmetryDepth, 0, 8)) * 4;

    pedalPreset.depth = (int)presets[bankChannel].depth * 4; //(GetBitMask(presets[bankChannel].symmetryDepth, 1, 8)) * 4; //presets[bankChannel].depth * 4;
    
         
    
    /*if(pedalPreset.depth > 700){
        LED_bypass_Aux = 1;
    }*/
    
    
    if (pedalPreset.tap != 1) {
        pedalPreset.tap = 0; //fail safe
    }
    if (pedalPreset.bypass != 1) {
        pedalPreset.bypass = 0; //fail safe
    }

    if (pedalPreset.subdivision < 0 || pedalPreset.subdivision > 6) {
        pedalPreset.subdivision = 6; //fail safe
    }
    
    if (pedalPreset.waveForm < 1 || pedalPreset.waveForm > 5) {
        pedalPreset.waveForm = 1; //fail safe
    }

    if (pedalPreset.volume < 1 || pedalPreset.volume > 1023) {
        pedalPreset.volume = 1000; //fail safe
    }
    
    if (pedalPreset.frequency < 1 || pedalPreset.frequency > 1023) {
        pedalPreset.frequency = 1000; //fail safe
    }
    
    if (pedalPreset.symmetry < 1 || pedalPreset.symmetry > 1023) {
        pedalPreset.symmetry = 1000; //fail safe
    }

    if (pedalPreset.depth < 1 || pedalPreset.depth > 1023) {
        pedalPreset.depth = 1000; //fail safe
    }
    
    
    return pedalPreset;
}


void getCurrentLEDState(void) {
    ledState.tap_A  = LED_tap_A;
    ledState.bypass_A = LED_bypass_A ;
    ledState.tap_B = LED_tap_B  ;
    ledState.bypass_B = LED_bypass_B ;    
    ledState.tap_Aux  = LED_tap_Aux;
    ledState.bypass_Aux = LED_bypass_Aux ;
}
void restoreLEDState(void) {
    LED_tap_A = ledState.tap_A;
    LED_bypass_A = ledState.bypass_A;
    LED_tap_B = ledState.tap_B;
    LED_bypass_B = ledState.bypass_B;
    LED_tap_Aux = ledState.tap_Aux;
    LED_bypass_Aux = ledState.bypass_Aux;
}

void updateSwitchBypassState(char state) {
    if (state != 1) {state = 0;}
    
    pedalState.bypass = state;
   // saveState();
}

int getSwitchBypassState() {
    if (isStateInitialized != 1) {
        initStateManager();
    }
    return pedalState.bypass;
}


void updatePedalMode() {
    pedalState.pedalMode = mode2_state;
   // saveState();
}

char getPedalMode() {
    if (isStateInitialized != 1) {
        initStateManager();
    }
    return pedalState.pedalMode;
}


void updateVolume(int currentValue) {
    pedalState.volume = currentValue;
    //saveState();
    
}

int getVolume() {
    if (isStateInitialized != 1) {
        initStateManager();
    }
    return pedalState.volume;
}

void updateFrequency(int currentValue) {
    pedalState.frequency = currentValue;
    //saveState();
    //PedalState ps = getCurrentState();
    //int c = 1;
}

int getFrequency() {
    if (isStateInitialized != 1) {
        initStateManager();
    }
    return pedalState.frequency;
}

void updateSymmetry(int currentValue) {
    pedalState.symmetry = currentValue;
    //saveState();
}

int getSymmetry() {
    if (isStateInitialized != 1) {
        initStateManager();
    }
    
    return pedalState.symmetry;
}


void updateDepth(int currentValue) {
    pedalState.depth = currentValue;
    /*saveState();
    PedalState ps = getCurrentState();
    int c = 1;*/
}

int getDepth() {
    if (isStateInitialized != 1) {
        initStateManager();
    }
    return pedalState.depth;
}

void updateTapTime() {
    pedalState.baseTapTime = baseline_mod_time;
   // saveState();
}

long getTapTime() {
    if (isStateInitialized != 1) {
        initStateManager();
    }
    
    if (pedalState.baseTapTime < 1 || pedalState.baseTapTime > 3000) {
        pedalState.baseTapTime = 3000;
        
    }
    
    return pedalState.baseTapTime;
 
}

void updateSubdivisionState() {
    pedalState.subdivision = top_push_state;
   // saveState();
}

int getSubdivisionState() {
    if (isStateInitialized != 1) {
        initStateManager();
    }
    return pedalState.subdivision;
 
}

void updateWaveFormState() {
    pedalState.waveForm = bottom_push_state;
  //  saveState();
}

int getWaveFormState() {
    if (isStateInitialized != 1) {
        initStateManager();
    }
    return pedalState.waveForm;
 
}
void updateSwitchTapState(int state) {
    if (state != 1) {state = 0;}
    
    pedalState.tap = state;
    saveState();
}

int getSwitchTapState() {
    if (isStateInitialized != 1) {
        initStateManager();
    }
    return pedalState.tap;   
}
/*
void updateVolume(int vol) {
    pedalState.volume = (char) (vol / 4);
}
void updateFreq(int freq) {
    pedalState.frequency = (char) (freq / 4);
}
void updateDepth(int depth) {
    pedalState.depth = (char) (depth / 4);
}
*/
// Stores the given value in storage at the given index
int SetBitMask(int storage, int value, int index, int shift) {
    int shiftCount = index * shift;
    int mask = 0x0f << shiftCount;  //0x1f = 31; this method carves out 32 bits of storage, which only gives 3 bins in an integer.  make it smaller :)
    if (shift == 8) {
        mask = 0xff << shiftCount;
    }
    return (storage & ~mask) | (value << shiftCount);
}

// Retrieves the value stored in storage at the given index
int GetBitMask(unsigned int storage, char index, char shift) {
    int shiftCount = index * shift;
    int mask = 0x0f << shiftCount;
    if (shift == 8) {
        mask = 0xff << shiftCount;
    }

    return (storage & mask) >> shiftCount;
}

