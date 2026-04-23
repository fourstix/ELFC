#define _ELFCLIB_

#include <stdlib.h>
#include <time.h>


/* define only extern procedures required */
#pragma           extrn Csystime
#pragma           extrn C_asctime

static struct tm _tm;

/*
 * Generate the standard ASCII date-time string
 */
char *_cstime(void) {
  systime(&_tm);
  return _asctime(&_tm);
}
