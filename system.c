/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"

/* Refer to the device datasheet for information about available
oscillator configurations. */
void ConfigureOscillator(void)
{
    OSCCONbits.SCS = 0b00; 
}

void wait_ms(uint16_t timeSec)
{
    long timemsl = 0;
    timemsl = timeSec * 1000l;
    for( ; timemsl; timemsl--);// no initial condition, while time is >0, decrement time each loop
}