/* 
 * File:   modulation.h
 * Author: Nancy
 *
 * Created on October 9, 2016, 5:21 PM
 */

#ifndef MODULATION_H
#define	MODULATION_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* MODULATION_H */


void updateModulationArray(void);
void calcCosArray(void);
int getModulationSubdivision(void);
void getModulationDelayTime(void);

int modCos(double, double);
int modTri(double, double);
int modSaw(double, double);
int modSawRev(double, double);
int modSquare(double, double);
