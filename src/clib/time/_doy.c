/*
 * doy.c - set tm_yday from other fields of struct tm
 *
 * Counts days from January 1 (day 0) to the date in *t.
 * All arithmetic fits in 16-bit int.
 */
#define _ELFCLIB_

#include <time.h>

static /* const */ int dim[2][12] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
    31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

void _doy(struct tm *t)
{
    int year;
    int leap;
    int m;
    int yday;

    year = t->tm_year + 1900;
    leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 1 : 0;
    yday = t->tm_mday - 1;
    for (m = 0; m < t->tm_mon; m++)
        yday += dim[leap][m];
    t->tm_yday = yday;
}
