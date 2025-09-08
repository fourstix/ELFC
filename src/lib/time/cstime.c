#define _ELFCLIB_

#include <stdlib.h>
#include <time.h>


/* define only extern procedures required */
#pragma           extrn Csystime
#pragma           extrn Casctime

static struct tm _tm;

/*
 * Generate the standard ASCII date-time string 
 */
char *cstime(void) {  
  systime(&_tm);
  return asctime(&_tm);  
}
