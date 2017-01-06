/* 
 * File:   MIDI.h
 * Author: Nancy
 *
 * Created on January 4, 2017, 4:12 PM
 */

#ifndef MIDI_H
#define	MIDI_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* MIDI_H */

#include <stdint.h>        /* For uint8_t definition */      
#include <stdbool.h>       /* For true/false definition */
#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "constants.h"

char UART_Init(const long int) ;
void InitializeMIDI(void);