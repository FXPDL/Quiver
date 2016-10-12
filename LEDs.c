#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include "LEDs.h"
#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "constants.h"        /* System funct/params, like osc/peripheral config */
#include "state_manager.h" 

uint8_t blink_rate = 20;

void set_leds_top(int x, int ledState) {
    LATFbits.LATF0 = 0;
    LATFbits.LATF1 = 0;
    LATFbits.LATF2 = 0;
    LATFbits.LATF3 = 0;
    LATFbits.LATF4 = 0;    
    switch (x) {
        case 1:
            LATFbits.LATF0 = ledState;
            break;
        case 2:
            LATFbits.LATF1 = ledState;
            break;
        case 3:
            LATFbits.LATF2 = ledState;
            break;
        case 4:
            LATFbits.LATF3 = ledState;
            break;
        case 5:
            LATFbits.LATF4 = ledState;
            break;
        case 6:
            break;
        case 100:
            LATFbits.LATF0 = 1;
            LATFbits.LATF1 = 1;
            LATFbits.LATF2 = 1;
            LATFbits.LATF3 = 1;
            LATFbits.LATF4 = 1; 
            break;            
    }
}


void set_leds_bottom(int x) {
    LATDbits.LATD0 = 0;
    LATDbits.LATD1 = 0;
    LATDbits.LATD2 = 0;
    LATDbits.LATD3 = 0;
    LATDbits.LATD4 = 0;    
    switch (x) {
        case 1:
            LATDbits.LATD0 = 1;
            break;
        case 2:
            LATDbits.LATD1 = 1;
            break;
        case 3:
            LATDbits.LATD2 = 1;
            break;
        case 4:
            LATDbits.LATD3 = 1;
            break;
        case 5:
            LATDbits.LATD4 = 1;
            break;
        case 6:
            break;
        case 100:
            LATDbits.LATD0 = 1;
            LATDbits.LATD1 = 1;
            LATDbits.LATD2 = 1;
            LATDbits.LATD3 = 1;
            LATDbits.LATD4 = 1; 
            break;            
    }
}


void showBootSequence(void) {
    getCurrentLEDState();
    suspend_blink = 1;

    LED_tap_A = 0;
    LED_bypass_A = 0;
    LED_tap_B = 0;
    LED_bypass_B = 0; 
    LED_tap_Aux = 0;
    LED_bypass_Aux = 0;
    

    /*for (uint8_t iFlash = 0; iFlash < 2; iFlash++) {
        LED_tap_Aux = 1;
        LED_bypass_Aux = 1;
        wait_ms(blink_rate );
        LED_tap_Aux = 0;
        LED_bypass_Aux = 0;
        LED_tap_A = 1;
        LED_bypass_A = 1;
        wait_ms(blink_rate );
        LED_tap_A = 0;
        LED_bypass_A = 0;
        wait_ms(blink_rate );
    }*/
    
    //solidring_tactiles();
    star_tactiles(0); 
    star_tactiles(0); 
    star_tactiles(1);
    star_tactiles(1);

    solidring_tactiles();
    solidring_tactiles();
  
    
    //suspend_blink = 0;
    restoreLEDState();
}


void showSave(void) {
    suspend_blink = 1;
    ring_tactiles();
    ring_tactiles();
    solidring_tactiles();
    solidring_tactiles();
    //suspend_blink = 0;
}

void showError_Alternating(void) {
    suspend_blink = 1;
    getCurrentLEDState();
    LED_tap_A = 0;
    LED_bypass_A = 0;
    
    for (uint8_t iFlash = 0; iFlash < 4; iFlash++) {
        LED_tap_B = 1;
        LED_bypass_B = 0;   
        wait_ms(blink_rate);
        LED_tap_B = 0;
        LED_bypass_B = 1;
        wait_ms(blink_rate);
    }
    restoreLEDState(); 
    //suspend_blink = 0;
}


void show_error(void) {
    
    suspend_blink = 1;
    getCurrentLEDState();
    LED_tap_A = 0;
    LED_bypass_A = 0;
    
    for (uint8_t iFlash = 0; iFlash < 4; iFlash++) {
        LED_tap_B = 1;
        LED_bypass_B = 1;   
        wait_ms(blink_rate);
        LED_tap_B = 0;
        LED_bypass_B = 0;
        wait_ms(blink_rate);
    }
    restoreLEDState();
    //suspend_blink = 0;
}


void show_cancel(void) {
    suspend_blink = 1;
    getCurrentLEDState();
    LED_tap_B = 0;
    LED_bypass_B = 0;
    
    for (uint8_t iFlash = 0; iFlash < 4; iFlash++) {
        LED_tap_A = 1;
        LED_bypass_A = 1;   
        wait_ms(blink_rate);
        LED_tap_A = 0;
        LED_bypass_A = 0;
        wait_ms(blink_rate);
    }
    restoreLEDState();  
    //suspend_blink = 0;
}


void star_tactiles(uint8_t reverse) {
    if (reverse == 1) {
        for (int iLed = 5; iLed > -1; iLed--) {
            set_leds_top(iLed, 1);
            set_leds_bottom(6 - iLed);
            wait_ms(5);
        }
    } else {
        for (int iLed = 1; iLed < 7; iLed++) {
            set_leds_top(iLed, 1);
            set_leds_bottom(6 - iLed);
            wait_ms(5);
        }        
    } 

}

void ring_tactiles(void) {
    for (int iLed = 1; iLed < 7; iLed++) {
        set_leds_top(iLed, 1);
        wait_ms(5);
    }
    for (int iLed = 5; iLed > -1; iLed--) {
        set_leds_bottom(iLed);
        wait_ms(5);
    }
}


void solidring_tactiles(void) {
    uint8_t ring_delay = 30;
    set_leds_top(100, 1); //all on
    set_leds_bottom(100); //all on
    wait_ms(ring_delay);
    
    set_leds_top(0, 1); //off
    set_leds_bottom(0); //off
    wait_ms(ring_delay);
}