#define _ELFCLIB_

#include <stdbool.h>
#include <math32.h>
#include <time.h>

/* define only extern procedures required */
#pragma           extrn Cu32_from_i32
#pragma           extrn Ci32_from_u32
#pragma           extrn Cdivi32
#pragma           extrn Caddu32
#pragma           extrn Ccmpi32
#pragma           extrn Caddi32
#pragma           extrn Csubi32
#pragma           extrn Cmuli32
#pragma           extrn Cmuli32x16
#pragma           extrn Ci32_from_int
#pragma           extrn Cint_from_i32
#pragma           extrn C_tz_dst
#pragma           extrn C_doy
#pragma           extrn C_dow

static /* const */ int32_t SECS_PER_DAY   = { 0x5180, 0x0001 }; /* 86400     */
static /* const */ int32_t DAYS_TO_EPOCH  = { 0x2539, 0x000B }; /* 730425    */
static /* const */ int32_t DAYS_PER_ERA   = { 0x3AB1, 0x0002 }; /* 146097    */
static /* const */ int32_t I32_36524      = { 0x8ECC, 0x0000 }; /* 36524     */
static /* const */ int32_t I32_146096     = { 0x3AB0, 0x0002 }; /* 146096    */
static /* const */ int32_t I32_ZERO  = { 0, 0 };
static /* const */ int32_t I32_ONE   = { 1, 0 };

static bool safe_add32(int32_t a, int32_t b, int32_t *out)
{
    uint32_t ua;
    uint32_t ub;
    uint32_t ur;
    int sa;
    int sb;
    int sr;

    ua = u32_from_i32(a);
    ub = u32_from_i32(b);
    ur = addu32(ua, ub);
    sa = (a.high >> 15) & 1;
    sb = (b.high >> 15) & 1;
    sr = (int)(ur.high >> 15) & 1;
    if (sa == sb && sr != sa) return false;
    *out = i32_from_u32(ur);
    return true;
}

void _time_t_to_tm(time_t ts, int32_t utc_offset_secs, struct tm *out)
{
    int32_t secs;
    int32_t days;
    int32_t rem;
    int32_t sec_rem;
    int32_t min_rem;
    int32_t z;
    int32_t era;
    int32_t doe;
    int32_t yoe_num;
    int32_t yoe;
    int32_t y;
    int32_t doy;
    int32_t mp;
    int32_t d;
    int32_t m;
    int imp;

    if (!safe_add32(ts, utc_offset_secs, &secs))
        return;

    days = divi32(secs, SECS_PER_DAY, &rem);
    if (cmpi32(rem, I32_ZERO) < 0) {
        rem  = addi32(rem, SECS_PER_DAY);
        days = subi32(days, I32_ONE);
    }

    rem = divi32(rem, i32_from_int(60), &sec_rem);
    out->tm_sec = int_from_i32(sec_rem);
    rem = divi32(rem, i32_from_int(60), &min_rem);
    out->tm_min  = int_from_i32(min_rem);
    out->tm_hour = int_from_i32(rem);

    z   = addi32(days, DAYS_TO_EPOCH);
    era = divi32(z, DAYS_PER_ERA, NULL);
    doe = subi32(z, muli32(era, DAYS_PER_ERA));

    yoe_num = subi32(
                addi32(
                    subi32(doe, divi32(doe, i32_from_int(1460),  NULL)),
                    divi32(doe, I32_36524, NULL)),
                divi32(doe, I32_146096, NULL));
    yoe = divi32(yoe_num, i32_from_int(365), NULL);

    y = addi32(yoe, muli32x16(era, 400));

    doy = subi32(doe,
            subi32(
                addi32(muli32x16(yoe, 365),
                       divi32(yoe, i32_from_int(4), NULL)),
                divi32(yoe, i32_from_int(100), NULL)));

    mp = divi32(
            addi32(muli32x16(doy, 5), i32_from_int(2)),
            i32_from_int(153), NULL);

    d = addi32(
            subi32(doy,
                divi32(
                    addi32(muli32x16(mp, 153), i32_from_int(2)),
                    i32_from_int(5), NULL)),
            I32_ONE);

    imp = int_from_i32(mp);
    m   = (imp < 10) ? addi32(mp, i32_from_int(2))
                     : subi32(mp, i32_from_int(10));

    if (imp >= 10) y = addi32(y, I32_ONE);

    out->tm_mday  = int_from_i32(d);
    out->tm_mon   = int_from_i32(m);
    out->tm_year  = int_from_i32(subi32(y, i32_from_int(1900)));
    out->tm_isdst = (_tz_dst >= 0) ? _tz_dst : -1;

    _doy(out);
    _dow(out);
}
