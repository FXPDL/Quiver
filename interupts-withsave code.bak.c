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
#include "user.h"          /* User funct/params, such as InitApp */


/******************************************************************************/
/* Interrupt Routines                                                         */

/******************************************************************************/

void interrupt isr(void) {
    extern volatile long clock;
    extern volatile long timer;
    extern volatile long sub_timer;
    extern volatile long tap_timer;
    extern volatile long mod_timer;
    extern volatile long tap_longpress_timer;
    extern volatile long baseline_delay_time;
    extern volatile long bypass_flash_timer;
    extern volatile long delay_time;
    extern volatile int top_push_state;
    extern volatile int saving_state;
    extern volatile int flash_saving;
    extern volatile int bypass_state;
    extern volatile long tap_ended;
    extern volatile int temp_tap_count;
       
    if (INTCONbits.TMR0IF == 1) {
        clock++;
        timer = timer + 1;
        sub_timer = sub_timer + 1;
        tap_timer = tap_timer + 1;
        mod_timer = mod_timer + 1;
        bypass_flash_timer++;
        tap_longpress_timer++;
        INTCONbits.TMR0IF = 0;
    }

/*    if (((clock - tap_ended) > 500) && temp_tap_count > 0) {
        temp_tap_count = 0;
        tap_ended = 0;
    }*/


    if (timer >= baseline_delay_time) { //delay_time
        LATFbits.LATF5 = 1;
        timer = 0;
    }

    if (timer >= 20) { //delay_time
        LATFbits.LATF5 = 0;
    }
    
    if (sub_timer >= delay_time) { //sub_delay_time
        set_leds_top(top_push_state, 1);
        sub_timer = 0;
    }

    if (sub_timer >= 20) { //delay_time
        set_leds_top(top_push_state, 0);
    }

    /*if (saving_state == 1 && flash_saving == 0) {
        flash_saving = 1;
        LATFbits.LATF6 = 1;
        bypass_flash_timer = 0;
    }
    if (flash_saving > 0 && flash_saving < 11) {
        if (bypass_flash_timer > 100) { //delay_time
            flash_saving++;
            if (LATFbits.LATF6 == 1) {
                LATFbits.LATF6 = 0;
            } else {
                LATFbits.LATF6 = 1;
            }
            bypass_flash_timer = 0;
        }
    } else if (flash_saving >= 11) {
        LATFbits.LATF6 = bypass_state;
    }*/

}


