#define _ELFCLIB_

#include <stdbool.h>
#include <math32.h>
#include <time.h>

/* define only extern procedures required */
#pragma           extrn Cu32_from_i32
#pragma           extrn Ci32_from_u32
#pragma           extrn Ci32_from_int
#pragma           extrn Cint_from_i32
#pragma           extrn Csubu32
#pragma           extrn Csubi32
#pragma           extrn Caddi32
#pragma           extrn Cdivi32
#pragma           extrn Ccmpi32
#pragma           extrn Cmuli32x16
#pragma           extrn Caddu32
#pragma           extrn Cmulu32
#pragma           extrn Ccmpu32
#pragma           extrn C_tz_dst
#pragma           extrn C_doy
#pragma           extrn C_dow

#define SECS_PER_MIN    60
#define SECS_PER_HOUR   3600

static /* const */ int32_t SECS_PER_DAY   = { 0x5180, 0x0001 }; /* 86400     */
static /* const */ int32_t DAYS_TO_EPOCH  = { 0x2539, 0x000B }; /* 730425    */
static /* const */ uint32_t U32_INT32_MAX = { 0xFFFF, 0x7FFF }; /* 0x7FFFFFFF */
static /* const */ uint32_t U32_80000000  = { 0x0000, 0x8000 }; /* 0x80000000 */
static /* const */ int32_t I32_ZERO  = { 0, 0 };
static /* const */ int32_t I32_ONE   = { 1, 0 };
static /* const */ int32_t I32_NEG1  = { 0xFFFF, 0xFFFF };

static const uint8_t days_in_month[2][12] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
    31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static const int cum_days_from_mar[12] = {
    0, 31, 61, 92, 122, 153, 184, 214, 245, 275, 306, 337
};

static bool safe_sub32(int32_t a, int32_t b, int32_t *out)
{
    uint32_t ua;
    uint32_t ub;
    uint32_t ur;
    int sa;
    int sb;
    int sr;

    ua = u32_from_i32(a);
    ub = u32_from_i32(b);
    ur = subu32(ua, ub);
    sa = (a.high >> 15) & 1;
    sb = (b.high >> 15) & 1;
    sr = (int)(ur.high >> 15) & 1;
    if (sa != sb && sr != sa) return false;
    *out = i32_from_u32(ur);
    return true;
}

static int32_t days_since_pg_epoch(int32_t year, int32_t mon, int32_t mday)
{
    int32_t days;

    if (int_from_i32(mon) < 2) {
        year = subi32(year, I32_ONE);
        mon  = addi32(mon, i32_from_int(10));
    } else {
        mon = subi32(mon, i32_from_int(2));
    }

    days = muli32x16(year, 365);
    days = addi32(days, divi32(year, i32_from_int(4),   NULL));
    days = subi32(days, divi32(year, i32_from_int(100), NULL));
    days = addi32(days, divi32(year, i32_from_int(400), NULL));
    days = addi32(days, i32_from_int(cum_days_from_mar[int_from_i32(mon)]));
    days = addi32(days, subi32(mday, I32_ONE));
    return days;
}

static bool is_leap(int32_t y)
{
    int32_t rem;
    divi32(y, i32_from_int(4), &rem);
    if (cmpi32(rem, I32_ZERO) != 0) return false;
    divi32(y, i32_from_int(100), &rem);
    if (cmpi32(rem, I32_ZERO) != 0) return true;
    divi32(y, i32_from_int(400), &rem);
    return (cmpi32(rem, I32_ZERO) == 0);
}

static void normalise_tm(struct tm *t)
{
    int32_t sec;
    int32_t min;
    int32_t hour;
    int32_t mday;
    int32_t mon;
    int32_t year;
    int32_t carry;
    int32_t rem;

    sec  = i32_from_int(t->tm_sec);
    min  = i32_from_int(t->tm_min);
    hour = i32_from_int(t->tm_hour);
    mday = i32_from_int(t->tm_mday);
    mon  = i32_from_int(t->tm_mon);
    year = addi32(i32_from_int(t->tm_year), i32_from_int(1900));

    carry = divi32(sec, i32_from_int(SECS_PER_MIN), &rem);
    min   = addi32(min, carry);
    sec   = rem;
    if (cmpi32(sec, I32_ZERO) < 0) {
        sec = addi32(sec, i32_from_int(SECS_PER_MIN));
        min = subi32(min, I32_ONE);
    }

    carry = divi32(min, i32_from_int(60), &rem);
    hour  = addi32(hour, carry);
    min   = rem;
    if (cmpi32(min, I32_ZERO) < 0) {
        min  = addi32(min, i32_from_int(60));
        hour = subi32(hour, I32_ONE);
    }

    carry = divi32(hour, i32_from_int(24), &rem);
    mday  = addi32(mday, carry);
    hour  = rem;
    if (cmpi32(hour, I32_ZERO) < 0) {
        hour = addi32(hour, i32_from_int(24));
        mday = subi32(mday, I32_ONE);
    }

    carry = divi32(mon, i32_from_int(12), &rem);
    year  = addi32(year, carry);
    mon   = rem;
    if (cmpi32(mon, I32_ZERO) < 0) {
        mon  = addi32(mon, i32_from_int(12));
        year = subi32(year, I32_ONE);
    }

    while (cmpi32(mday, I32_ONE) < 0) {
        mon = subi32(mon, I32_ONE);
        if (cmpi32(mon, I32_ZERO) < 0) {
            mon  = i32_from_int(11);
            year = subi32(year, I32_ONE);
        }
        mday = addi32(mday,
               i32_from_int(days_in_month[is_leap(year) ? 1 : 0][int_from_i32(mon)]));
    }
    while (cmpi32(mday,
           i32_from_int(
               days_in_month[is_leap(year) ? 1 : 0][int_from_i32(mon)])) > 0) {
        mday = subi32(mday,
               i32_from_int(days_in_month[is_leap(year) ? 1 : 0][int_from_i32(mon)]));
        mon  = addi32(mon, I32_ONE);
        if (cmpi32(mon, i32_from_int(11)) > 0) {
            mon  = I32_ZERO;
            year = addi32(year, I32_ONE);
        }
    }

    t->tm_sec  = int_from_i32(sec);
    t->tm_min  = int_from_i32(min);
    t->tm_hour = int_from_i32(hour);
    t->tm_mday = int_from_i32(mday);
    t->tm_mon  = int_from_i32(mon);
    t->tm_year = int_from_i32(subi32(year, i32_from_int(1900)));

    _doy(t);
    _dow(t);
}

time_t _tm_to_time_t(struct tm *t, int32_t utc_offset_secs)
{
    int32_t pg_days;
    int32_t days;
    int32_t tod;
    int32_t secs;
    uint32_t ud;
    uint32_t uspd;
    uint32_t utod;
    uint32_t secs_u;

    normalise_tm(t);
    t->tm_isdst = (_tz_dst >= 0) ? _tz_dst : t->tm_isdst;

    pg_days = days_since_pg_epoch(
                  addi32(i32_from_int(t->tm_year), i32_from_int(1900)),
                  i32_from_int(t->tm_mon),
                  i32_from_int(t->tm_mday));

    if (!safe_sub32(pg_days, DAYS_TO_EPOCH, &days))
        return I32_NEG1;

    tod = addi32(
            addi32(
                muli32x16(i32_from_int(t->tm_hour), SECS_PER_HOUR),
                muli32x16(i32_from_int(t->tm_min),  SECS_PER_MIN)),
            i32_from_int(t->tm_sec));

    ud     = u32_from_i32(days);
    uspd   = u32_from_i32(SECS_PER_DAY);
    utod   = u32_from_i32(tod);
    secs_u = addu32(mulu32(ud, uspd), utod);

    if (cmpi32(days, I32_ZERO) > 0) {
        if (cmpu32(secs_u, U32_INT32_MAX) > 0) return I32_NEG1;
    }
    if (cmpi32(days, I32_ZERO) < 0) {
        if (cmpu32(secs_u, U32_80000000) < 0) return I32_NEG1;
    }

    secs = i32_from_u32(secs_u);

    if (!safe_sub32(secs, utc_offset_secs, &secs))
        return I32_NEG1;

    return secs;
}
