#define _ELFCLIB_

#include <stdlib.h>
#include <time.h>

#pragma              extrn Csystime
#pragma              extrn C_tm_to_time_t
#pragma              extrn C_tz_offset
#pragma              extrn Cgmtime

/*
 Calculate the Universal Co-ordinated Time
 */
int utctime(struct tm *tp) {
  int rtc;      /* flag to indicate RTC used */
  time_t utc;
  struct tm *gmt;
  
  /* get the system time */
  rtc = systime(tp);

  utc = _tm_to_time_t(tp, _tz_offset());
  gmt = gmtime(&utc);
  *tp = *gmt;

  return rtc;
}
