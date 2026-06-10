/*
 * mktime.c - convert local struct tm to time_t (UTC)
 */
#define _ELFCLIB_

#include <time.h>

/* define only extern procedures required */
#pragma           extrn C_tm_to_time_t
#pragma           extrn C_tz_offset

static /* const */ int32_t I32_NEG1  = { 0xFFFF, 0xFFFF };

time_t mktime(struct tm *t)
{
    if (!t) return I32_NEG1;
    return _tm_to_time_t(t, _tz_offset());
}
