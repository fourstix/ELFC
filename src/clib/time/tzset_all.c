/*
 * tzset.c
 *
 * Read the TZ environment variable (POSIX timezone format) and set:
 *   _tzname     short name of the zone currently in effect
 *               (the std name, or the dst name if DST is active)
 *   _tz_offset  int32_t offset in seconds from UTC for the zone
 *               currently in effect (local = UTC + _tz_offset;
 *               note this is the OPPOSITE sign convention from the
 *               POSIX TZ string itself, which gives seconds to ADD
 *               to local time to reach UTC)
 *   _tz_dst     0 = no DST in effect, 1 = DST in effect,
 *               -1 = unknown (a DST name was given but no transition
 *               rule, so current status cannot be determined)
 *
 * If TZ is not set, or is malformed, defaults to UTC: _tzname="UTC",
 * _tz_offset=0, _tz_dst=0.
 */
#define _ELFCLIB_

#include <stdlib.h>
#include <math32.h>
#include <time.h>

#pragma extrn Cgetenv
#pragma extrn Cnegi32
#pragma extrn Ctime
#pragma extrn C_tzname
#pragma extrn C_tz_offset
#pragma extrn C_tz_dst
#pragma extrn C_tz_parse
#pragma extrn C_tz_is_dst_active

static void set_utc_default(void)
{
    _tzname[0] = 'U';
    _tzname[1] = 'T';
    _tzname[2] = 'C';
    _tzname[3] = '\0';
    _tz_offset.low  = 0;
    _tz_offset.high = 0;
    _tz_dst = 0;
}

void tzset_all(void)
{
    char *tz_str;
    static struct tz_parsed tz;
    int dst_status;
    int i;

    tz_str = getenv("TZ");
    if (tz_str == NULL) {
        set_utc_default();
        return;
    }

    if (!_tz_parse(tz_str, &tz)) {
        set_utc_default();
        return;
    }

    if (!tz.has_dst) {
        /* zone never observes DST */
        for (i = 0; i < TZ_NAME_MAX; i++)
            _tzname[i] = tz.std_name[i];
        _tz_offset = negi32(tz.std_offset);   /* convert to local=UTC+offset */
        _tz_dst = 0;
        return;
    }

    if (!tz.has_rule) {
        /* DST observed but we cannot tell if it's active right now;
         * report the standard zone as a reasonable default value
         * while flagging the uncertainty via _tz_dst */
        for (i = 0; i < TZ_NAME_MAX; i++)
            _tzname[i] = tz.std_name[i];
        _tz_offset = negi32(tz.std_offset);
        _tz_dst = -1;
        return;
    }

    dst_status = _tz_is_dst_active(&tz, time(NULL));

    if (dst_status == 1) {
        for (i = 0; i < TZ_NAME_MAX; i++)
            _tzname[i] = tz.dst_name[i];
        _tz_offset = negi32(tz.dst_offset);
        _tz_dst = 1;
    } else if (dst_status == 0) {
        for (i = 0; i < TZ_NAME_MAX; i++)
            _tzname[i] = tz.std_name[i];
        _tz_offset = negi32(tz.std_offset);
        _tz_dst = 0;
    } else {
        for (i = 0; i < TZ_NAME_MAX; i++)
            _tzname[i] = tz.std_name[i];
        _tz_offset = negi32(tz.std_offset);
        _tz_dst = -1;
    }
}
