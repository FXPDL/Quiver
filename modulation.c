
#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>
#include <math.h>        /* For true/false definition */
#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "modulation.h"


int modSin(double angle, double inflection) {
    double period = 1.0;
    double shift = 0;
    
    if(angle<=inflection) {
        period = 180.0/inflection;
    } else {
        shift = -(360-inflection*2)*(180/(360-inflection));
        period = 180/(360-inflection);  
        
    }

    return (int)trunc(100.0 * sin((period*angle-shift) * M_PI/180.0));   
}

int modTri(double angle, double inflection) {
    double period = 1.0;
    double shift = 0;
    
    if(angle<=inflection) {
        period = 180.0/inflection;
    } else {
        shift = -(360-inflection*2)*(180/(360-inflection));
        period = 180/(360-inflection);  
        
    }

    return (int)trunc(200.0/M_PI * asin(sin((period*angle-shift) * M_PI/180.0)));   
}


int modSaw(double angle, double inflection) {
    double period = 1.0;
    double shift = 0;
    
    if(angle<=inflection) {
        period = 180.0/inflection;
    } else {
        shift = -(360-inflection*2)*(180/(360-inflection));
        period = 180/(360-inflection);  
    }


    int mod = (int)trunc(-200.0/M_PI * atan(cot(((period*angle-shift)* M_PI/180.0 + M_PI)/2 )));
    return mod;   
}

int modSawRev(double angle, double inflection) {
    return -1 * modSaw(angle, inflection);
}


//=SIGN(SIN(F2*RADIANS(H2)-RADIANS(G2)))*100
int modSquare(double angle, double inflection) {
    return (int)sign(modSin(angle, inflection))*100;   
}



double cot(double d) {
  return (1 / tan(d));
}

int sign(double d) {
   return (d > 0) ? 1 : ((d < 0) ? -1 : 0);
}