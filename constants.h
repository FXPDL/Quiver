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
#define exp_mode PORTAbits.RA4   //Slide switch: 0 = expression mode (top of pedal) / 1 = tap mode (bottom of pedal))
#define mode_2 PORTCbits.RC0
#define mode_1 PORTDbits.RD7
#define chorus PORTCbits.RC4
#define expJackInput PORTFbits.RF6


#define relay_delay   20  //milliseconds
#define debounce_limit  25
#define tap_reset  1563

 

volatile long timer = 0;
volatile long sub_timer = 0;
volatile uint16_t longBypass_timer = 0;
volatile uint16_t longTap_timer = 0;


uint16_t long_press_limit = 1000; 
volatile long baseline_mod_time = 2000;

uint8_t longBypass_start = 0;
uint8_t longTap_start = 0;
volatile uint8_t doubleTap_state = 0;
uint8_t mode1_state = 0;
uint8_t mode2_state = 0;
uint8_t blink_state = 1;

volatile uint8_t suspend_blink =  0;  //Stop the tap blink for debugging

uint8_t preset_programmning_on = 0;
uint8_t preset_blink = 0;

int blink_delay = 100;

int top_push_state = 6;
int bottom_push_state = 1;

uint16_t myBuf[ERASE_FLASH_BLOCKSIZE];

char modulation_changed = 0;
char mod_time_changed = 1;
char reset_sub_delay = 0;
char adjust_mod_delay = 0;

int tmpModDelay = 0;


long tap[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int debounce_count = 0;
int debounce_bypass = 0;
int debounce_mode1 = 0;
int debounce_mode2 = 0;

volatile long tap_timer = 0;
volatile long double_timer = 0;

char presetSaveMode = 0;
char presetChannel = 1;
char expressionChannel = 1;

char switchBypass_state = -1; //initialize to an invalid value so the initialize will run.
char switchTap_state = -1; //initialize to an invalid value so the initialize will run.
volatile char longTap_state = -1; //initialize to an invalid value so the initialize will run.
volatile char longBypass_state = 0; //initialize to an invalid value so the initialize will run.

char expSwitchState = -1; 

char presetModeCnst = 1;
char expressModeCnst = 2;

//int delayArray[260] = {2082, 2044, 2008, 1973, 1939, 1906, 1874, 1844, 1814, 1785, 1757, 1730, 1704, 1679, 1654, 1630, 1607, 1584, 1562, 1541, 1520, 1500, 1480, 1461, 1443, 1424, 1407, 1389, 1372, 1356, 1340, 1324, 1309, 1294, 1279, 1265, 1250, 1237, 1223, 1210, 1197, 1185, 1172, 1160, 1149, 1137, 1126, 1114, 1104, 1093, 1082, 1072, 1062, 1052, 1042, 1033, 1023, 1014, 1005, 996, 988, 979, 971, 962, 954, 946, 938, 930, 923, 915, 908, 901, 894, 887, 880, 873, 866, 860, 853, 847, 840, 834, 828, 822, 816, 810, 804, 799, 793, 787, 782, 777, 771, 766, 761, 756, 751, 746, 741, 736, 731, 727, 722, 717, 713, 708, 704, 700, 695, 691, 687, 683, 678, 674, 670, 666, 663, 659, 655, 651, 647, 644, 640, 636, 633, 629, 626, 622, 619, 615, 612, 609, 606, 602, 599, 596, 593, 590, 587, 584, 581, 578, 575, 572, 569, 566, 563, 560, 558, 555, 552, 549, 547, 544, 542, 539, 536, 534, 531, 529, 526, 524, 522, 519, 517, 514, 512, 510, 507, 505, 503, 501, 498, 496, 494, 492, 490, 488, 486, 483, 481, 479, 477, 475, 473, 471, 469, 467, 466, 464, 462, 460, 458, 456, 454, 452, 451, 449, 447, 445, 444, 442, 440, 438, 437, 435, 433, 432, 430, 428, 427, 425, 424, 422, 420, 419, 417, 416, 414, 413, 411, 410, 408, 407, 405, 404, 402, 401, 400, 398, 397, 395, 394, 393, 391, 390, 389, 387, 386, 385, 383, 382, 381, 379, 378, 377, 376, 374, 373, 372, 371, 369, 368, 367, 366};
//60 int modArray[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  
//120 samples
int modArray[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  
double sinArray[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  

int symmetry = 180;