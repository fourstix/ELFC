#define _ELFCLIB_

#include <time.h>

/* day of week offsets by month */
static int _mdow[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};

/*
 * Set the day of week field, from time structure's year, month day fields
 */ 
void _dow(struct tm* tp) {
  int y, m, d;
  
  if (tp) {
    y = tp->tm_year + 1900;
    m = tp->tm_mon;
    d = tp->tm_mday;
    
    y -= m < 2;

    tp->tm_wday = (y + y/4 - y/100 + y/400 + _mdow[m] + d) % 7;
  }
}
