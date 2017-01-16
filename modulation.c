
#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>
#include <math.h>
#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "constants.h"
#include "modulation.h"

extern volatile long delay_time;
extern int mod_delay_time;

void calcCosArray(void) {
    for (char iAngle = 0; iAngle < 120; iAngle++) {
        double tmpVal = 3 * iAngle * M_PI/180.0;
        tmpVal = cos(tmpVal);
        cosArray[iAngle] = tmpVal;
    }
}

int getModulationSubdivision(void) {
    if (delay_time >= 2400) {
        return 120;
    } else if (delay_time >= 600) {
        return 60;
    } else {
        return 30;
    }
}
void getModulationDelayTime(void) {
    adjust_mod_delay = 0;
    int subDiv = getModulationSubdivision();
    mod_delay_time = (int)((float)delay_time/(float)subDiv);
//    if ((mod_delay_time * subDiv) != delay_time) {
//        adjust_mod_delay = 1;
//    }
}

void updateModulationArray(void) {
    int subDiv = getModulationSubdivision();    
    if (modArray[120] == bottom_push_state && modArray[121] == symmetry && modArray[122] == subDiv) {
        //array params haven't changed.
        return;
    }

    int angleFactor = 360/subDiv;
    for (char iAngle = 0; iAngle < subDiv; iAngle++) {
        int thisAngle = angleFactor * iAngle;
        switch (bottom_push_state) {
            case 1: //Sin
                modArray[iAngle] = modCos(thisAngle, symmetry); 
                break;
            case 2: //tri
                modArray[iAngle] = modTri(thisAngle, symmetry); 
                break;
            case 3: //Square
                modArray[iAngle] = modSquare(thisAngle, symmetry);
                break;
            case 4: //Saw
                modArray[iAngle] = modSawRev(thisAngle, symmetry); 
                break;
            case 5: //Reverse Saw
                modArray[iAngle] = modSaw(thisAngle, symmetry);            
                break;
            default:
                modArray[iAngle] = 0;
                break;
        }
    }
    for (char iAngle = subDiv; iAngle < 120; iAngle++) {
       modArray[iAngle] = 0 ; 
    }
    modArray[120] = bottom_push_state;
    modArray[121] = symmetry;
    modArray[122] = subDiv;
}

int modCos(double angle, double inflection) {
    double period = 1.0;
    double shift = 0.0;
    
    if(angle<=inflection) {
        period = 180.0/inflection;
    } else {
        shift = -(360-inflection*2)*(180/(360-inflection));
        period = 180/(360-inflection);  
        
    }
    double tmpVal = (period*angle-shift) /3;
    tmpVal = cosArray[(int)(tmpVal)]; 
    return (int)(-100.0 * tmpVal);
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
    double tmpVal = (period*angle-shift) ;//* M_PI/180.0;
    if (tmpVal > 180) {
        tmpVal = tmpVal - 270.0;
    } else {
        tmpVal = 90 - tmpVal;
    } 
    tmpVal = tmpVal * -10/9;  
    
    return (int)(tmpVal);    
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

    int mod = (int)((period*angle-shift-180)*5/9);
    return mod;   
}

int modSawRev(double angle, double inflection) {
    return -1 * modSaw(angle, inflection);
}


int modSquare(double angle, double inflection) {
    int tmpVal = modCos(angle, inflection);
    return (angle <= inflection) ? -100 : 100;
}


