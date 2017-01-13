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
int mod_counter = 0;
long test_timer = 0;

void interrupt isr(void) {
    int tmpSubDelay;

    
    extern volatile long timer;
    extern volatile long sub_timer;
    extern volatile long tap_timer;
    extern signed int adjusted_pot_value;
    extern int mod_delay_time;

    extern volatile long baseline_delay_time;

    extern  int top_push_state;
    extern uint8_t feedback_start;
    extern volatile long mod_timer;    
    extern volatile long delay_time;
    
    
    if (INTCONbits.TMR0IF == 1) {
        test_timer++;
        tmpSubDelay = delay_time;
        timer = timer + 1;
        sub_timer = sub_timer + 1;
        tap_timer = tap_timer + 1;
        mod_timer = mod_timer + 1;
        double_timer++;


        
        
        if (feedback_start == 1) {
            feedback_timer++;
            if (feedback_timer > long_press_limit) {feedback_timer = long_press_limit;}
        }
        if (longTap_start == 1) {
            longTap_timer++;
            if (longTap_timer > long_press_limit) {
                longTap_timer = long_press_limit;
            }
        }
         INTCONbits.TMR0IF = 0;       
         
         if (adjust_sub_delay == 1) {
             if ((sub_timer >= delay_time) && ((baseline_delay_time - timer) < 4)) {
                 tmpSubDelay = sub_timer + (baseline_delay_time- timer);
             }
         }
    }

    
    if (longTap_state < 1 && doubleTap_state < 1 && presetSaveMode < 1) {
       
        //Don't blink the tap if the tap is held down
        if (timer >= baseline_delay_time) { //delay_time

            //if (suspend_blink == 0) {
                LED_tap_A = 1;  
            //}
            timer = 0;
            
            if (reset_sub_delay == 1 || modulation_changed == 1) {
                //Sync the delay to the led
    //            CCPR1 = delay_counter;
                
                //Sync the modulation to the delay
                mod_counter = 0;
                modulation_changed = 0;
                mod_timer = mod_delay_time;
                
                reset_sub_delay = 0;
                sub_timer = delay_time;
            }
        }
        
        if (timer >= 30) { //delay_time
            //if (suspend_blink == 0) {
                LED_tap_A = 0; 
            //}
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
  
    if (presetSaveMode < 1 && mode2_state == 0) {
        if (sub_timer >= tmpSubDelay ) { //sub_delay_time
            if (suspend_blink == 0) {
                set_leds_top(top_push_state, 1);
            }
            tmpSubDelay = delay_time;
            sub_timer = 0;
        }

        if (sub_timer >= 20) { //delay_time
            if (suspend_blink == 0) {
                set_leds_top(top_push_state, 0);
            }
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


    
    if (mod_timer >= mod_delay_time) {        
       mod_timer = 0;
       
             
       
       if (mod_counter >= 60) {
            mod_counter = 0;
            test_timer = 0;
            LED_tap_Aux = 1;
        } else {
            LED_tap_Aux = 0;
        }
       

       
       chorus = 0;
       /*int modAngle = 6*mod_counter;
        switch (bottom_push_state) {
            case 1:  //Sin
                mod_value = modSin(modAngle, symmetry); 
                break;
            case 2:  //tri
                mod_value = modTri(modAngle, symmetry); 
                break;
            case 3:  //Square
                mod_value = (modAngle <= symmetry) ? 100 : -100; //modSquare(6*mod_counter, symmetry);
                break;
            case 4: //Saw
                mod_value =  modSaw(modAngle, symmetry); 
                break;
            case 5:  //Reverse Saw
                mod_value = modSawRev(modAngle, symmetry);            
                break;
            default:
                mod_value = 0;
                break;
        }*/
       mod_value = modArray[mod_counter];
        /*if (mod_value > 90) {
            LED_bypass_Aux = 1;
        } else {
            LED_bypass_Aux = 0;
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

}

