#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "constants.h"      /* program constants */ 
#include "tactiles.h"
#include "LEDs.h"
#include "preset_programming.h"

 uint8_t topTactile_pressed = 0;  
 uint8_t bottomTactile_pressed = 0;  

void read_bottom_tactile(void) {
    //read bottom tactile-----------------------------
    //  1) reset state if passed all states
    //  2) subroutine to set leds to match current state
    //  3) store state for possible brownout
    //  4) freeze program until button released
    //------------------------------------------------

    
    if (bottom_tactile == 0) {
        if (bottomTactile_pressed > 0) {
            bottomTactile_pressed--;
        }
    } else if (bottomTactile_pressed < debounce_limit*3) {  //extend debounce limit b/c these tactiles are hinky
        bottomTactile_pressed++;
    }
    
    
    if (bottomTactile_pressed == 0) { //read bottom tactile
        bottom_push_state = bottom_push_state + 1;
        if (bottom_push_state > 5) {
            bottom_push_state = 1;
        }
        modulation_changed = 1;
        set_leds_bottom(bottom_push_state);
       // FLASH_WriteWord(0x1F82, myBuf, bottom_push_state);
        while (bottom_tactile == 0) { //wait for release
        }
        wait_ms(20);
    }
}

void read_top_tactile(void) {
    //read top tactile--------------------------------
    //  1) reset state if passed all states
    //  2) subroutine to set leds to match current state
    //  3) subroutine to adjust delay time based on subdivision state
    //  4) store state for possible brownout
    //  5) freeze program until button released
    //------------------------------------------------

    
    if (top_tactile == 0) {
        if (topTactile_pressed > 0) {
            topTactile_pressed--;
        }
    } else if (topTactile_pressed < debounce_limit*3) {  //extend debounce limit b/c these tactiles are hinky
        topTactile_pressed++;
    }
    
    
    
    
    if (topTactile_pressed == 0) {

        top_push_state = top_push_state + 1;
        if (top_push_state >= 7) {
            top_push_state = 1;
        }
        set_leds_top(top_push_state, 1);
        mod_time_changed = 1;

        //FLASH_WriteWord(0x1F81, myBuf, top_push_state);
        while (top_tactile == 0) {
        }
        wait_ms(20);
    }
}

void update_mode(void) {
    //top left mode button ------------------------------------
    //  1) toggle state
    // Modes: Standard (off) / Preset / Expression
    //--------------------------------------------------
    if (mode_2 == 0) {

        
        debounce_mode2++;
        if (debounce_mode2 > 25) {
            debounce_mode2 = 25;

            if (presetSaveMode == 1) {
                presetSaveMode = 0; 
                resetRingLEDs();
            } else {
                mode2_state++;
                if (mode2_state > 2) {
                    mode2_state = 0;
                }
            }
            
            setPedalMode();
            while (mode_2 == 0) {
            }
        }
    } else {
        debounce_mode2 = 0;
    }
        
}

void setPedalMode(void) {
    switch (mode2_state) {
        case 0:
            LED_bypass_Aux = 0;
            LED_tap_Aux = 0;
            resetRingLEDs();
            break;
        case 1:
            LED_bypass_Aux = 0;
            LED_tap_Aux = 1;
            setPresetDisplay(presetChannel); //restore the LEDs
            break;
        case 2:
            LED_bypass_Aux = 1;
            LED_tap_Aux = 0;
            setExpressionDisplay(expressionChannel); //restore the LEDs
            break;
    }
}

void update_selectMode(void) {
    if (mode2_state == 0 && presetSaveMode != 1) {
        //not in preset select mode or preset save mode
        return;
    }
    if (mode_1 == 0) {
        debounce_mode1++;
        if (debounce_mode1 > 25) {
            debounce_mode1 = 25;
            if (mode2_state == presetModeCnst || presetSaveMode == 1) {
                presetChannel++;
                if (presetChannel > 10) {
                    presetChannel = 1;
                }
                setPresetDisplay(presetChannel);
            } else if (mode2_state == expressModeCnst) {
                expressionChannel++;
                if (expressionChannel > 5) {
                    expressionChannel = 1;
                }
                setExpressionDisplay(expressionChannel);
            }
            //Save button
            // preset_programmning_on =  !preset_programmning_on;

            //showBootSequence();
            //showSave();

            while (mode_1 == 0) {
            }
        }
    } else {
        debounce_mode1 = 0;
    }
    
}