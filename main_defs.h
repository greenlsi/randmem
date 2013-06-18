#ifndef _MAIN_DEFS_HH_
#define _MAIN_DEFS_HH_

 
#ifdef BIT_VERSION_32
#define version  "32 Bit Version 3"
#else 
#ifdef BIT_VERSION_64
#define version  "64 Bit Version 3"
#else
#define version  "Solaris Bit Version 3"
#endif
#endif

#define MAX_PASSES      22   //32GB

#define MAX_RAM_GB         2.0    //2GB (maximum of process in Linux)
#define MAX_ARRAY_VALUE    ( MAX_RAM_GB * 1024 * 1024 * 1024 / 4 ) //536870912 //2GB

#define MAX_NUM_MALLOCS 100

// ************* GLOBAL VARIABLES **********
double  runTime; // 100 ms;
int     numexecs;

int     integer;
int     serial;
double  usermemsize;
double  blockmemsize;
int     read; 

// ************* FUNCIONES **********
void initVars( void );
int parseArguments (int argc, char **argv);
int get_total_free_mem( int arraysize );


#endif // _MAIN_DEFS_HH_

