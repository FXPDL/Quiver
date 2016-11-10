
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
#include "SwitchTap.h"
#include "preset_programming.h"

int tap_iteration = 1;
long tap_total = 0;
uint8_t num_taps = 4;
long tap_history [5];
extern volatile long tap_timer;


uint8_t switchTap_pressed = 0;   
uint8_t switchTap_down = 0;


void initSwitchTap() {
    int initState = getSwitchTapState();
   // setSwitchTapState(initState);
}


//tap button ------------------------------------
//  1) look to see if x sec has passed between switches
//  1a) if condition is met then reset the counter to zero and reset matrix, timer
//  1b) delay until button released
//  2) if timing is less then x sec then store time to matrix
//  3) add all entry's to matrix and divide by number of iterations
//  4) subroutine to apply subdivisions to the newly tapped tempo
//  5) calculate new modulation interval for timing
//  6) reset tap timer
//  7) iterate the tap counter
//  8) delay until button release
//-----------------------------------------------

void updateSwitchTap(void) {
    uint8_t iCnt = 0;
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
        
                 
        if (tap_timer >= tap_reset) {
            //This is a first tap.
 
            switchTap_down = 1;
            tap_timer = 0;           
            tap_iteration = 1;
            tap_total = 0;
            delay_time_changed = 0;
            LATDbits.LATD0 = 0;
 
            for (iCnt = 1; iCnt <= num_taps; iCnt++) {
                tap_history[iCnt] = 0;
            }


            if (longTap_start == 0) {
                longTap_start = 1;
                longTap_state = 0;
                longTap_timer = 0;
            }
            

           //Switch was on, so if it is long press then ignore the tap.  If it is short, then record the tap
            if (longTap_timer >= long_press_limit && longTap_state == 0) {
                //Long press
                longTap_timer = long_press_limit; //try and prevent overflow
                LED_tap_A = 0;
                
                if (feedback_start != 1) {
                    setLongTapState(1);
                } else {
                    setDoublePressState(1);
                }
            }
                
        } else if (tap_timer < tap_reset && longTap_state == 0  && switchTap_down != 1) {
            //additional taps (in series)
            switchTap_down = 1;
            if (tap_timer >= tap_reset-10) { //1172) {
                tap_timer = tap_reset-10; //1172;
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

            baseline_delay_time = tap_total / tapCntDivisor;
            delay_time_changed = 1;
            tap_timer = 0;
            
            tap_iteration++;
        }

    } else if (switchTap_pressed >= debounce_limit) {
        switchTap_down = 0;
        switchTap_state = 0;
 
        //LED_tap_B = 0;

       // longTap_state = 0;
        //when the switch is up, longTap is definitely off.  If the toggle for tap is true, then turn the tap off.
        setLongTapState(0);
        //setDoublePressState(0);
        longTap_timer = 0;
        longTap_start = 0;

        switchTap_pressed = debounce_limit; /* defensive code if integrator got corrupted */
    }    
    
}


void setSwitchTapState(int f_state) {
    if (switchTap_state == f_state) {return;}
    switchTap_state = f_state;
    //LED_tap_A = f_state;
    //LED_tap_B = 0;

    updateSwitchTapState(switchTap_state);  
}

void setLongTapState(int f_state) {
    if (longTap_state == f_state) {return;}
    longTap_state = f_state;
    LED_tap_B = f_state;
   
    
}