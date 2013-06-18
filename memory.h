/*
 * =====================================================================================
 *
 *       Filename:  memory.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/04/13 21:41:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Marina Zapater (), marina@die.upm.es
 *   Organization:  GreenLSI
 *
 * =====================================================================================
 */
#ifndef _MEMORY_HH_
#define _MEMORY_HH_

#include "cpuidh.h"
#include "main_defs.h"

int     randNumbers;
int     randMax;
char    startRam[200];
char    test[20];
char    type[20];
char    memsize[20];

int    testII(int jmax, int arraymax, int *xi);
int    testIIR(int jmax, int arraymax, int *xi);
// Serial RW Integer
int    testJI(int jmax, int arraymax, int *xi);    
// Random RW Integer
int    testJIR(int jmax, int arraymax, int *xi);    
   
double testID(int jmax, int arraymax, int *xi, double *xd);    
double testIDR(int jmax, int arraymax, int *xi, double *xd);    
double testJD(int jmax, int arraymax, int *xi, double *xd);    
double testJDR(int jmax, int arraymax, int *xi, double *xd);    

int checkTime(int jmax);

double execute_integer_benchmark( int arraysize, int *xi, int numexecs );
double execute_intfp_benchmark( int arraysize, int *xi, double *xd, int numexecs );

#endif // _MEMORY_H_
