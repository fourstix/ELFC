#ifndef _TIME_
#define _TIME_

/* include stdlib if not included already */
#ifndef _STDLIB_
#include <stdlib.h>
#endif

#include <math32.h>

 /* don't define all external functions inside C library procdures to prevent dupes */
#ifndef _ELFCLIB_
#pragma .link .library time.lib
#pragma .link .requires Ctimezone
#endif

typedef int32_t time_t;

#ifndef __ELFIO__
#define asctime  _asctime
#define cstime   _cstime
#define strftime _strftime
#define ctime    _ctime
#else
#define asctime  _asctime2
#define cstime   _cstime2
#define strftime _strftime2
#define ctime    _ctime2
#endif

extern char *_tzname;  /* Time Zone Name */
extern int32_t _tz_offset; /* seconds difference from GMT (West negative, East positive) */
extern int _tz_dst;    /* 1 if DST in effect, 0 if not and -1 if unknwon */

#define TZ_NAME_MAX  8

/*
 * Parsed representation of a POSIX TZ string:
 *   std_name  offset  [ dst_name [ dst_offset ] [ , rule ] ]
 *
 * has_dst is false if there is no dst_name component at all (e.g.
 * "UTC0" or "EST5"), meaning the zone never observes DST.
 *
 * has_rule is false if a dst_name is present but no ",rule" was
 * given; POSIX defines a default US rule in that case, but on this
 * platform we treat it as "DST status unknown" instead of guessing
 * at a region-specific default.
 */
struct tz_parsed {
    char    std_name[TZ_NAME_MAX];
    int32_t std_offset;     /* seconds to ADD to local time to get UTC */
    char    dst_name[TZ_NAME_MAX];
    int32_t dst_offset;     /* seconds to ADD to local DST time to get UTC */
    int     has_dst;
    int     has_rule;
    int     start_month;    /* 1-12 */
    int     start_week;     /* 1-5 (5 = last) */
    int     start_day;      /* 0-6, 0=Sunday */
    int32_t start_time;     /* seconds after local midnight, default 7200 */
    int     end_month;
    int     end_week;
    int     end_day;
    int32_t end_time;
};

int _tz_parse(const char *tz, struct tz_parsed *out);
int _tz_is_dst_active(struct tz_parsed *tz, time_t now_utc);
void tzset_us(void);
void tzset_all(void);

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
char *_asctime(struct tm *tp);
char *_asctime2(struct tm *tp);
char *_cstime(void);
char *_cstime2(void);
int  _strftime(char* s, int smax, const char * fmt, struct tm *tp);
int  _strftime2(char* s, int smax, const char * fmt, struct tm *tp);
void timezone(char *tzname, int tzoff_min, int tzdst);
int  utctime(struct tm *tp);
time_t _tm_to_time_t(struct tm *t, int32_t utc_offset_secs);
void _time_t_to_tm(time_t ts, int32_t utc_offset_secs, struct tm *out);
char *_ctime(time_t *timer);
char *_ctime2(time_t *timer);
time_t time(time_t *second);
time_t timegm(struct tm *t);
time_t mktime(struct tm *t);
struct tm *gmtime(time_t *timer);
struct tm *localtime(time_t *timer);

#endif
