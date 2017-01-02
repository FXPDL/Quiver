
/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#endif


#include "state_manager.h"
#include "constants.h"
#include "preset_programming.h"

                       


void setDoublePressState(int f_state) {
    if (doubleTap_state == f_state) {return;}
    doubleTap_state = f_state;
    if (f_state == 1) {
        LED_tap_A = 0;
        LED_bypass_A = 0;
        LED_tap_B = 0;
        LED_bypass_B = 0;
    }
    
    LED_bypass_Aux = f_state;
    LED_tap_Aux = f_state;
    
    wait_ms(relay_delay);
    
}
 