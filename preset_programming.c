
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
#include "preset_programming.h"
#include "tactiles.h"

                       


void setDoublePressState(int f_state) {
    if (doubleTap_state == f_state) {return;}
    doubleTap_state = f_state;
    if (f_state == 1) {
        LED_tap_A = 0;
       // LED_bypass_A = 0;
        LED_tap_B = 0;
        //LED_bypass_B = 0;
       
    }
    
    if (doubleTap_state == 1) {
        if (presetSaveMode == 0) {
            presetSaveMode = 1;
            LED_bypass_Aux = 0;
            setPresetDisplay(presetChannel);
        } else {
                    //  savePreset();
            presetSaveMode = 0;  
            setPedalMode();
            resetRingLEDs();
            showSave();

        }
    }
    
    wait_ms(relay_delay);
    
}

void setPresetDisplay(char ledChannel) {
    if (ledChannel < 6) {
        set_leds_top(ledChannel, 1);
        set_leds_bottom(6); 
    } else {
        set_leds_top(6, 1);
        set_leds_bottom(10 - ledChannel + 1); 
    }
}

void resetRingLEDs(void) {
    set_leds_top(top_push_state, 1);
    set_leds_bottom(bottom_push_state);
}

void setExpressionDisplay(char ledChannel) {
    set_leds_top(ledChannel, 1);
    set_leds_bottom(6);
}