
/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#endif


#include "state_manager.h"
#include "SwitchTap.h"
#include "constants.h"


/*long tap1 = 0;
long tap2 = 0;
long tap3 = 0;
long tap4 = 0;
long tap5 = 0;
long tap6 = 0;
long tap7 = 0;
long tap8 = 0;
long tap9 = 0;
long tap10 = 0;*/
int tap_iteration = 1;
long tap_total = 0;
int num_taps = 4;
long tap_history [5];

int switchTap_pressed = 0;  
int switchTap_up = 1;  
int switchTap_toggle = 0;

void initSwitchTap() {
    int initState = getSwitchTapState();
    setSwitchTapState(initState);
}

void updateSwitchTap(void) {
    uint8_t iCnt;
    //http://www.kennethkuhn.com/electronics/debounce.c
    /* Step 1: Update the integrator based on the input signal.  Note that the 
    integrator follows the input, decreasing or increasing towards the limits as 
    determined by the input state (0 or 1). */

    if (switch_tap == 0) {
        if (switchTap_pressed > 0) {
            switchTap_pressed--;
        }
    } else if (switchTap_pressed < debounce_limit) {
        switchTap_pressed++;
    }

    /* Step 2: Update the output state based on the integrator.  Note that the
    output will only change states if the integrator has reached a limit, either
    0 or MAXIMUM. */

    
    if (switchTap_pressed == 0) {
        //switch is down
            //switchTap was off, so turn it on
            setSwitchTapState(1);

        if (tap_timer >= 1563) {
            tap_timer = 0;
            tap_iteration = 1;
            tap_total = 0;
            delay_time_changed = 0;
            
            for (iCnt = 1; iCnt <= num_taps; iCnt++) {
                tap_history[iCnt] = 0;
            }
            
        } else if (tap_timer < 1563) {
            
            if (tap_iteration <= 4) {
                if (tap_timer >= 1172) {
                    tap_timer = 1172;
                }
                int tapCntDivisor = num_taps;
                if (tap_iteration <= num_taps) {
                    tap_total += tap_timer;
                    tap_history[tap_iteration] = tap_timer;
                    tapCntDivisor = tap_iteration;
                } else {
                    tap_total = 0;
                    for (iCnt = 1; iCnt < num_taps; iCnt++) {
                        tap_history[iCnt] = tap_history[iCnt + 1];
                        tap_total += tap_history[iCnt];
                    }
                    tap_history[num_taps] = tap_timer;
                    tap_total += tap_timer;
                }

              //  baseline_delay_time = tap_total / tapCntDivisor;
                delay_time_changed = 1;
                tap_timer = 0;
                tap_iteration++;
            }            
            
            switchTap_up = 0;
        }
    } else if (switchTap_pressed >= debounce_limit) {
        if (switchTap_toggle == 1) {
            setSwitchTapState(0);
        }
        switchTap_toggle = 0;
        switchTap_up = 1;
        switchTap_pressed = debounce_limit; /* defensive code if integrator got corrupted */
    }    
    
    
}


void setSwitchTapState(int f_state) {
    if (switchTap_state == f_state) {return;}
    switchTap_state = f_state;
    //LED_tap_A = f_state;
    //LED_tap_B = 0;
    Relay_2 = f_state;
    Relay_1 = !f_state;

    wait_ms(relay_delay);

    Relay_2 = 0;
    Relay_1 = 0;

    updateSwitchTapState(switchTap_state);  
    wait_ms(relay_delay);
}
