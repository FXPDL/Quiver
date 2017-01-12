
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

void calcSinArray(void) {
    for (char iAngle = 0; iAngle < 120; iAngle++) {
        double tmpVal = 3 * iAngle * M_PI/180.0;
        tmpVal = sin(tmpVal);
        sinArray[iAngle] = tmpVal;
    }
    char x = 1;
}
/*
void updateModulationArray(void) {
    
    for (char iAngle = 0; iAngle< 60; iAngle++) {
        int thisAngle = 6 * iAngle;
        switch (bottom_push_state) {
            case 1: //Sin
                modArray[iAngle] = modSin(thisAngle, symmetry); 
                break;
            case 2: //tri
                modArray[iAngle] = modTri(thisAngle, symmetry); 
                break;
            case 3: //Square
                modArray[iAngle] = modSquare(thisAngle, symmetry);
                break;
            case 4: //Saw
                modArray[iAngle] = modTri(thisAngle, symmetry); 
                break;
            case 5: //Reverse Saw
                modArray[iAngle] = modTri(thisAngle, symmetry);            
                break;
            default:
                modArray[iAngle] = 0;
                break;
        }
    }
    char x = 1;
}*/

int modSin(double angle, double inflection) {
    double period = 1.0;
    double shift = 0.0;
    
    if(angle<=inflection) {
        period = 180.0/inflection;
    } else {
        shift = -(360-inflection*2)*(180/(360-inflection));
        period = 180/(360-inflection);  
        
    }
    double tmpVal = (period*angle-shift) /3;
    tmpVal = sinArray[(int)(tmpVal)]; // sin(tmpVal);
    return (int)(100.0 * tmpVal); //(int)trunc(100.0 * sin((period*angle-shift) * M_PI/180.0));   
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
    if (tmpVal > 270) {
        tmpVal = tmpVal - 360.0;
    } else if (tmpVal > 90) {
        tmpVal = 180 - tmpVal;
    } 
    tmpVal = tmpVal * 10/9;  //tmpVal * M_PI/180.0 * 200.0/M_PI;

    return (int)(tmpVal);    
}


int modSaw(double angle, double inflection) {
    double period = 1.0;
    double shift = 0;
    
    if(angle<=inflection) {
        period = 180.0/inflection;
    } else {
        shift = -(360-inflection*2)*(180/(360-inflection)) + 360;
        period = 180/(360-inflection);  
    }

    //int mod = (int)(-200.0/M_PI * atan(cot(((period*angle-shift)* M_PI/180.0 + M_PI)/2 )));
    int mod = (int)((period*angle-shift)*5/9);
    return mod;   
}

int modSawRev(double angle, double inflection) {
    return -1 * modSaw(angle, inflection);
}


//=SIGN(SIN(F2*RADIANS(H2)-RADIANS(G2)))*100
int modSquare(double angle, double inflection) {
    int tmpVal = modSin(angle, inflection);
    return (tmpVal > 0 ? 100 : -100);
    //return (angle <= inflection) ? 100 : -100;
}


