/*
 * gmtime.c - convert time_t to UTC struct tm
 * Returns pointer to a static buffer.
 */
#define _ELFCLIB_

#include <time.h>

/* define only extern procedures required */
#pragma           extrn C_time_t_to_tm

static /* const */ int32_t I32_ZERO  = { 0, 0 };

struct tm *gmtime(/* const */ time_t *tp)
{
    static struct tm tm_buf;
    if (!tp) return NULL;
    _time_t_to_tm(*tp, I32_ZERO, &tm_buf);
    tm_buf.tm_isdst = 0;
    return &tm_buf;
}
