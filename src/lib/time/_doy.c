#define _ELFCLIB_

#include <time.h>

/* day of year month offsets, adjusted for zero base */
static int _mdoy[] = {0, 30, 58, 89, 119, 150, 180, 211, 242, 272, 303, 333};
 
/*
 * Set the day of year field, from time structure's year, month and day fields
 */ 
void _doy(struct tm *tp) {
  int leap;
  int y, m, d;
  
  if (tp) {  
    y = tp->tm_year + 1900;
    m = tp->tm_mon;
    d = tp->tm_mday;
    
    /* if January or February, no leap year adjustment */
    if (m < 2) 
      leap = 0;
    else   
      leap = (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0));

    tp->tm_yday = _mdoy[m] + leap + d;  
  } 
}
