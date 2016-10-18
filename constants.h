/* 
 * File:   constants.h
 * Author: Nancy
 *
 * Created on October 9, 2016, 7:08 PM
 */

#ifndef CONSTANTS_H
#define	CONSTANTS_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* CONSTANTS_H */

#include <stdint.h>        /* For uint8_t definition */      
#include <stdbool.h>       /* For true/false definition */
#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "memory.h"



#define bottom_tactile PORTDbits.RD6
#define top_tactile PORTDbits.RD5
#define LED_tap_A LATBbits.LATB4
#define LED_tap_B LATBbits.LATB5
#define LED_bypass_A LATBbits.LATB2
#define LED_bypass_B LATBbits.LATB3
#define LED_bypass_Aux LATBbits.LATB1
#define LED_tap_Aux LATBbits.LATB0
#define Relay_1 LATGbits.LATG1
#define Relay_2 LATGbits.LATG2
#define switch_bypass PORTEbits.RE1
#define switch_tap PORTEbits.RE0
#define exp_mode PORTAbits.RA4
#define mode_2 PORTCbits.RC0
#define mode_1 PORTDbits.RD7
#define chorus PORTCbits.RC4

#define relay_delay   20  //milliseconds
#define debounce_limit  25


volatile long timer = 0;
volatile long sub_timer = 0;
volatile uint16_t feedback_timer = 0;

uint16_t long_press_limit = 1000; 
volatile long baseline_delay_time = 2000;

uint8_t feedback_start = 0;
uint8_t mode1_state = 0;
uint8_t mode2_state = 0;
uint8_t blink_state = 1;

volatile uint8_t suspend_blink =  0;  //Stop the tap blink for debugging

uint8_t preset_programmning_on = 0;
uint8_t preset_blink = 0;

int blink_delay = 100;

int top_push_state = 6;
int bottom_push_state = 6;

uint16_t myBuf[ERASE_FLASH_BLOCKSIZE];

int delay_time_changed = 1;

long tap[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int debounce_count = 0;
int debounce_bypass = 0;
int debounce_mode1 = 0;
int debounce_mode2 = 0;

volatile long tap_timer;

uint8_t switchBypass_state = -1; //initialize to an invalid value so the initialize will run.
uint8_t switchTap_state = -1; //initialize to an invalid value so the initialize will run.
