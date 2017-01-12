/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */ 
#include <math.h>       /* For trunc definition */
#include <stdbool.h>        /* For true/false definition */
#include "user.h"
#include "constants.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void) {
    TRISBbits.TRISB0 = 0; //set as OUTPUT
    TRISBbits.TRISB1 = 0; //set as OUTPUT
    TRISBbits.TRISB2 = 0; //set as OUTPUT
    TRISBbits.TRISB3 = 0; //set as OUTPUT
    TRISBbits.TRISB4 = 0; //set as OUTPUT
    TRISBbits.TRISB5 = 0; //set as OUTPUT
    
    TRISCbits.TRISC0 = 1; //set as INPUT
    TRISCbits.TRISC4 = 0; //set as OUTPUT
    TRISCbits.TRISC5 = 0; //set as OUTPUT
    //ANSELCbits.ANSC0 = 0; //set as DIGITAL

    TRISDbits.TRISD0 = 0; //set as OUTPUT
    TRISDbits.TRISD1 = 0; //set as OUTPUT
    TRISDbits.TRISD2 = 0; //set as OUTPUT
    TRISDbits.TRISD3 = 0; //set as OUTPUT
    TRISDbits.TRISD4 = 0; //set as OUTPUT
    TRISDbits.TRISD5 = 1; //set as INPUT
    TRISDbits.TRISD6 = 1; //set as INPUT
    TRISDbits.TRISD7 = 1; //set as INPUT
    //ANSELDbits.ANSD5 = 0; //set as DIGITAL
    //ANSELDbits.ANSD6 = 0; //set as DIGITAL
    //ANSELDbits.ANSD7 = 0; //set as DIGITAL
    

    TRISEbits.TRISE0 = 1; //set as INPUT
    TRISEbits.TRISE1 = 1; //set as INPUT
    ANSELEbits.ANSE0 = 0; //set as DIGITAL
    ANSELEbits.ANSE1 = 0; //set as DIGITAL
    PORTEbits.RE0 = 0; //set as ViL
    PORTEbits.RE1 = 0; //set as ViL

    TRISFbits.TRISF0 = 0; //set as OUTPUT
    TRISFbits.TRISF1 = 0; //set as OUTPUT
    TRISFbits.TRISF2 = 0; //set as OUTPUT
    TRISFbits.TRISF3 = 0; //set as OUTPUT
    TRISFbits.TRISF4 = 0; //set as OUTPUT
    TRISFbits.TRISF5 = 0; //set as OUTPUT
    TRISFbits.TRISF6 = 1; //set as INPUT
    ANSELFbits.ANSF6 = 0; //set as DIGITAL
    
    TRISGbits.TRISG1 = 0; //set as OUTPUT
    TRISGbits.TRISG2 = 0; //set as OUTPUT

    init_adc();
    init_pwm();

    INTCONbits.GIE = 0b1; //enable interrupt
    INTCONbits.TMR0IE = 0b1;
    INTCONbits.TMR0IF = 0b0;
}


int set_subdivision(int x, int y) {
    //x = delay time
    //y = state
    
    adjust_sub_delay = 0;
    int tmpX = x;
    float scalar = 1.0;

    switch (y) {
        case 1:
            scalar = 2.0; // half note
            break;
        case 2:
            scalar = 0.6666; //quarter triplet
            break;
        case 3:
            scalar = .5; //eight 
            break;
        case 4:
            scalar = 0.3333; //eight triplet
            break;
        case 5:
            scalar = 0.25; //16th
            break;
        case 6:
            x = x; // 1:1 ratio
            break;
    }
    
    tmpX = tmpX * scalar;
    
    if (trunc(tmpX) != tmpX) {
        adjust_sub_delay = 1;
    }

    return tmpX;
}

void init_adc(void) {
    ADCON1bits.ADFM = 0b1; // right justify the output
    ADCON1bits.ADCS = 0b110; // use Fosc/64 for clock source
    ADCON1bits.ADPREF = 0b00; // Vref = Vdd
    ADCON0bits.ADON = 0b1; // turn on the ADC
}

uint16_t adc_convert(uint8_t channel) {
    ADCON0bits.CHS = channel; // select the given channel
    ADCON0bits.GO = 0b1; // start the conversion
    while (ADCON0bits.GO_nDONE); // wait for the conversion to finish
    return (ADRESH << 8) | ADRESL; // return the result
}

void init_pwm(void) {
    APFCONbits.CCP2SEL = 0; //CCP2 is on RC1
    TRISCbits.TRISC2 = 0; //CCP1 pin to output
    TRISCbits.TRISC1 = 0; //CCP2 pin to output
    TRISGbits.TRISG0 = 0; //CCP3 pin to output
    TRISGbits.TRISG3 = 0; //CCP4 pin to output
    TRISGbits.TRISG4 = 0; //CCP5 pin to output
    TRISEbits.TRISE6 = 0; //CCP6 pin to output
    TRISEbits.TRISE5 = 0; //CCP7 pin to output
    TRISEbits.TRISE4 = 0; //CCP8 pin to output
    TRISEbits.TRISE3 = 0; //CCP9 pin to output
    TRISEbits.TRISE2 = 0; //CCP10 pin to output
    CCP1CONbits.CCP1M = 0b1111; // set CCP1 as PWM mode
    CCP2CONbits.CCP2M = 0b1111; // set CCP2 as PWM mode
    CCP3CONbits.CCP3M = 0b1111; // set CCP3 as PWM mode
    CCP4CONbits.CCP4M = 0b1111; // set CCP4 as PWM mode
    CCP5CONbits.CCP5M = 0b1111; // set CCP5 as PWM mode
    CCP6CONbits.CCP6M = 0b1111; // set CCP6 as PWM mode
    CCP7CONbits.CCP7M = 0b1111; // set CCP7 as PWM mode
    CCP8CONbits.CCP8M = 0b1111; // set CCP8 as PWM mode
    CCP9CONbits.CCP9M = 0b1111; // set CCP9 as PWM mode
    CCP10CONbits.CCP10M = 0b1111; // set CCP10 as PWM mode
    CCPTMRS0 = 0b00000000; //set CCP4, CCP3, CCP2, CCP1 to reference Timer2
    CCPTMRS1 = 0b00000000; //set CCP8, CCP7, CCP6, CCP5 to reference Timer2
    CCPTMRS2 = 0b00000000; //set CCP10, CCP9 to reference Timer2
    CCPR1 = 50; //set CCP1 Duty Cycle to 50%
    CCPR2 = 100; //set CCP1 Duty Cycle to 50%
    CCPR3 = 150; //set CCP1 Duty Cycle to 50%
    CCPR4 = 200; //set CCP1 Duty Cycle to 50%
    init_timer2();
    init_timer0();
}

void init_timer2(void) {
    T2CONbits.T2OUTPS = 0b0000;
    T2CONbits.T2CKPS = 0b00;
    PR2 = 0xFF; //set Timer2 max value (16Mhz/4*1*15.67khz)
    T2CONbits.TMR2ON = 1;
}

void init_timer0(void) {
    OPTION_REGbits.TMR0CS = 0b0;
    OPTION_REGbits.PSA = 0b0;
    OPTION_REGbits.PS0 = 0b0;
    OPTION_REGbits.PS1 = 0b1;
    OPTION_REGbits.PS2 = 0b0;
}

float map(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


float scalePotValue(float x, float out_min, float out_max) {
    //The pots have a raw value of 0 to 1023.
    return x * (out_max - out_min) / 1023 + out_min;
}


int scaleA100kPot(double input) {	
    //Scale the pot input to a percentage of 1, then use a curve fit to get PWM
    if (input == 0.0) {input = 1.0;}  //Don't let it go to zero, it creates a div by zero error;
    float pwm = 3.6347 * (pow((input/1023.0), -1.112));
    return (int)(pwm);
}

int scaleiA100kPot(double input) {
    //Scale the pot input to a percentage of 1, then use a curve fit to get PWM
    if (input == 0.0) {input = 1.0;}  //Don't let it go to zero, it creates a div by zero error;
    float pwm = 3.5755 * (pow((input / 1023.0), -1.112));
    return (int)(pwm);
}

int scaleA10kPot(double input) {	
    //Scale the pot input to a percentage of 1, then use a curve fit to get PWM
    if (input == 0.0) {return 255;}  //Don't let it go to zero, it creates a div by zero error;
    if (input == 1023.0) {return 0;} 
    float pwm = 8.7428 * (pow((input/1023.0), -1.222));
    return (int)(pwm);
}


int scaleiA10kPot(double input) {	
    //Reverse the axis for the inverse value
    //Scale the pot input to a percentage of 1, then use a curve fit to get PWM
     if (input == 0.0) {return 0;}  //Don't let it go to zero, it creates a div by zero error;

    if (input == 1023.0) {return 255;}  //Don't let it go to zero, it creates a div by zero error;

    float pwm = 8.7428 * (pow((1-(input/1023.0)), -1.222));
    return (int)(pwm);
}

long modulation(long x, long y) {
    //modulation(mod_value, adjusted_pot_value);
     
    return (127500 + (y * x)) / 1000;
}

void InitializeTaps(void) {
    for (int itap = 0; itap < 12; itap++) {
        tap[itap] = 0;
    }
}

void ReadSavedSettings(void) {
    //Pull startup conditions from FLASH
    top_push_state = FLASH_ReadWord(0x1F81);
    bottom_push_state = FLASH_ReadWord(0x1F82);

    if (top_push_state > 6) {
        //Limit to acceptable values
        top_push_state = 6;
    }
    if (bottom_push_state > 5) {
        //Limit to acceptable values
        bottom_push_state = 1;
    }
    
    //load startup conditions
    Relay_1 = !switchBypass_state;
    Relay_2 = switchBypass_state;
    LED_bypass_A = 0; //bypass_state; //TODO: turned off tap blink for testing
    LED_bypass_B = 0; //!bypass_state; //TODO: turned off tap blink for testing

    LED_tap_A = 0;
    LED_tap_B = 0;

    LED_bypass_Aux = 0; //right
    LED_tap_Aux = 0; //left


    set_leds_top(top_push_state, 1);
    set_leds_bottom(bottom_push_state);
}