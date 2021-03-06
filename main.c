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
#include "state_manager.h"
#include "knobs.h"
/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/





char isInitialized = 0;
volatile long mod_timer = 0;

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

int oldSymmetry = 0;
int oldBaseTime = 0;

uint8_t iCnt;
uint8_t n;
char midiBuff[RECEIVE_BUFF_SIZE];
int midiLevel = 0;

int tap_iteration = 1;
long tap_total = 0;
uint8_t num_taps = 4;
long tap_history [5];
char useInitVals = 0;

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void) {
    LED_tap_B = 0;

    calcCosArray();   
   
    USARTInit(31250);
    ConfigureOscillator();
    InitApp();

    LED_tap_Aux = 0;
    LED_bypass_Aux = 0;
    LED_tap_A = 0;
    LED_tap_B = 0;
    
    switch_tap = 1;
    switch_bypass = 1;
    bottom_tactile = 1;
    top_tactile = 1;
    mode_2 = 1;
    mode_1 = 1;
    
    initSwitchTap();    
    InitWaveform();
    InitSubdivision();
    InitializeTaps();
    
    initSwitchBypass();
    
    //init knobs
    knob1_prev = getVolume();
    knob2_prev = getFrequency();
    knob3_prev = getSymmetry();
    knob5_prev = getDepth();

    
    setVolume(knob1_prev); 
    setFrequency(knob2_prev);
    //setSymmetry(knob3_prev);
    //adjusted_pot_value = (int)map((float)knob5_prev, 0.0, 1023.0, 1275.0, 0.0);  //This equation destroys the pedal if I call it inside a function.  So just put the equation here.

    
    //showBootSequence();    
    //ReadSavedSettings();
    //initSwitchBypass();
    
    while (1) {
        //record previous values to determine if a significant change has occurred.
        oldSymmetry = symmetry;
        oldBaseTime = baseline_mod_time;
        
        //Get the amount of data waiting in USART queue
        n = USARTDataAvailable();
        //LED_bypass_B = 0;
        //If we have some data
        if (n > 2) {
            LED_bypass_Aux = 1;
            
            USARTReadBuffer(midiBuff, n);
            if (n > 2) {
                if (midiBuff[0] >= 176 && midiBuff[0] < 192) {
                    //First bit is channel and it is prefaced with (in binary) with 1011 (176 in decimal), and it is zero based.  So the controller is sending 14, which converts to 176 + 14 - 1 = 189.
                    midiBuff[0] -= 175;
                    if (midiBuff[0] == 14) {  
                        switch (midiBuff[1]) {
                            case 102: //Bypass / Engage
                                if (midiBuff[2] == 127) { //Feedback mode
                                    if (switchBypass_state == 0) {setSwitchBypassState(1);}
                                    LED_bypass_A = 0;
                                    setLongBypassState(1);
                                } else if (midiBuff[2] == 126) { //Feedback off
                                    setSwitchBypassState(1);
                                    setLongBypassState(0);
                                } else if (midiBuff[2] < 64) { //Turn off (in bypass))
                                    setSwitchBypassState(0);
                                } else { // Turn on (not bypassed) 
                                    setSwitchBypassState(1);
                                } 
                                break;
                            case 93: //Tap tempo
                                if (tap_timer >= tap_reset) {
                                    tap_timer = 0;
                                    tap_iteration = 1;
                                    tap_total = 0;
                                    mod_time_changed = 0;

                                    for (iCnt = 1; iCnt <= num_taps; iCnt++) {
                                        tap_history[iCnt] = 0;
                                    }
                                } else {
                                    if (tap_timer >= 1172) { //max delay time (chip sounds weird if it is longer than this)
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

                                    baseline_mod_time = tap_total / tapCntDivisor;
                                    mod_time_changed = 1;
                                    tap_timer = 0;
                                    updateTapTime();
                                }
                                break;
                            case 14:  //Volume 
                                midiLevel = (int) map(midiBuff[2], 127, 0, 0, 1023);   //rescale from midi range (0 - 127) to knob range (0 - 1023)
                                CCPR4 = scaleA10kPot(midiLevel);
                                CCPR5 = scaleiA10kPot(midiLevel);
                                break;
                            case 15:  //Frequency 
                                midiLevel = (int) map(midiBuff[2], 127, 0, 0, 1023);   //rescale from midi range (0 - 127) to knob range (0 - 1023)
                                CCPR1 = scaleA100kPot(1023 - midiLevel); //Invert the direction of the knob, so subtract from max
                                CCPR2 = scaleA100kPot(1023 - midiLevel);
                                break;
                            case 16:  //Symmetry 
                                symmetry = (int) map(midiBuff[2], 127, 0, 45, 315);   
                                break;
                            case 17:  //Rate 
                                baseline_mod_time = (int)map(midiBuff[2], 127, 0, 180, 2820);  
                                updateTapTime();
                                break;
                            case 18:  //Depth 
                                adjusted_pot_value = (int)map(midiBuff[2], 127, 0, 1275, 0);   
                                break;
                            case 19:  //Subdivision
                                top_push_state = midiBuff[2];
                                if (top_push_state > 5) {//If the midi sends a value greater than 6, default it back to no subdivision (6).
                                    top_push_state = 6;
                                }
                                if (top_push_state == 0) { //Top push state no division state is 6 (for some reason)
                                    top_push_state = 6;
                                }
                                set_leds_top(top_push_state, 1);
                                mod_time_changed = 1;
                                updateSubdivisionState();
                                break;
                            case 20:  //Wave form 
                                modulation_changed = 1;
                                bottom_push_state = midiBuff[2];
                                if (bottom_push_state > 5) { //Play it safe, if the midi sends a value greater than 5, default it back to sin wave.
                                    bottom_push_state = 1;
                                }
                                if (bottom_push_state < 1) { //PIf the midi sends a value less than 1, default it back to sin wave.
                                    bottom_push_state = 1;
                                }
                                set_leds_bottom(bottom_push_state); 
                                updateWaveFormState();
                                break;                                
                        }
                    }
                }
            }
        } 
        

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


       
        if (!isInitialized) {
            //Don't read the knob on start up, use the saved setting
            knob1_prev = knob_1_pos;
            knob2_prev = knob_2_pos;
            //knob3_prev = knob_3_pos;
            knob5_prev = knob_5_pos;

        }
            
        //Volume
        if ((knob_1_pos - knob1_prev) >= 4 || (knob_1_pos - knob1_prev) <= -4) {
            knob1_prev = knob_1_pos;
            //CCPR4 = scaleA10kPot(knob1_prev);
            //CCPR5 = scaleiA10kPot(knob1_prev);
            setVolume(knob1_prev);
            
            
        } 


        //Frequency
        if (knob_2_pos - knob2_prev >= 4 || knob_2_pos - knob2_prev <= -4) {
            knob2_prev = knob_2_pos;
            //CCPR1 = scaleA100kPot(1023-knob2_prev);  //Invert the direction of the knob, so subtract from max
            //CCPR2 = scaleA100kPot(1023-knob2_prev);
            setFrequency(knob2_prev);
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
           // symmetry = (int) map(knob3_prev, 0, 1023, 45, 315); 
            setSymmetry(knob3_prev);

            /*if (symmetry > 174 && symmetry < 185) {
                LED_bypass_Aux = 1;
            } else {
                LED_bypass_Aux = 0;
            }*/
        }
        
        if (oldSymmetry - symmetry >= 2 || oldSymmetry - symmetry <= -2) {
            //"Debounce" the symmetry knob; make sure the scaled value has changed, and eliminate "noise"
            modulation_changed = 1;
        }
        
        //Rate
        //knob 4 action ----------------------------------
        //Delay MOD SPEED U11 U12 PWM6 PWM7
        //  1) Look to see if knob has changed by more then 0.2%
        //  2) Map knob to 20-1000 for array
        //  3) Set new time interval for modulation
        //------------------------------------------------
        if (!isInitialized) {
            //Don't read the knob on start up, use the saved setting
            knob4_prev = knob_4_pos;
            
        }
        if (knob_4_pos - knob4_prev >= 4 || knob_4_pos - knob4_prev <= -4) {
            
            knob4_prev = knob_4_pos;
            baseline_mod_time = (int)map(knob4_prev, 0, 1023, 180, 2820);  
            updateTapTime();
            
        }
        
        if (oldBaseTime - baseline_mod_time >= 1 || oldBaseTime - baseline_mod_time <= -1) {
            //"Debounce" the rate knob; make sure the scaled value has changed, and eliminate "noise"
            mod_time_changed = 1;

        }
        
        //Depth ----------------------------------
        if (knob_5_pos - knob5_prev >= 4 || knob_5_pos - knob5_prev <= -4) {
            knob5_prev = knob_5_pos;
            adjusted_pot_value = (int)map(knob5_prev, 0, 1023, 1275, 0);
            setDepth(knob5_prev);
            
        }        

        
        //subroutine to calculate led interval and PWM value if delay time has changed
         
        if (mod_time_changed == 1) { 
//baseline_mod_time = 2400;           
            delay_time = baseline_mod_time;
            delay_time = set_subdivision(baseline_mod_time, top_push_state);
            getModulationDelayTime();
            modulation_changed = 1;
            mod_time_changed = 0;
                        
        } 

 
        if ((modArray[120] != bottom_push_state || modArray[121] != symmetry || modArray[122] != modulationSubdivision)) {
            updateModulationArray();
            isInitialized = 1;
            
        }   
    }
}
