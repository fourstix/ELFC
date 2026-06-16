/*
 * timegm.c - convert UTC struct tm to time_t
 */
#define _ELFCLIB_

#include <time.h>

/* define only extern procedures required */
#pragma           extrn C_tm_to_time_t

static /* const */ int32_t I32_ZERO  = { 0, 0 };
static /* const */ int32_t I32_NEG1  = { 0xFFFF, 0xFFFF };

time_t timegm(struct tm *t)
{
    if (!t) return I32_NEG1;
    return _tm_to_time_t(t, I32_ZERO);
}
