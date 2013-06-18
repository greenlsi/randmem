/*
 * =====================================================================================
 *
 *       Filename:  memory.c
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

#include "memory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdint.h>
#include <malloc.h>

// Random RW Integer
int testJIR(int jmax, int arraymax, int *xi)    
{
    int i, j;
    int toti;
    
    start_time();
    
    for (j=0; j<jmax; j++)
    {
        toti = 0;
        for (i=0; i<arraymax; i=i+32)
        {
            xi[xi[i+28]] = xi[xi[i+30]];
            xi[xi[i+24]] = xi[xi[i+26]];
            xi[xi[i+20]] = xi[xi[i+22]];
            xi[xi[i+16]] = xi[xi[i+18]];
            xi[xi[i+12]] = xi[xi[i+14]];
            xi[xi[i+ 8]] = xi[xi[i+10]];
            xi[xi[i+ 4]] = xi[xi[i+ 6]];
            xi[xi[i+ 0]] = xi[xi[i+ 2]];
        }
    }
    end_time();
        
    return toti;
}

// Serial RW Integer
int testJI(int jmax, int arraymax, int *xi)    
{
    int i, j;
    int toti;
    
    start_time();

    
    for (j=0; j<jmax; j++)
    {
        toti = 0;
        for (i=0; i<arraymax; i=i+32)
        {
            xi[xi[i+ 2]] = xi[xi[i+ 0]];
            xi[xi[i+ 6]] = xi[xi[i+ 4]];
            xi[xi[i+10]] = xi[xi[i+ 8]];
            xi[xi[i+14]] = xi[xi[i+12]];
            xi[xi[i+18]] = xi[xi[i+16]];
            xi[xi[i+22]] = xi[xi[i+20]];
            xi[xi[i+26]] = xi[xi[i+24]];
            xi[xi[i+30]] = xi[xi[i+28]];
        }
    }
    end_time();
        

    return toti;
}

int testIIR(int jmax, int arraymax, int *xi)    
{
    int i, j;
    int toti;
    
    start_time();
    
    for (j=0; j<jmax; j++)
    {
        toti = 0;
        for (i=0; i<arraymax; i=i+32)
        {
            toti = toti & xi[xi[i+30]] | xi[xi[i+28]]
                        & xi[xi[i+26]] | xi[xi[i+24]]
                        & xi[xi[i+22]] | xi[xi[i+20]]
                        & xi[xi[i+18]] | xi[xi[i+16]]
                        & xi[xi[i+14]] | xi[xi[i+12]]
                        & xi[xi[i+10]] | xi[xi[i+ 8]]
                        & xi[xi[i+ 6]] | xi[xi[i+ 4]]
                        & xi[xi[i+ 2]] | xi[xi[i+ 0]];
        }
    }
    end_time();
        
    return toti;
}

int testII(int jmax, int arraymax, int *xi)    
{
    int i, j;
    int toti;
    
    start_time();
    
    for (j=0; j<jmax; j++)
    {
        toti = 0;
        for (i=0; i<arraymax; i=i+32)
        {
            toti = toti & xi[xi[i+ 0]] | xi[xi[i+ 2]]
                        & xi[xi[i+ 4]] | xi[xi[i+ 6]]
                        & xi[xi[i+ 8]] | xi[xi[i+10]]
                        & xi[xi[i+12]] | xi[xi[i+14]]
                        & xi[xi[i+16]] | xi[xi[i+18]]
                        & xi[xi[i+20]] | xi[xi[i+22]]
                        & xi[xi[i+24]] | xi[xi[i+26]]
                        & xi[xi[i+28]] | xi[xi[i+30]];
        }
    }
    end_time();
        
    return toti;
}

double testJDR(int jmax, int darraymax, int *xi, double *xd)    
{
    int i, j;
    double totd;
        

    start_time();
    
    for (j=0; j<jmax; j++)
    {
        totd = 0.0;
        for (i=0; i<darraymax; i=i+16)
        {
            xd[xi[i+14]] = xd[xi[i+15]];
            xd[xi[i+12]] = xd[xi[i+13]];
            xd[xi[i+10]] = xd[xi[i+11]];
            xd[xi[i+ 8]] = xd[xi[i+ 9]];
            xd[xi[i+ 6]] = xd[xi[i+ 7]];
            xd[xi[i+ 4]] = xd[xi[i+ 5]];
            xd[xi[i+ 2]] = xd[xi[i+ 3]];
            xd[xi[i+ 0]] = xd[xi[i+ 1]];
        }
    }
    end_time();

    return totd;
}

double testJD(int jmax, int darraymax, int *xi, double *xd)    
{

    int i, j;
    double totd;
        
    start_time();
    
    for (j=0; j<jmax; j++)
    {
        totd = 0.0;
        for (i=0; i<darraymax; i=i+16)
        {
            xd[xi[i+ 1]] = xd[xi[i+ 0]];
            xd[xi[i+ 3]] = xd[xi[i+ 2]];
            xd[xi[i+ 5]] = xd[xi[i+ 4]];
            xd[xi[i+ 7]] = xd[xi[i+ 6]];
            xd[xi[i+ 9]] = xd[xi[i+ 8]];
            xd[xi[i+11]] = xd[xi[i+10]];
            xd[xi[i+13]] = xd[xi[i+12]];
            xd[xi[i+15]] = xd[xi[i+14]];
        }
    }
    end_time();

    return totd;
}

double testIDR(int jmax, int darraymax, int *xi, double *xd)    
{
    int i, j;
    double totd;
        
    start_time();
    
    for (j=0; j<jmax; j++)
    {
        totd = 0.0;
        for (i=0; i<darraymax; i=i+16)
        {
            totd = totd + xd[xi[i+15]] * xd[xi[i+14]]
                        - xd[xi[i+13]] * xd[xi[i+12]]
                        + xd[xi[i+11]] * xd[xi[i+10]]
                        - xd[xi[i+ 9]] * xd[xi[i+ 8]]
                        + xd[xi[i+ 7]] * xd[xi[i+ 6]]
                        - xd[xi[i+ 5]] * xd[xi[i+ 4]]
                        + xd[xi[i+ 3]] * xd[xi[i+ 2]]
                        - xd[xi[i+ 1]] * xd[xi[i+ 0]];
        }

    }
    end_time();

    return totd;
}

double testID(int jmax, int darraymax, int *xi, double *xd)    
{
    int i, j;
    double totd;
        
    start_time();
    
    for (j=0; j<jmax; j++)
    {
        totd = 0.0;
        for (i=0; i<darraymax; i=i+16)
        {
            totd = totd + xd[xi[i+ 0]] * xd[xi[i+ 1]]
                        - xd[xi[i+ 2]] * xd[xi[i+ 3]]
                        + xd[xi[i+ 4]] * xd[xi[i+ 5]]
                        - xd[xi[i+ 6]] * xd[xi[i+ 7]]
                        + xd[xi[i+ 8]] * xd[xi[i+ 9]]
                        - xd[xi[i+10]] * xd[xi[i+11]]
                        + xd[xi[i+12]] * xd[xi[i+13]]
                        - xd[xi[i+14]] * xd[xi[i+15]];
        }
    }
    end_time();

    return totd;
}

int checkTime(int jmax)
{
    if (secs < runTime) {
        if (secs < runTime / 8.0) {
            jmax = jmax * 10;
        }
        else {
            jmax = (int)(runTime * 1.25 / secs * (double)jmax+1);
        }
    }
    return jmax;
}

double execute_integer_benchmark( int arraysize, int *xi, int numexecs)
{
    int i, g, k ;
    int jmax;
    int toti;
    double totd, results=0;
    double sbytes;
    double mega = 1024.0 * 1024.0;

    //Integer benchmarks
        
    // Serial Read Integer *********************
    if ((serial == 1) && (read == 1) ){
        for (i=0; i<arraysize+1; i++) {
            xi[i] = i+1;
        }
        jmax = 1;
        sbytes = 4.0;
        for (k=0; k< numexecs; k++) {
            do {
                toti = testII(jmax, arraysize, xi);
                jmax = checkTime(jmax);   
            } while (secs < runTime);
            results +=  (double)arraysize * (double)jmax * sbytes / mega / secs;
        }
    } 

    // Serial Read/Write Integer *********************
    if ((serial == 1) && (read == 0) ){

        for (i=0; i<arraysize+1; i++) {
            xi[i] = i+1;
        }
        jmax = 1;
        sbytes = 4.0;
        for (k=0; k< numexecs; k++) {
            do {
                toti = testJI(jmax, arraysize, xi);    
                jmax = checkTime(jmax);   
            } while (secs < runTime);
            results +=  (double)arraysize * (double)jmax * sbytes / mega / secs;
        }
    }

    // Random Read Integer *********************
    if ((serial == 0) && (read == 1) ){
        srand(123);
        for (i=0; i<arraysize+1; i++) {
           xi[i] = (int)((double)arraysize * ((double)(rand()) / (double)2147483648.0));
        }

        jmax = 1;
        sbytes = 4.0;
        for (k=0; k< numexecs; k++) {
            do {
                toti = testIIR(jmax, arraysize, xi);    
                jmax = checkTime(jmax);   
            } while (secs < runTime);
            results +=  (double)arraysize * (double)jmax * sbytes / mega / secs;
        }
    }

    // Random Read/Write Integer *********************
    if ((serial == 0) && (read == 0) ){
        srand(123);
        for (i=0; i<arraysize+1; i++) {
           xi[i] = (int)((double)arraysize * ((double)(rand()) / (double)2147483648.0));
        }

        jmax = 1;
        sbytes = 4.0;
        for (k=0; k< numexecs; k++) {
            do {
                toti = testJIR(jmax, arraysize, xi);    
                jmax = checkTime(jmax);   
            } while (secs < runTime);
            results +=  (double)arraysize * (double)jmax * sbytes / mega / secs;
        }

    }

    return results/numexecs;
}

//XXX-marina: change here
double execute_intfp_benchmark( int arraysize, int *xi, double *xd, int numexecs )
{
    int i, g, k ;
    int jmax;
    int toti;
    double totd, results;
    double sbytes;
    double mega = 1024.0 * 1024.0;
    int darraymax ;
    
    // Double benchmarks

    // Serial Read Double *********************
    if ((serial == 1) && (read == 1) ){
        for (i=0; i<darraymax+1; i++) {
            xd[i] = 1.0;
            xi[i] = i+1;
        }
        jmax = 1;
        sbytes = 12.0;
        for (k=0; k< numexecs; k++) {
            do {
                totd = testID(jmax, darraymax, xi, xd);       
                jmax = checkTime(jmax);   
            } while (secs < runTime);
            results +=  (double)darraymax * (double)jmax * sbytes / mega / secs;
        }
    }
        
    // Serial Read/Write Double *********************
    if ((serial == 1) && (read == 0) ){
        for (i=0; i<darraymax+1; i++) {
            xd[i] = 1.0;
            xi[i] = i+1;
        }
        jmax = 1;
        sbytes = 12.0;
        for (k=0; k< numexecs; k++) {
            do {
                totd = testJD(jmax, darraymax, xi, xd);    
                jmax = checkTime(jmax);   
            } while (secs < runTime);
            results +=  (double)darraymax * (double)jmax * sbytes / mega / secs;
        }
    }

    // Random Read Double *********************
    if ((serial == 0) && (read == 1) ){
        srand(123);
        for (i=0; i<darraymax+1; i++) {
            xi[i] = (int)((double)darraymax * ((double)(rand()) / (double)2147483648.0));
            xd[i] = 1.0;
        }

        jmax = 1;
        sbytes = 12.0;    
        for (k=0; k< numexecs; k++) {
            do {
                totd = testIDR(jmax, darraymax, xi, xd); 
                jmax = checkTime(jmax);   
            } while (secs < runTime);
            results +=  (double)darraymax * (double)jmax * sbytes / mega / secs;
        }
    }

    // Random Read/Write Double *********************
    if ((serial == 0) && (read == 0) ){
        srand(123);
        for (i=0; i<darraymax+1; i++) {
            xi[i] = (int)((double)darraymax * ((double)(rand()) / (double)2147483648.0));
        }

        jmax = 1;
        sbytes = 12.0;    
        for (k=0; k< numexecs; k++) {
            do {
                totd = testJDR(jmax, darraymax, xi, xd); 
                jmax = checkTime(jmax);   
            } while (secs < runTime);
            results +=  (double)darraymax * (double)jmax * sbytes / mega / secs;
        }
    }

    return results/numexecs;
}


