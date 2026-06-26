#define _ELFCLIB_

#include <stdlib.h>
#include <math32.h>
#include <ctype.h>
#include <time.h>

#pragma extrn Cisalpha
#pragma extrn Cisdigit
#pragma extrn Ci32_from_int
#pragma extrn Cmuli32x16
#pragma extrn Caddi32
#pragma extrn Csubi32
#pragma extrn Cnegi32

/*
 * parse_name: read a zone name into buf (max TZ_NAME_MAX-1 chars).
 * Accepts either a run of alphabetic characters, or a <...>-quoted
 * run of any characters except '>' (the angle brackets are not
 * copied into buf). Returns pointer to the character after the
 * name, or NULL on malformed input.
 */
static const char *_parse_name(const char *p, char *buf)
{
    int n;

    n = 0;

    if (*p == '<') {
        p++;
        while (*p != '>' && *p != '\0') {
            if (n < TZ_NAME_MAX - 1) {
                buf[n] = *p;
                n++;
            }
            p++;
        }
        if (*p != '>')
            return NULL;
        p++;
    } else {
        if (!isalpha(*p))
            return NULL;
        while (isalpha(*p)) {
            if (n < TZ_NAME_MAX - 1) {
                buf[n] = *p;
                n++;
            }
            p++;
        }
    }

    buf[n] = '\0';
    return p;
}

/*
 * parse_uint: read a run of digits as an unsigned 16-bit int.
 * Returns pointer after the digits, or NULL if no digits found.
 */
static const char *_parse_uint(const char *p, int *out)
{
    int v;

    if (!isdigit(*p))
        return NULL;

    v = 0;
    while (isdigit(*p)) {
        v = v * 10 + (*p - '0');
        p++;
    }

    *out = v;
    return p;
}

/*
 * parse_offset: read [+|-]hh[:mm[:ss]] and return the value in
 * seconds (POSIX sign convention preserved: no sign or '+' is
 * positive, meaning west of UTC / add to local to get UTC).
 */
static const char *_parse_offset(const char *p, int32_t *out)
{
    int sign;
    int hh;
    int mm;
    int ss;
    int32_t total;

    sign = 1;
    if (*p == '+') {
        p++;
    } else if (*p == '-') {
        sign = -1;
        p++;
    }

    hh = 0;
    mm = 0;
    ss = 0;

    p = _parse_uint(p, &hh);
    if (p == NULL)
        return NULL;

    if (*p == ':') {
        p++;
        p = _parse_uint(p, &mm);
        if (p == NULL)
            return NULL;

        if (*p == ':') {
            p++;
            p = _parse_uint(p, &ss);
            if (p == NULL)
                return NULL;
        }
    }

    total = i32_from_int(hh);
    total = muli32x16(total, 3600);
    total = addi32(total, i32_from_int(mm * 60 + ss));

    if (sign < 0)
        total = negi32(total);

    *out = total;
    return p;
}

/*
 * _parse_rule_date: read Mm.w.d and return month/week/day.
 * Only the M-form (Julian day forms Jn / n are not supported, since
 * this platform's library is built around month/week/day rules).
 */
static const char *_parse_rule_date(const char *p, int *month, int *week,
                                    int *day)
{
    int m;
    int w;
    int d;

    if (*p != 'M')
        return NULL;
    p++;

    p = _parse_uint(p, &m);
    if (p == NULL || *p != '.')
        return NULL;
    p++;

    p = _parse_uint(p, &w);
    if (p == NULL || *p != '.')
        return NULL;
    p++;

    p = _parse_uint(p, &d);
    if (p == NULL)
        return NULL;

    if (m < 1 || m > 12 || w < 1 || w > 5 || d < 0 || d > 6)
        return NULL;

    *month = m;
    *week  = w;
    *day   = d;
    return p;
}

/*
 * parse_rule_time: read an optional /hh[:mm[:ss]] transition time.
 * If no '/' is present, *out is set to the default of 02:00:00
 * (7200 seconds) and p is returned unchanged.
 */
static const char *_parse_rule_time(const char *p, int32_t *out)
{
    int32_t two_am;

    if (*p != '/') {
        two_am.low  = 7200 & 0xFFFF;
        two_am.high = 0;
        *out = two_am;
        return p;
    }

    p++;
    return _parse_offset(p, out);
}

int _tz_parse(const char *tz, struct tz_parsed *out)
{
    const char *p;
    int32_t one_hour;
    
    if (tz == NULL || *tz == '\0')
        return 0;

    out->has_dst  = 0;
    out->has_rule = 0;

    p = _parse_name(tz, out->std_name);
    if (p == NULL)
        return 0;

    p = _parse_offset(p, &out->std_offset);
    if (p == NULL)
        return 0;

    if (*p == '\0')
        return 1;                /* no DST component: e.g. "UTC0" */

    /* DST name present */
    p = _parse_name(p, out->dst_name);
    if (p == NULL)
        return 0;
    out->has_dst = 1;

    if (*p != '\0' && *p != ',') {
        /* explicit DST offset given */
        p = _parse_offset(p, &out->dst_offset);
        if (p == NULL)
            return 0;
    } else {
        /* default: standard offset minus one hour */
        one_hour.low  = 3600 & 0xFFFF;
        one_hour.high = 0;
        out->dst_offset = subi32(out->std_offset, one_hour);
    }

    if (*p == '\0')
        return 1;                /* DST name/offset but no rule: unknown */

    if (*p != ',')
        return 0;
    p++;

    p = _parse_rule_date(p, &out->start_month, &out->start_week,
                         &out->start_day);
    if (p == NULL)
        return 0;
    p = _parse_rule_time(p, &out->start_time);
    if (p == NULL)
        return 0;

    if (*p != ',')
        return 0;
    p++;

    p = _parse_rule_date(p, &out->end_month, &out->end_week, &out->end_day);
    if (p == NULL)
        return 0;
    p = _parse_rule_time(p, &out->end_time);
    if (p == NULL)
        return 0;

    if (*p != '\0')
        return 0;                /* trailing garbage */

    out->has_rule = 1;
    return 1;
}
