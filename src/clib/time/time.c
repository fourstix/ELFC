/*
 * time.c - return current UTC time_t
 * Calls systime() to get current local time, converts to UTC time_t.
 * If tp is non-NULL, also stores result there.
 */
#define _ELFCLIB_

#include <time.h>

/* define only extern procedures required */
#pragma extrn Csystime
#pragma extrn C_tz_hr
#pragma extrn C_tz_min
#pragma extrn Ci32_from_int
#pragma extrn Caddi32
#pragma extrn Cmuli32x16
#pragma extrn C_tm_to_time_t
#pragma extrn C_tz_offset

#define SECS_PER_MIN 60
#define SECS_PER_HOUR 3600

time_t time(time_t *tp)
{
  static struct tm tm_buf;
  time_t result;

  systime(&tm_buf);
  result = _tm_to_time_t(&tm_buf, _tz_offset);
  if (tp != NULL) *tp = result;
  return result;
}
