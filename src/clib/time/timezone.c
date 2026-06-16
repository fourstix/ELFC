#define _ELFCLIB_

#include <stdlib.h>
#include <time.h>

/* define only extern procedures required */
#pragma extrn Cmuli32x16
#pragma extrn Caddi32
#pragma extrn Ci32_from_int

#define SECS_PER_HOUR 3600

/* Time Zone name */
char *_tzname = NULL;

/* Timezone offsets are not always whole number hours (Newfoundland and India)
 */
/* Offsets are negative for timezones WEST of GMT (North and South America) */
/* Offsets are positive for timezones EAST of GMT (Europe, Africa and Asia) */

int32_t _tz_offset = {0, 0}; /* seconds offset from GMT */
int _tz_dst = -1;            /* DST is unknown until set */

void timezone(char *tzname, int tzoff_min, int tzdst)
{
  _tzname = tzname;
  _tz_offset = muli32x16(i32_from_int(tzoff_min), 60);
  if (tzdst == 1) {
    _tz_offset = addi32(_tz_offset, i32_from_int(SECS_PER_HOUR));
  }
  _tz_dst = tzdst;
}
