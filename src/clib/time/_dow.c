/*
 * dow.c - set tm_wday from other fields of struct tm
 *
 * Uses Tomohiko Sakamoto's algorithm.
 * All intermediate values fit in 16-bit signed int for years 1900-2099.
 * The largest intermediate value is approximately year + year/4 ~ 2585,
 * well within the 16-bit signed range of 32767.
 */
#define _ELFCLIB_

#include <time.h>

void _dow(struct tm *t)
{
    static /* const */ int adj[12] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    int y;
    int wday;

    y = t->tm_year + 1900;
    if (t->tm_mon < 2)
        y--;
    wday = y + y/4 - y/100 + y/400 + adj[t->tm_mon] + t->tm_mday;
    wday = wday % 7;
    if (wday < 0)
        wday += 7;
    t->tm_wday = wday;
}
