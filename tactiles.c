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





void read_bottom_tactile(void) {
    //read bottom tactile-----------------------------
    //  1) reset state if passed all states
    //  2) subroutine to set leds to match current state
    //  3) store state for possible brownout
    //  4) freeze program until button released
    //------------------------------------------------
    if (bottom_tactile == 0) { //read bottom tactile
        bottom_push_state++;
        if (bottom_push_state >= 7) {
            bottom_push_state = 1;
        }
        set_leds_bottom(bottom_push_state);
        FLASH_WriteWord(0x1F82, myBuf, bottom_push_state);
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
        top_push_state = top_push_state + 1;
        if (top_push_state >= 7) {
            top_push_state = 1;
        }
        set_leds_top(top_push_state, 1);
        delay_time_changed = 1;
        FLASH_WriteWord(0x1F81, myBuf, top_push_state);
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
            mode2_state++;
            if (mode2_state > 2) {
                mode2_state = 0;
            }
            switch(mode2_state) {
                case 0:
                    LED_bypass_Aux = 0;
                    LED_tap_Aux = 0;
                    break;
                case 1:
                    LED_bypass_Aux = 1;
                    LED_tap_Aux = 0;
                    break;
                case 2:
                    LED_bypass_Aux = 0;
                    LED_tap_Aux = 1;
                    break;
            }
            while (mode_2 == 0) {
            }
        }
    } else {
        debounce_mode2 = 0;
    }
        
}