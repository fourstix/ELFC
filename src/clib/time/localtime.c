/*
 * localtime.c - convert time_t to local struct tm
 * Returns pointer to a static buffer.
 */
#define _ELFCLIB_

#include <stdlib.h>
#include <time.h>

/* define only extern procedures required */
#pragma extrn C_time_t_to_tm
#pragma extrn C_tz_offset

struct tm *localtime(/* const */ time_t *tp)
{
  static struct tm tm_buf;
  if (!tp) return NULL;
  _time_t_to_tm(*tp, _tz_offset, &tm_buf);
  return &tm_buf;
}
