#define _ELFCLIB_

#include <stdlib.h>
#include <math32.h>
#include <time.h>

#pragma extrn Ci32_from_int
#pragma extrn Cint_from_i32
#pragma extrn Caddi32
#pragma extrn Cdivi32
#pragma extrn Ccmpi32
#pragma extrn Ctimegm
#pragma extrn Cgmtime
#pragma extrn C_dow

static const int days_in_month_tbl[2][12] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
    31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static int is_leap_year(int year)
{
    if (year % 4 != 0)   return 0;
    if (year % 100 != 0) return 1;
    if (year % 400 != 0) return 0;
    return 1;
}

/*
 * rule_to_mday: given a year, month, target weekday (0=Sun..6=Sat),
 * and week number (1-5, 5=last), return the day-of-month on which
 * the rule's transition falls.
 */
static int _rule_to_mday(int year, int month, int week, int weekday)
{
    static struct tm probe;
    int first_wday;
    int mday;
    int leap;
    int dim;

    leap = is_leap_year(year);
    dim  = days_in_month_tbl[leap][month - 1];

    /* Find the weekday of the 1st of this month via _dow */
    probe.tm_year = year - 1900;
    probe.tm_mon  = month - 1;
    probe.tm_mday = 1;
    probe.tm_hour = 0;
    probe.tm_min  = 0;
    probe.tm_sec  = 0;
    _dow(&probe);
    first_wday = probe.tm_wday;

    /* Day-of-month of the first occurrence of `weekday` in this month */
    mday = 1 + ((weekday - first_wday + 7) % 7);

    /* Advance to the requested week */
    mday = mday + (week - 1) * 7;

    if (mday > dim) {
        /* week 5 ("last") overflowed past the end of the month:
         * step back to the previous occurrence of `weekday` */
        mday -= 7;
    }

    return mday;
}

/*
 * transition_instant: compute the UTC time_t at which a given
 * Mm.w.d rule transition occurs in the given year, given the local
 * clock offset in effect *before* the transition (std_offset for
 * the start-of-DST transition, dst_offset for the end-of-DST
 * transition), since the rule's time-of-day is expressed in the
 * wall-clock time that is active immediately before the switch.
 */
static time_t _transition_instant(int year, int month, int week, int day,
                                  int32_t time_of_day, int32_t utc_offset)
{
    static struct tm t;
    int32_t secs_part;
    int32_t mins_part;
    int32_t hh;
    int32_t mm;
    int32_t ss;
    time_t result;

    t.tm_year = year - 1900;
    t.tm_mon  = month - 1;
    t.tm_mday = _rule_to_mday(year, month, week, day);

    /* split time_of_day (seconds) into h:m:s */
    hh = divi32(time_of_day, i32_from_int(3600), &secs_part);
    mm = divi32(secs_part, i32_from_int(60), &ss);
    mins_part = mm;

    t.tm_hour = int_from_i32(hh);
    t.tm_min  = int_from_i32(mins_part);
    t.tm_sec  = int_from_i32(ss);

    /* t is local wall-clock time; convert to UTC by adding the
     * offset that was in effect at that wall-clock moment (POSIX
     * convention: offset is seconds to ADD to local to reach UTC) */
    result = timegm(&t);
    result = addi32(result, utc_offset);
    return result;
}

int _tz_is_dst_active(struct tz_parsed *tz, time_t now_utc)
{
    static struct tm now_tm;
    int year;
    time_t start;
    time_t end;

    if (!tz->has_dst || !tz->has_rule)
        return -1;

    /* Determine the calendar year to evaluate the rule in, based on
     * the current UTC time (close enough for rule purposes; a
     * transition within a few hours of midnight UTC on Dec 31/Jan 1
     * could in principle evaluate against the "wrong" year, but the
     * practical effect is negligible since transitions never occur
     * near a year boundary). */
    now_tm = *gmtime(&now_utc);
    year = now_tm.tm_year + 1900;


    start = _transition_instant(year, tz->start_month, tz->start_week,
                                tz->start_day, tz->start_time,
                                tz->std_offset);
    end = _transition_instant(year, tz->end_month, tz->end_week,
                              tz->end_day, tz->end_time,
                              tz->dst_offset);

    if (cmpi32(start, end) < 0) {
        /* Northern-hemisphere style: DST active for [start, end) */
        if (cmpi32(now_utc, start) >= 0 && cmpi32(now_utc, end) < 0)
            return 1;
        return 0;
    } else {
        /* Southern-hemisphere style: DST wraps the year boundary,
         * active everywhere except [end, start) */
        if (cmpi32(now_utc, end) >= 0 && cmpi32(now_utc, start) < 0)
            return 0;
        return 1;
    }
}
