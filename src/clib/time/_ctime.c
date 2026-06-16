/*
 * ctime.c - format time_t as local time string
 * Equivalent to asctime(localtime(tp)).
 * Returns pointer to static buffer from asctime, or NULL on error.
 */
#define _ELFCLIB_

#include <time.h>

/* define only extern procedures required */
#pragma           extrn Clocaltime
#pragma           extrn C_asctime

char *_ctime(/*const*/ time_t *tp)
{
    struct tm *t;
    if (!tp) return NULL;
    t = localtime(tp);
    if (!t) return NULL;
    return _asctime(t);
}
