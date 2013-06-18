/* 
 gcc randmem.c cpuidc.o cpuida.o -lrt -lc -lm -O3 -o randmem32
 ./randmem32

  gcc randmem.c cpuidc64.o cpuida64.o -m64 -lrt -lc -lm -O3 -o randmem64
 ./randmem64

 * RandMem Benchmark Version 2 Copyright (c) Roy Longbottom 2010 
 *
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "cpuidh.h"
 #include <math.h>
 #include <malloc.h>
 #include <mm_malloc.h>


int    testII(int jmax, int arraymax);
int    testIIR(int jmax, int arraymax);
int    testJI(int jmax, int arraymax);    
int    testJIR(int jmax, int arraymax);    
   
double testID(int jmax, int arraymax);    
double testIDR(int jmax, int arraymax);    
double testJD(int jmax, int arraymax);    
double testJDR(int jmax, int arraymax);    

int checkTime(int jmax);

// ************* GLOBAL VARIABLES **********
 
int    * xi;
double * xd;

  #define version  "64 Bit Version 2"
//  #define version  "32 Bit Version 2"

double results[100][10];


double   runTime = 0.1; // 100 ms;


unsigned int  ramKB;
unsigned int  ramKBused;
int  arraymax;
int  arraymax1;
int  darraymax;
int  passes = 1;
int  passesDone;
int   randNumbers;
int   randMax;
char  startRam[200];



int testJIR(int jmax, int arraymax)    
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

int testJI(int jmax, int arraymax)    
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

int testIIR(int jmax, int arraymax)    
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

int testII(int jmax, int arraymax)    
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

double testJDR(int jmax, int darraymax)    
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

double testJD(int jmax, int darraymax)    
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

double testIDR(int jmax, int darraymax)    
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

double testID(int jmax, int darraymax)    
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


int main()
{
    int i, g, k;
    int jmax;
    int toti;
    double totd;
    double sbytes;
    double mega = 1024.0 * 1024.0;
    FILE    *outfile;

    getDetails();

    ramKB = (unsigned int)(ramGB * 1000000);
    arraymax = 1536;
    arraymax1 = arraymax;
    passes = 11;
    if (ramGB >  0.029) passes = 12;
    if (ramGB >  0.058) passes = 13;
    if (ramGB >  0.116) passes = 14;
    if (ramGB >  0.232) passes = 15;
    if (ramGB >  0.464) passes = 16;
    if (ramGB >  0.928) passes = 17;
    if (ramGB >  1.856) passes = 18;
    if (ramGB >  3.712) passes = 19;


    outfile = fopen("RandMem.txt","a+");
    if (outfile == NULL)
    {
        printf ("Cannot open results file \n\n");
        printf(" Press Enter\n");
        g  = getchar();
        exit (0);
    }

    printf("\n");
    for (i=1; i<10; i++)
    {
        printf("%s\n", configdata[i]);
    }
    printf("\n");
    fprintf (outfile, " #####################################################################\n\n");                     
    for (i=1; i<10; i++)
    {
        fprintf(outfile, "%s \n", configdata[i]);
    }
    fprintf (outfile, "\n\n");
 
               printf(" #####################################################\n"); 
    fprintf (outfile, " #####################################################################\n\n");                     


    local_time();
    printf("\n   Random/Serial Memory Test %s %s \n", version, timeday);
    printf("         Integer.......................  Double/Integer................\n");
    printf("         Serial........  Random........  Serial........  Random........\n");
    printf("    RAM   Read   Rd/Wrt   Read   Rd/Wrt   Read   Rd/Wrt   Read   Rd/Wrt\n");
    printf("     KB  MB/Sec  MB/Sec  MB/Sec  MB/Sec  MB/Sec  MB/Sec  MB/Sec  MB/Sec\n\n");
  
    fprintf(outfile, "\n   Random/Serial Memory Test %s %s \n", version, timeday);
    fprintf(outfile, "                    Copyright (C) 2010, Roy Longbottom\n\n");

    fprintf(outfile, "         Integer.......................  Double/Integer................\n");
    fprintf(outfile, "         Serial........  Random........  Serial........  Random........\n");
    fprintf(outfile, "    RAM   Read   Rd/Wrt   Read   Rd/Wrt   Read   Rd/Wrt   Read   Rd/Wrt\n");
    fprintf(outfile, "     KB  MB/Sec  MB/Sec  MB/Sec  MB/Sec  MB/Sec  MB/Sec  MB/Sec  MB/Sec\n\n");
    fflush(outfile);
    
    passesDone = 0;
    for (k=0; k<passes; k++) // 11
    {
        for (i=0; i<10; i++)
        {
            results[k][i] = 0;
        }
    }
    for (k=0; k<passes; k++) // 11
    {
        passesDone = k + 1;
        printf("%7d ", arraymax * 4 / 1024);
        fprintf(outfile,  "%7d ", arraymax * 4 / 1024);

        xi = (int *)_mm_malloc(arraymax * 4 + 8, 16);
        if (xi == NULL)
        {
           printf(" ERROR WILL EXIT\n");
           printf(" Press Enter\n");
           g  = getchar();
           exit(1);
        }
    
        // Serial Read Integer *********************

        for (i=0; i<arraymax+1; i++)
        {
            xi[i] = i+1;
        }
        jmax = 1;
        sbytes = 4.0;
        do
        {
            toti = testII(jmax, arraymax);
            jmax = checkTime(jmax);   
        }
        while (secs < runTime);
        results[k][0] =  (double)arraymax * (double)jmax * sbytes / mega / secs;

        printf("%7.0f ", results[k][0]);
        fflush(stdout);
        fprintf(outfile, "%7.0f ", results[k][0]);
 

        // Serial Read/Write Integer *********************

        for (i=0; i<arraymax+1; i++)
        {
            xi[i] = i+1;
        }

        jmax = 1;
        sbytes = 4.0;
        do
        {
            toti = testJI(jmax, arraymax);    
            jmax = checkTime(jmax);   
        }
        while (secs < runTime);
        results[k][1] =  (double)arraymax * (double)jmax * sbytes / mega / secs;
 
        printf("%7.0f ", results[k][1]);
        fflush(stdout);
        fprintf(outfile, "%7.0f ", results[k][1]);


        // Random Read Integer *********************

        srand(123);

        for (i=0; i<arraymax+1; i++)
        {
           xi[i] = (int)((double)arraymax * ((double)(rand()) / (double)2147483648.0));
       }


        jmax = 1;
        sbytes = 4.0;
        do
        {
            toti = testIIR(jmax, arraymax);    
            jmax = checkTime(jmax);   
        }
        while (secs < runTime);
        results[k][2] =  (double)arraymax * (double)jmax * sbytes / mega / secs;

        printf("%7.0f ", results[k][2]);
        fflush(stdout);
        fprintf(outfile, "%7.0f ", results[k][2]);

        // Random Read/Write Integer *********************

        srand(123);
        for (i=0; i<arraymax+1; i++)
        {
           xi[i] = (int)((double)arraymax * ((double)(rand()) / (double)2147483648.0));
        }

        jmax = 1;
        sbytes = 4.0;
        do
        {
            toti = testJIR(jmax, arraymax);    
            jmax = checkTime(jmax);   
        }
        while (secs < runTime);
        results[k][3] =  (double)arraymax * (double)jmax * sbytes / mega / secs;


        printf("%7.0f ", results[k][3]);
        fflush(stdout);
        fprintf(outfile, "%7.0f ", results[k][3]);


        _mm_free(xi);

        // xxxxxxxx Double

        darraymax = arraymax / 3;

        xi = (int *)_mm_malloc(darraymax * 4 + 8, 16);
        if (xi == NULL)
        {
           printf(" ERROR WILL EXIT\n");
           printf(" Press Enter\n");
           g  = getchar();
           exit(1);
        }

        xd = (double *)_mm_malloc(darraymax * 8 + 8, 16);
        if (xd == NULL)
        {
           _mm_free(xi);
           printf(" ERROR WILL EXIT\n");
           printf(" Press Enter\n");
           g  = getchar();
           exit(1);
        }


        // Serial Read Double *********************

        for (i=0; i<darraymax+1; i++)
        {
            xd[i] = 1.0;
            xi[i] = i+1;
        }
        jmax = 1;
        sbytes = 12.0;
        do
        {
            totd = testID(jmax, darraymax);       
            jmax = checkTime(jmax);   
        }
        while (secs < runTime);
        results[k][4] =  (double)darraymax * (double)jmax * sbytes / mega / secs;

        printf("%7.0f ", results[k][4]);
        fflush(stdout);
        fprintf(outfile, "%7.0f ", results[k][4]);


        // Serial Read/Write Double *********************

        for (i=0; i<darraymax+1; i++)
        {
            xd[i] = 1.0;
            xi[i] = i+1;
        }
        jmax = 1;
        sbytes = 12.0;
        do
        {
            totd = testJD(jmax, darraymax);    
            jmax = checkTime(jmax);   
        }
        while (secs < runTime);
        results[k][5] =  (double)darraymax * (double)jmax * sbytes / mega / secs;


        printf("%7.0f ", results[k][5]);
        fflush(stdout);
        fprintf(outfile, "%7.0f ", results[k][5]);


        // Random Read Double *********************
        
        srand(123);
        for (i=0; i<darraymax+1; i++)
        {
            xi[i] = (int)((double)darraymax * ((double)(rand()) / (double)2147483648.0));
            xd[i] = 1.0;
        }

        jmax = 1;
        sbytes = 12.0;    
        do
        {
            totd = testIDR(jmax, darraymax); 
            jmax = checkTime(jmax);   
        }
        while (secs < runTime);
        results[k][6] =  (double)darraymax * (double)jmax * sbytes / mega / secs;


        printf("%7.0f ", results[k][6]);
        fflush(stdout);
        fprintf(outfile, "%7.0f ", results[k][6]);


        // Random Read/Write Double *********************

        srand(123);
        for (i=0; i<darraymax+1; i++)
        {
            xi[i] = (int)((double)darraymax * ((double)(rand()) / (double)2147483648.0));
        }

        jmax = 1;
        sbytes = 12.0;    
        do
        {
            totd = testJDR(jmax, darraymax); 
            jmax = checkTime(jmax);   
        }
        while (secs < runTime);
        results[k][7] =  (double)darraymax * (double)jmax * sbytes / mega / secs;


        printf("%7.0f ", results[k][7]);
        fflush(stdout);
        fprintf(outfile, "%7.0f", results[k][7]);

        _mm_free(xd);
        _mm_free(xi);

        printf("\n");
        fflush(stdout);
        fprintf(outfile, "\n");
        arraymax = arraymax * 2;
        fflush(outfile);
    }

    local_time();
    fprintf(outfile, "\n                End of test %s\n", timeday);        
    fprintf(outfile,"\n");
    fclose(outfile);
    printf("\n");
    printf("  Press Enter\n");
    g  = getchar();
    return 1;
    
} // runTests


int checkTime(int jmax)
{
    if (secs < runTime)
    {
          if (secs < runTime / 8.0)
          {
                jmax = jmax * 10;
          }
          else
          {
                jmax = (int)(runTime * 1.25 / secs * (double)jmax+1);
          }
      }
      return jmax;
}


