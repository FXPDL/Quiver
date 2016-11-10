
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
#include "SwitchBypass.h"
                       

uint8_t currentBypassState = -1;
int switchBypass_pressed = 0;  
int switchBypass_up = 1;  
int switchBypass_toggle = 0;

//int bypass_down = 0;
uint8_t bypass_turning_on = 0;



void initSwitchBypass() {
    int initState = getSwitchBypassState();
    setSwitchBypassState(initState);
}

void updateSwitchBypass(void) {

    //http://www.kennethkuhn.com/electronics/debounce.c
    /* Step 1: Update the integrator based on the input signal.  Note that the 
    integrator follows the input, decreasing or increasing towards the limits as 
    determined by the input state (0 or 1). */

    if (switch_bypass == 0) {
        if (switchBypass_pressed > 0) {
            switchBypass_pressed--;
        }
    } else if (switchBypass_pressed < debounce_limit) {
        switchBypass_pressed++;
    }

    /* Step 2: Update the output state based on the integrator.  Note that the
    output will only change states if the integrator has reached a limit, either
    0 or MAXIMUM. */

    if (switchBypass_pressed == 0) {
        //switch is down

        if (feedback_start == 0) {
            feedback_start = 1; 
            feedback_timer = 0;
        }

        if (feedback_timer >= long_press_limit && feedback_state == 0 && doubleTap_state == 0) {
            //bypass_down = long_press_limit; //try and prevent overflow4

            LED_bypass_A = 0;
            if (longTap_start != 1) {
                setFeedbackState(1);
            } else {
                setDoublePressState(1);
            }
        }        
        
        if (doubleTap_state == 0 && feedback_state == 0) {
            if (switchBypass_state == 1) {
                //switch was on, so turn it off on release
                if (switchBypass_up == 1) {
                    currentBypassState = 1;
                    switchBypass_toggle = 1;
                }



                //Switch was on, so if it is long press then kick in feedback.  If it is short, then turn off the fuzz
                /*if (feedback_timer >= long_press_limit && feedback_state == 0 && doubleTap_state == 0 && bypass_turning_on == 0) {
                    //bypass_down = long_press_limit; //try and prevent overflow
                    LATDbits.LATD0 = 1;
                    LED_bypass_A = 0;
                    if (longTap_start != 1) {
                        setFeedbackState(1);
                    } else {
                        setDoublePressState(1);
                    }
                }*/
            } else {
                if (bypass_turning_on != 1) {
                   
                    currentBypassState = 0;
                    //switchBypass was off, so turn it on
                    bypass_turning_on = 1;
                    switchBypass_toggle = 0;
                    //setSwitchBypassState(1);
                    feedback_state = 0;
                    feedback_start = 0;
                }
            }

        }
        switchBypass_up = 0;
    } else if (switchBypass_pressed >= debounce_limit) {
        if (doubleTap_state == 1) {
            setSwitchBypassState(currentBypassState);
        } else if (bypass_turning_on == 1 || feedback_state == 1) {
            setSwitchBypassState(1);
        } else if (switchBypass_toggle == 1 && feedback_state == 0 && doubleTap_state == 0) {
            setSwitchBypassState(0);
        }
        

        LED_bypass_A = switchBypass_state;
        //when the switch is up, Feedback is definitely off.  If the toggle for bypass is true, then turn the bypass off.
        setFeedbackState(0);
        setDoublePressState(0);
        feedback_start = 0;
        bypass_turning_on = 0;
        switchBypass_toggle = 0;
        switchBypass_up = 1;
        //bypass_down = 0;
        switchBypass_pressed = debounce_limit; /* defensive code if integrator got corrupted */
    }    
    
    
}


void setSwitchBypassState(int f_state) {
    if (switchBypass_state == f_state) {return;}
    switchBypass_state = f_state;
    LED_bypass_A = f_state;
    LED_bypass_B = 0;
    Relay_2 = f_state;
    Relay_1 = !f_state;
    
    wait_ms(relay_delay);

    Relay_2 = 0;
    Relay_1 = 0;

    updateSwitchBypassState(switchBypass_state);  
    wait_ms(relay_delay); 
}

void setFeedbackState(int f_state) {
    if (feedback_state == f_state) {return;}
    feedback_state = f_state;
    LED_bypass_B = f_state;
        
   // wait_ms(relay_delay);
    
}
 