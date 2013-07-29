/* 
 * 
 * RandMem Benchmark Version 2 Copyright (c) Roy Longbottom 2010 
 * Improved and modified by marina@die.upm.es (GreenLSI 2013) 
 * http://greenlsi.die.upm.es
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdint.h>
#include <malloc.h>

#include "cpuidh.h"
#include "memory.h"
#include "main_defs.h"


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  initVars
 *  Description:  Initialize global variables 
 * =====================================================================================
 */
void initVars(void)
{
    runTime = 0.1; //secs
    numexecs = 1;
    integer=1;
    serial=1;
    usermemsize=0;
    blockmemsize=MAX_ARRAY_VALUE;
    read=1; 
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  parseArguments
 *  Description:  parse command-line arguments 
 * =====================================================================================
 */
int parseArguments (int argc, char **argv)
{
    //TODO-marina: parse command-line arguments
     int i;
     /*printf("Parsing command-line arguments: argc=%d \n", argc);*/

     for(i=1; i < argc; i++) {

         /*printf("Parsing command-line arguments: arg:%d - %s \n", i, argv[i]);*/
         if (strcmp(argv[i], "--help") == 0) {
            printf("Usage: %s --pattern=<pattern type> --data=<data type> --access=<read/write access> --memsize=<mem size in GB> --blocksize=<memory block size (KB)> --runtime=<runtime in secs> --numexecs=<number of executions>\n", argv[0]);
            printf("    - pattern: test to run, can be 'serial' or 'random'\n");
            printf("    - data: type of data to run, can be 'integer' or 'intfp'\n");
            printf("    - access: type of access to memory, can be 'r' or 'rw'\n");
            printf("    - memsize: memory size in GB to use\n");
            printf("    - blocksize: maximum size of each memory block (in KB)\n");
            printf("    - runtime: minimum time to run benchmark (in secs) \n");
            printf("    - numexecs: Number of times the benchmark is executed \n");
            exit(0);
         } 
         else if (strcmp(argv[i], "--pattern=random") == 0) {
            serial=0;
         } 
         else if (strcmp(argv[i], "--pattern=serial") == 0) {
            serial=1;
         } 
         else if (strcmp(argv[i], "--access=rw") == 0) {
            read=0;
         } 
         else if (strcmp(argv[i], "--data=integer") == 0) {
            integer=1;
         } 
         else if (strcmp(argv[i], "--data=intfp") == 0) {
            integer=0;
         } 
         else if (! strncmp(argv[i], "--memsize=", 10) ) {
            usermemsize = atof(argv[i]+10);
            /*printf("User memsize is: %f \n", usermemsize);*/
         } 
         else if (! strncmp(argv[i], "--blocksize=", 12) ) {
            blockmemsize = atof(argv[i]+12);
            /*printf("Max block size is: %f \n", blockmemsize);*/
         } 
         else if (! strncmp(argv[i], "--runtime=", 10) ) {
            runTime = atof(argv[i]+10);
         } 
         else if (! strncmp(argv[i], "--numexecs=", 11) ) {
            numexecs = atoi(argv[i]+11);
         } 
         else {
             printf(stderr, "unrecognised argument %s\n", argv[i]);
             return -1;
         }
    }
    return 0;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  print_output_header
 *  Description:  Prints file/stdout output header. Returns file descriptor of
 *                output file
 * =====================================================================================
 */
void print_output_header( void )
{
    int i, g;

    for (i=1; i<7; i++) {
        printf("%s\n", configdata[i]);
    }
    printf("\n");
     
    printf(" #####################################################\n"); 


    local_time();
    printf("\n   Random/Serial Memory Test %s %s \n", version, timeday);
    printf("\n   Benchmark runtime: %f \n", runTime);
    printf("\n   Number of executions : %d \n", numexecs);
    
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  print_benchmark_params
 *  Description:  Prints benchmark parameters
 * =====================================================================================
 */
void print_benchmark_params( void )
{
    // Integer - Integer/FP benchmark
    if (integer){
        printf("             Integer\n");
    }
    else {
       printf("                 Double/Integer\n");
    }

    // Serial - Random benchmark
    if(serial){
        printf("             Serial........\n");
    }
    else{
        printf("            Random........\n");
    }
        
    //Read - write benchmark
    if (read){  
        printf("   Exec   Pass      RAM   Read   \n");
        printf("                KB  MB/Sec  \n\n");
    }
    else {     
        printf("   Exec   Pass    RAM   Rd/Wrt   \n");
        printf("                KB  MB/Sec  \n\n");
    }
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_total_free_mem
 *  Description:  
 * =====================================================================================
 */
int get_total_free_mem( int arraysize )
{
    int vm_size = 0;
    struct rlimit lim;

    FILE *fpipe;
    
    fpipe = (FILE*) popen("free | head -n 2 | tail -n 1 | awk '{print $4}'", "r");
    
    if ( !fpipe ){
        perror("  get_total_free_mem(): function popen() failed. Exiting...");
        exit(1);
    }
    fscanf(fpipe, "%d", &vm_size); 
    pclose(fpipe);

    /*system("free | head -n 2 | tail -n 1 | awk '{print $4}'");*/
    /*scanf("%d", &vm_size) ;*/

    if (getrlimit(RLIMIT_AS, &lim) != 0)
        return 0;
    if (lim.rlim_cur <= vm_size)
        return 0;
    
    printf ("VMsize is: %d -- ArraySize is: %d \n ", vm_size, arraysize);
    
    if ( arraysize < vm_size ){
        return arraysize ;
    }

    return (vm_size * 1024 / 4) ;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  Main
 * =====================================================================================
 */
int main( int argc, char *argv[] )
{
    int i,j, g, m, k;
    double results;
    
    int     num_malloc=0, malloc_size[MAX_NUM_MALLOCS], malloc_flag=0;
    int     *xi[MAX_NUM_MALLOCS];
    double  *xd[MAX_NUM_MALLOCS];

    int     arraymax , darraymax;

    int arraymodule=0, arrayrem=0, blockarraysize, dbarraysize;

    struct rlimit limit ;

    //Initialize global variables
    initVars();

    //Parsing command-line args    
    parseArguments(argc, argv);

    // GetDetails function
    printf("\n");
    getDetails();
    
    
    // Get limits of memory
    /*getrlimit (RLIMIT_DATA, &limit);*/
    /*printf("  RLIMIT_DATA limit: soft=%lld; hard=%lld\n", (long long) limit.rlim_cur, (long long) limit.rlim_max);*/
    /*getrlimit (RLIMIT_MEMLOCK, &limit);*/
    /*printf("  RLIMIT_MEMLOCK limit: soft=%lld; hard=%lld\n", (long long) limit.rlim_cur, (long long) limit.rlim_max);*/
    /*getrlimit (RLIMIT_AS, &limit);*/
    /*printf("  RLIMIT_AS limit: soft=%lld; hard=%lld\n\n", (long long) limit.rlim_cur, (long long) limit.rlim_max);*/
    
    // Setting usermemsize to appropriate value
    if (usermemsize == 0){
        if ( ramGB > MAX_RAM_GB ){
            usermemsize=  MAX_RAM_GB ; //( MAX_ARRAY_VALUE / 1024 / 1024 / 1024 * 4 );
            printf("  User did not define memory size. Memory size exceeds maximum. Defaulting to %f \n", MAX_RAM_GB);
        }
        else {
            usermemsize=ramGB;    
            printf("  User did not define memory size. Defaulting to %f \n", usermemsize);
        }
    }
    else if (usermemsize > ramGB) {
        if ( ramGB > MAX_RAM_GB ){
            usermemsize=  MAX_RAM_GB ; //( MAX_ARRAY_VALUE / 1024 / 1024 / 1024 * 4 );
        }
        else {
            usermemsize=ramGB;
        }
        printf("Memory required by user exceeds maximum of %f.\n Defaultint to %f GB", (double) MAX_RAM_GB, ramGB);            
    }
        
    //----------------------------------------------------------------------------------------
    // Printing header files 
    print_output_header( );

    //----------------------------------------------------------------------------------------
    // Trying to allocate desired memory space

    results = 0;
    //Calculating array size for usermemsize
    arraymax = usermemsize * 1024 * 1024 * 1024 / 4 ;
    blockarraysize = blockmemsize * 1024 * 1024 / 4 ;

    printf("   Total memory to allocate %f and size of memory blocks %f \n", usermemsize, blockmemsize );

    if (blockarraysize < arraymax){
        arraymodule = arraymax / blockarraysize ;
        arrayrem = arraymax % blockarraysize ;
    }
    else {
        arrayrem=arraymax;
    }
    
    printf("   Number of blocks to allocate: %d and remainder memory: %d \n", arraymodule, arrayrem);
    printf("   Trying to allocate desired memory space \n");

    for (m=0 ; m<= arraymodule ; m++){
    
        if ( m == arraymodule ) {
            if (arrayrem){
                blockarraysize=arrayrem ; 
                /*printf("DEBUG: blockarraysize %d \n", blockarraysize);*/
            }
            else{
                break;
            }
        }
        if (integer){
            malloc_flag=0;
            do{
                printf("      Trying %d contiguous KB... ", (int) (blockarraysize / 1024 / 1024 * 4) );
                xi[num_malloc] = (int *) calloc (blockarraysize + 2 , 4 );
                if (xi[num_malloc] == NULL) {
                   printf(" Cannot allocate \n");
                   blockarraysize/=2;
                }
                else {
                   printf(" Allocation OK \n");
                   malloc_flag=1;
                   malloc_size[num_malloc]=blockarraysize;
                   num_malloc++;
                }
            } while (!malloc_flag);
        }
        else { //intfp
            malloc_flag=0;
            do{
                printf("      Trying %7d contiguous KB... ", blockarraysize * 4 / 1024);
                dbarraysize = blockarraysize / 3;         
                xi[num_malloc] = (int *)malloc(dbarraysize * 4 + 8);
                xd[num_malloc] = (double *)malloc(dbarraysize * 8 + 8);

                if ( (xi[num_malloc] == NULL) || (xd[num_malloc] == NULL) ) {
                   printf(" Cannot allocate \n");
                   if (blockarraysize > 0) {
                        blockarraysize/=2;
                   }
                   else {
                       printf(" All memory used. Cannot allocate anymore\n");
                       break;
                   }
                }
                else {
                   printf(" Allocation OK \n");
                   malloc_flag=1;
                   malloc_size[num_malloc]=blockarraysize;
                   num_malloc++;
                }


            } while (!malloc_flag);
        }
    }
    printf("\n\n");
    printf(" #####################################################\n\n"); 

    // Running benchmark
    // ----------------------------------------------------------------
    printf("  Running benchmark \n\n ");
    print_benchmark_params();

    /*for ( k=0 ; k< numexecs ; k++ ) {*/
    for (m=0 ; m< num_malloc ; m++){
        
        if (integer) {
            /*printf("  Executing Integer Benchmark for time: %d and size %d \n", m, malloc_size[m]);*/
            results = execute_integer_benchmark( malloc_size[m], xi[m], numexecs );
        }
        else {
            results = execute_intfp_benchmark( malloc_size[m], xi[m], xd[m], numexecs );
        }
        printf("     %d     %d    %7.0f \n", k, m, results);
        fflush(stdout);

    }
    /*}*/

    printf("\n");
    fflush(stdout);

    // Freeing memory
    // -----------------------------------------------------------------
     
    for (m=0 ; m< num_malloc ; m++){
        if (integer){
            free(xi[m]);
        }
        else {
            free(xi[m]);
            free(xd[m]);
        }
    } 

    local_time();
    printf("\n");
    return 1;
    
} // runTests



