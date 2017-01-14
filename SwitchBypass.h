/* 
 * File:   SwitchBypass.h
 * Author: Nancy
 *
 * Created on October 15, 2016, 6:41 PM
 */

#ifndef SWITCHBYPASS_H
#define	SWITCHBYPASS_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* SWITCHBYPASS_H */

#include <stdint.h>        /* For uint8_t definition */
#include "system.h"


void initSwitchBypass(void);
void updateSwitchBypass(void);
void setSwitchBypassState(int);
void setLongBypassState(int);
