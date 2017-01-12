//REV 8

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */      
#include <stdbool.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "memory.h"
#include "constants.h"      /* program constants */ 

#include "user.h"          /* User funct/params, such as InitApp */
#include "LEDs.h"          /* LED controlling functions */
#include "tactiles.h"          /* LED controlling functions */

#include "SwitchBypass.h"    /* Bypass switch control */
#include "SwitchTap.h"    /* Bypass switch control */
//#include "Switch1.h"    /* Bypass switch control */
#include "usart_pic16.h"
#include "modulation.h"
/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/






volatile long mod_timer = 0;
signed int adjusted_pot_value;
int mod_delay_time = 2000;

volatile long delay_time = 2000;

int delayfound = 0;
//int delay_counter = 0;
int tmpVal = 0;


int knob_1_pos = 0;
int knob_2_pos = 0;
int knob_3_pos = 0;
int knob_4_pos = 0;
int knob_5_pos = 0;
volatile int knob1_prev = 2000;
volatile int knob2_prev = 2000;
volatile int knob3_prev = 2000;
volatile int knob4_prev = 2000;
volatile int knob5_prev = 2000;



uint8_t iCnt;
/******************************************************************************/
/* Main Program                                                               */

/******************************************************************************/

void main(void) {

    //symmetry = 180;
    calcSinArray();
    
    //updateModulationArray(); 
    
       
    /*symmetry = 25;
    updateModulationArray(); 
    
        
    symmetry = 235;
    updateModulationArray();*/
    
    USARTInit(31250);
    ConfigureOscillator();
    InitApp();

    switch_tap = 1;
    switch_bypass = 1;
    bottom_tactile = 1;
    top_tactile = 1;
    mode_2 = 1;
    mode_1 = 1;
    
    InitializeTaps();
    initSwitchBypass();
    
    //showBootSequence();    
    ReadSavedSettings();
    
    while (1) {

        
        update_mode();
        update_selectMode();
        

        updateSwitchBypass();
        if (presetSaveMode != 1) { //preset mode and preset save mode
            updateSwitchTap();
        }

        if (presetSaveMode != 1 && mode2_state != presetModeCnst) { //preset mode and preset save mode
            read_bottom_tactile();
            read_top_tactile();
        }
        
        //read pots---------------------------------------
        knob_1_pos = adc_convert(0); //   
        knob_2_pos = adc_convert(1);
        knob_3_pos = adc_convert(2);
        knob_4_pos = adc_convert(3);
        knob_5_pos = adc_convert(4);

       
        //Volume
        if ((knob_1_pos - knob1_prev) >= 4 || (knob_1_pos - knob1_prev) <= -4) {
            knob1_prev = knob_1_pos;
            CCPR4 = scaleA10kPot(knob1_prev);
            CCPR5 = scaleiA10kPot(knob1_prev);
            
        } 


        //Frequency
        if (knob_2_pos - knob2_prev >= 4 || knob_2_pos - knob2_prev <= -4) {
            knob2_prev = knob_2_pos;
            CCPR1 = scaleA100kPot(1023-knob2_prev);  //Invert the direction of the knob, so subtract from max
            CCPR2 = scaleA100kPot(1023-knob2_prev);
        }


        //Symmetry
        //knob 3 action ----------------------------------
        //Delay FB U9 U10 PWM4 PWM5
        //  1) Look to see if knob has changed by more then 0.2%
        //  2) Map knob to 0-39 for array
        //  3) Set CCP to calibrated value
        //------------------------------------------------
        if (knob_3_pos - knob3_prev >= 4 || knob_3_pos - knob3_prev <= -4) {
            knob3_prev = knob_3_pos;
            symmetry = (int) map(knob3_prev, 0, 1023, 45, 315);    
            if (symmetry == 180) {
                LED_bypass_Aux = 1;
            } else {
                LED_bypass_Aux = 0;
            }
        }
        
        

        //Rate
        //knob 4 action ----------------------------------
        //Delay MOD SPEED U11 U12 PWM6 PWM7
        //  1) Look to see if knob has changed by more then 0.2%
        //  2) Map knob to 20-1000 for array
        //  3) Set new time interval for modulation
        //------------------------------------------------
        if (knob_4_pos - knob4_prev >= 4 || knob_4_pos - knob4_prev <= -4) {
            knob4_prev = knob_4_pos;
           // mod_delay_time = map(knob4_prev, 0, 1023, 60, 1000);          
            mod_delay_time = (int)map(knob4_prev, 0, 1023, 3, 47); 

        }



        //Depth ----------------------------------
        if (knob_5_pos - knob5_prev >= 4 || knob_5_pos - knob5_prev <= -4) {
            knob5_prev = knob_5_pos;
            adjusted_pot_value = (int)map(knob5_prev, 0, 1023, 1275, 0);
        }        

        
        
        //subroutine to calculate led interval and PWM value if delay time has changed
        if (delay_time_changed == 1) {   
            delay_time = baseline_delay_time;
            delay_time = set_subdivision(baseline_delay_time, top_push_state);
            reset_sub_delay = 1;
            delayfound = 0;
            delay_counter = 0;

            /*while (delayfound == 0) {
                if (delayArray[delay_counter] <= delay_time * 2) {
                    delayfound = 1;
                    
                } else {
                    delay_counter++;
                    
                }
            }*/

            delay_time_changed = 0;

        } 
    }
}
