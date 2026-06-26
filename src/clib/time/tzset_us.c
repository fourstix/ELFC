/*
 * tzset_simple.c
 *
 * Simplified tzset() for US/North American time zones.
 *
 * Handles POSIX TZ strings of the form:
 *   STD offset [ DST [ , rule ] ]
 * where:
 *   STD/DST  2-5 letters (no <> quoting needed for North American zones)
 *   offset   unsigned integer hours only (no sign, no :mm:ss)
 *   rule     present but ignored; the US DST rule is hardcoded:
 *              Start: 2nd Sunday of March at 02:00 local standard time
 *              End:   1st Sunday of November at 02:00 local DST time
 *            (US rule since 2007, covers all Canadian provinces too)
 *
 * DST status is determined by calling systime() to get the current
 * local date and checking it against the transition dates. Since
 * systime() returns local wall-clock time, and the transition times
 * are defined in local time, no UTC conversion is needed.
 *
 * Handles all common North American zones:
 *   EST5EDT  CST6CDT  MST7MDT  PST8PDT  AST4ADT  AKST9AKDT
 *   HST10    MST7   (no-DST zones)
 *
 * Sets _tz_name, _tz_offset (int32_t seconds), _tz_dst as described
 * in tzset.h. Defaults to UTC on any parse error.
 *
 * getenv is forward-declared (not via env.h) to avoid the host-side
 * header conflict between <fcntl.h>'s native time_t and ours.
 */
#define _ELFCLIB_

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#pragma extrn Cgetenv
#pragma extrn Cisalpha
#pragma extrn Cisdigit
#pragma extrn Cstrncpy
#pragma extrn Cnegi32
#pragma extrn C_tz_name
#pragma extrn C_tz_offset
#pragma extrn C_tz_dst
#pragma extrn Csystime

/* ── helpers ─────────────────────────────────────────────────────── */

static void set_utc_default(void)
{
    _tz_name[0] = 'U';
    _tz_name[1] = 'T';
    _tz_name[2] = 'C';
    _tz_name[3] = '\0';
    _tz_offset.low  = 0;
    _tz_offset.high = 0;
    _tz_dst = 0;
}

/*
 * dst_active: determine if US DST is currently in effect.
 *
 * Uses systime() to get the current local date. Since systime()
 * returns local wall-clock time, and US DST transitions are defined
 * in local time (2:00am), the comparison is direct.
 *
 * Fast-path by month:
 *   Jan, Feb, Dec          -> standard time (return 0)
 *   Apr, May, Jun, Jul,
 *   Aug, Sep, Oct          -> DST (return 1)
 *   Mar                    -> DST if past 2nd Sunday at 2:00am
 *   Nov                    -> standard if past 1st Sunday at 2:00am
 *
 * Finding the Nth Sunday without division:
 *   The 2nd Sunday of March falls on day 8..14.
 *   The 1st Sunday of November falls on day 1..7.
 *   Given today's mday and wday (0=Sun), the Sunday of this week
 *   is on (mday - wday). If that Sunday is in the target range,
 *   it is the transition Sunday.
 */
static int dst_active(void)
{
    static struct tm t;
    int mon;
    int mday;
    int wday;
    int hour;
    int sun_this_week;

    systime(&t);
    mon  = t.tm_mon + 1;   /* convert 0-based to 1-based */
    mday = t.tm_mday;
    wday = t.tm_wday;       /* 0=Sunday */
    hour = t.tm_hour;

    if (mon <= 2 || mon == 12)
        return 0;           /* Jan, Feb, Dec: standard */

    if (mon >= 4 && mon <= 10)
        return 1;           /* Apr..Oct: DST */

    if (mon == 3) {
        /* March: DST starts on the 2nd Sunday (days 8..14) at 2:00am */
        if (mday < 8)
            return 0;       /* before earliest possible 2nd Sunday */
        if (mday > 14)
            return 1;       /* after latest possible 2nd Sunday */
        /* mday in 8..14: check if we have reached the 2nd Sunday */
        sun_this_week = mday - wday;
        if (sun_this_week < 8)
            return 0;       /* this week's Sunday is before day 8 */
        /* this week's Sunday is the 2nd Sunday of March */
        if (wday == 0)
            return (hour >= 2) ? 1 : 0;   /* transition day */
        return 1;           /* past the transition Sunday */
    }

    /* mon == 11: November: DST ends on the 1st Sunday (days 1..7) at 2:00am */
    if (mday > 7)
        return 0;           /* after latest possible 1st Sunday */
    sun_this_week = mday - wday;
    if (sun_this_week < 1)
        return 1;           /* this week's Sunday before day 1: not ended yet */
    /* this week's Sunday is the 1st Sunday of November */
    if (wday == 0)
        return (hour >= 2) ? 0 : 1;   /* transition day */
    return 0;               /* past the transition Sunday */
}

/* ── tzset ──────────────────────────────────────────────────────────────── */

void tzset_us(void)
{
    static char std_name[TZ_NAME_MAX];
    static char dst_name[TZ_NAME_MAX];
    const char *p;
    int std_name_len;
    int dst_name_len;
    int offset_hours;
    int has_dst;
    int32_t std_offset;
    int32_t dst_offset;

    p = getenv("TZ");
    if (p == NULL) {
        set_utc_default();
        return;
    }

    /* standard zone name: letters only */
    std_name_len = 0;
    while (isalpha((unsigned char)*p) && std_name_len < TZ_NAME_MAX - 1)
        std_name[std_name_len++] = *p++;
    std_name[std_name_len] = '\0';

    if (std_name_len == 0) {
        set_utc_default();
        return;
    }

    /* unsigned integer hours offset */
    if (!isdigit((unsigned char)*p)) {
        set_utc_default();
        return;
    }
    offset_hours = 0;
    while (isdigit((unsigned char)*p))
        offset_hours = offset_hours * 10 + (*p++ - '0');

    /* build offsets in seconds
     * POSIX convention: offset is seconds to ADD to local to get UTC,
     * so for us local = UTC - POSIX_offset, i.e. _tz_offset = -offset */
    std_offset.low  = (uint16_t)((offset_hours * 3600) & 0xFFFF);
    std_offset.high = (uint16_t)((offset_hours * 3600) >> 16);

    /* DST offset is always 1 hour less than standard for North America */
    dst_offset.low  = (uint16_t)(((offset_hours - 1) * 3600) & 0xFFFF);
    dst_offset.high = (uint16_t)(((offset_hours - 1) * 3600) >> 16);

    /* optional DST name */
    has_dst = 0;
    dst_name[0] = '\0';
    if (isalpha((unsigned char)*p)) {
        has_dst = 1;
        dst_name_len = 0;
        while (isalpha((unsigned char)*p) && dst_name_len < TZ_NAME_MAX - 1)
            dst_name[dst_name_len++] = *p++;
        dst_name[dst_name_len] = '\0';
        /* any remaining rule string is intentionally ignored */
    }

    if (!has_dst) {
        strncpy(_tz_name, std_name, TZ_NAME_MAX);
        _tz_offset = negi32(std_offset);
        _tz_dst = 0;
        return;
    }

    if (dst_active()) {
        strncpy(_tz_name, dst_name, TZ_NAME_MAX);
        _tz_offset = negi32(dst_offset);
        _tz_dst = 1;
    } else {
        strncpy(_tz_name, std_name, TZ_NAME_MAX);
        _tz_offset = negi32(std_offset);
        _tz_dst = 0;
    }
}
