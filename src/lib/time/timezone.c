#define _ELFCLIB_

#include <stdlib.h>
#include <time.h>

/* Time Zone name */
char *_tzname = NULL;

/* Timezone offsets are not always whole number hours (Newfoundland and India) */
/* Offsets are negative for timezones WEST of GMT (North and South America) */
/* Offsets are positive for timezones EAST of GMT (Europe, Africa and Asia) */

int _tz_min    =  0;     /* minutes offset from GMT */
int _tz_hr     =  0;     /* hours offset from GMT */
int _tz_dst    = -1;     /* DST is unknown until set */


void timezone(char *tzname, int tzoff_min, int tzdst) {
  int tz_hr, tz_min;
  
  tz_hr  = tzoff_min / 60;
  tz_min = tzoff_min % 60;
  
  _tzname = tzname;
  _tz_hr  = tz_hr;
  _tz_min = tz_min;
  _tz_dst = tzdst;
}
