#define _ELFCLIB_

#include <stdlib.h>
#include <time.h>

/* define only extern procedures required */
#pragma        extrn C_systime
#pragma        extrn C_dow
#pragma        extrn C_doy
#pragma        extrn C_tz_dst

/* Kernel defines 8 bytes for RTC, we only need first 6 */
static   char _ts[8];

/*
 calculate the day of year from January 1
 */
int systime(struct tm *tp) {
  int  rtc;

  /* get the time from the system OS */
  rtc = _systime(_ts);

  /* Set tm fields from buffer */
  tp->tm_mon   = _ts[0] - 1;   /* C month offset is from 0 to 11, RTC is 1 to 12 */
  tp->tm_mday  = _ts[1];       /* month day 1 to 31 */
  tp->tm_year  = _ts[2] + 72;  /* C year offset is from 1900, RTC is from 1972 */
  tp->tm_hour  = _ts[3];       /* hours 0 to 23 */
  tp->tm_min   = _ts[4];       /* minutes 0 to 59 */
  tp->tm_sec   = _ts[5];       /* seconds 0 to 59 */

  /* set tm fields calculatd from other fields */
  _dow(tp);     /* days since Sunday 0 to 6 */
  _doy(tp);     /* days since January 1,  0 to 365 */

  /* Set dst flag from timezone information */
  tp->tm_isdst = _tz_dst;      /* dst flag 1 for Yes, 0 for No, -1 for Unknown */

  return rtc;
}
