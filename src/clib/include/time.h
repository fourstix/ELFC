#ifndef _TIME_
#define _TIME_

/* include stdlib if not included already */
#ifndef _STDLIB_
#include <stdlib.h>
#endif

 /* don't define all external functions inside C library procdures to prevent dupes */
#ifndef _ELFCLIB_
#pragma .link .library time.lib
#endif


extern char *_tzname;  /* Time Zone Name */
extern int _tz_min;    /* minutes difference from GMT (West negative, East positive) */
extern int _tz_hr;     /* hours difference from GMT (West negative, East positive) */
extern int _tz_dst;    /* 1 if DST in effect, 0 if not and -1 if unknwon */


struct tm {
    int tm_sec;       /* seconds after the minute (0 to 60) */
    int tm_min;       /* minutes after the hour (0 to 60) */
    int tm_hour;      /* hours after midnight (0 to 23) */
    int tm_mday;      /* day of the month (1 to 31) */
    int tm_mon;       /* months since January (0 to 11) */
    int tm_year;      /* years since 1900 */
    int tm_wday;      /* days since Sunday (0 to 6) */
    int tm_yday;      /* days since January 1 (0 to 365) */
    int tm_isdst;     /* Daylight Savings Time (0 => no, 1 => yes, -1 => unknown) */
};

void _dow(struct tm *tp);
void _doy(struct tm *tp);
int  systime(struct tm *tp);
char *asctime(struct tm *tp);
char *cstime(void);
int  strftime(char* s, int smax, const char * fmt, struct tm *tp);
void timezone(char *tzname, int tzoff_min, int tzdst);
int  utctime(struct tm *tp);


#endif
