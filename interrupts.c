/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "constants.h"          
#include "user.h"          /* User funct/params, such as InitApp */
#include "modulation.h"    /* Modulation constants*/
#include "usart_pic16.h"
#include "modulation.h"

/******************************************************************************/
/* Interrupt Routines                                                         */

/******************************************************************************/
signed int mod_value = 0;
int mod_counter = 1;


void interrupt isr(void) {


    extern char isInitialized; 
    extern volatile long timer;
    extern volatile long sub_timer;
    extern volatile long tap_timer;
    extern signed int adjusted_pot_value;
    extern int mod_delay_time;



    extern  int top_push_state;
    extern uint8_t longBypass_start;
    extern volatile long mod_timer;    
    extern volatile long delay_time;
    
    
    if (INTCONbits.TMR0IF == 1) {
        if (isInitialized == 0) {
            //Pedal is not fully initialized yet!
            //Clear the interrupt
            INTCONbits.TMR0IF = 0;
            return;
        }
        
        /*longBypass_start = 0;
        longTap_start  = 0;
        longTap_state = 0;
            doubleTap_state = 0;
            presetSaveMode = 0;
            baseline_mod_time = 2820;*/
        
        
        if (timer == 0) {
            tmpModDelay = mod_delay_time;
        }
        timer = timer + 1;
        sub_timer = sub_timer + 1;
        tap_timer = tap_timer + 1;
        mod_timer = mod_timer + 1;
        double_timer++;
        
        char subDiv = getModulationSubdivision();




        if ((mod_timer >= tmpModDelay) && (mod_counter == subDiv) && (tmpModDelay == mod_delay_time)) {
            tmpModDelay = (delay_time - sub_timer);
        } 
        
        if (longBypass_start == 1) {
            longBypass_timer++;
            if (longBypass_timer > long_press_limit) {longBypass_timer = long_press_limit;}
        }
        if (longTap_start == 1) {
            longTap_timer++;
            if (longTap_timer > long_press_limit) {
                longTap_timer = long_press_limit;
            }
        }     
           
        if (longTap_state < 1 && doubleTap_state < 1 && presetSaveMode < 1) {
            //Don't blink the tap if the tap is held down
            if (timer >= baseline_mod_time) { //delay_time

                //if (suspend_blink == 0) {
                    LED_tap_A = 1;  
                //}
                timer = 0;

                if (modulation_changed == 1) {
                    //Sync the delay to the led
                    //Sync the modulation to the delay
                    modulation_changed = 0;
                    mod_time_changed = 0;
                    sub_timer = delay_time;
                    tmpModDelay = mod_delay_time;
                    mod_timer = tmpModDelay;
                    /*mod_counter = 0;
                    
                    mod_timer = 0;
                    tmpModDelay = mod_delay_time;*/

                    //reset_sub_delay = 0;
                    //sub_timer = delay_time;
                }
            } 

            if (timer >= 30) { //delay_time
                //if (suspend_blink == 0) {
                    LED_tap_A = 0; 
                //}
            }
        } 

        
        /*if (subDiv * mod_delay_time  != delay_time) {
            LED_bypass_Aux = 1;
        } else {
            LED_bypass_Aux = 0;
        }*/
        
        if (presetSaveMode < 1 && mode2_state == 0) {
            if (sub_timer >= delay_time ) { //sub_delay_time
                if (suspend_blink == 0) {
                    set_leds_top(top_push_state, 1);
                }
               // tmpModDelay = delay_time;
                sub_timer = 0;
            }

            if (sub_timer >= 20) { //delay_time
                if (suspend_blink == 0) {
                    set_leds_top(top_push_state, 0);
                }
            }
        }        
        
        
        

        if (presetSaveMode == 1) { 
            if (double_timer >= 250) {
                LED_tap_Aux = 1;
                double_timer = 0;
            }
            if (double_timer >= 30) { 
                LED_tap_Aux = 0;
            }    
        } 

                        


                //1 tick = 0.5119ms!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        //increment modulation -----------------------------
        //  1) Read counter to see if more then 30 steps
        //  1a) If > 31, reset counter to zero
        //  2) based on modulation state, determine which array to reference
        //  3) call array and map it to the counter to develop a value
        //  4) subroutine to calculate PWM cycle depending on mod value and depth pot
        //  5) write CCP value U14 CCPR9
        //  6) reset timer
        //--------------------------------------------------



        if (mod_timer >= tmpModDelay) {    
            mod_timer = 0;
            
           if (mod_counter >= subDiv) {
                mod_counter = 0;
                tmpModDelay = mod_delay_time;
                /*LED_tap_Aux = 1;
            } else {
                LED_tap_Aux = 0;*/
            }

           

           mod_value = modArray[mod_counter];
           /* if (mod_value < -90) {
                LED_tap_Aux = 1;
            } else {
                LED_tap_Aux = 0;
            }*/

            mod_value = modulation(mod_value, adjusted_pot_value);
            CCPR3 =  mod_value / 2;
            mod_counter++;

        } 

        if (preset_programmning_on == 1) {
            preset_blink++;

            if (preset_blink >= blink_delay) {
                LED_bypass_Aux = 1;
                if (preset_blink > blink_delay*2) {
                    preset_blink = 0;
                }

            } else {
                LED_bypass_Aux = 0;
            }

        } else {
            if (preset_blink > 0) {
                preset_blink = 0;
                LED_bypass_Aux = 0;
            }
        }
        
        
        //Clear the interrupt
        INTCONbits.TMR0IF = 0;  
    }
}

