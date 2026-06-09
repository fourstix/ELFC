/*
 * test_time.c
 *
 * Test program for the 16-bit time functions.
 * Compiled and run on a host system to verify correctness.
 *
 * math32.h defines int32_t/uint32_t as structs — do NOT include stdint.h.
 * The math32 library stubs use native long arithmetic internally,
 * accessed via a local typedef to avoid naming conflicts.
 */

#include <string.h>
#include <stdio.h>
#include <math32.h>
#include <time.h>

/* 86400 */
static int32_t I32_86400 = { 0x5180, 0x0001 };

/* 31622400 */
static int32_t I32_31622400 = { 0x8500, 0x01E2 };

/* 5097600 */
static int32_t I32_5097600 = { 0xC880, 0x004D };

/* -86400 */
static int32_t I32_NEG_86400 = { 0xAE80, 0xFFFE };

/* ── systime stub ───────────────────────────────────────────────────────── */

int systime(struct tm *tp)
{
    /* Stubbed to 2024-03-15 14:30:00 local */
    tp->tm_year  = 124;
    tp->tm_mon   = 2;
    tp->tm_mday  = 15;
    tp->tm_hour  = 14;
    tp->tm_min   = 30;
    tp->tm_sec   = 0;
    tp->tm_isdst = 0;
    
    return 1;
}

/* ── test helpers ───────────────────────────────────────────────────────── */

static int tests_run  = 0;
static int tests_pass = 0;

static void check(const char *name, int pass)
{
    tests_run++;
    if (pass) {
        tests_pass++;
        printf("PASS: %s\n", name);
    } else {
        printf("FAIL: %s\n", name);
    }
}

/* ── tests ──────────────────────────────────────────────────────────────── */

static void test_timegm(void)
{
    static struct tm t;
    time_t result;

    t.tm_year=100; t.tm_mon=0; t.tm_mday=1;
    t.tm_hour=0;   t.tm_min=0; t.tm_sec=0;
    result = timegm(&t);
    check("timegm: epoch = 0", cmpi32(result, i32_from_int(0)) == 0);

    t.tm_year=100; t.tm_mon=0; t.tm_mday=2;
    t.tm_hour=0;   t.tm_min=0; t.tm_sec=0;
    result = timegm(&t);
    check("timegm: +1 day = 86400", cmpi32(result, I32_86400) == 0);

    t.tm_year=101; t.tm_mon=0; t.tm_mday=1;
    t.tm_hour=0;   t.tm_min=0; t.tm_sec=0;
    result = timegm(&t);
    check("timegm: 2001-01-01 = 31622400", cmpi32(result, I32_31622400) == 0);

    t.tm_year=99; t.tm_mon=11; t.tm_mday=31;
    t.tm_hour=23; t.tm_min=59; t.tm_sec=59;
    result = timegm(&t);
    check("timegm: 1999-12-31 23:59:59 = -1", cmpi32(result, i32_from_int(-1)) == 0);

    t.tm_year=100; t.tm_mon=1; t.tm_mday=29;
    t.tm_hour=0;   t.tm_min=0; t.tm_sec=0;
    result = timegm(&t);
    check("timegm: 2000-02-29 = 5097600", cmpi32(result, I32_5097600) == 0);

    t.tm_year=100; t.tm_mon=0; t.tm_mday=0;
    t.tm_hour=0;   t.tm_min=0; t.tm_sec=0;
    result = timegm(&t);
    check("timegm: mday=0 normalise = -86400", cmpi32(result, I32_NEG_86400) == 0);

    t.tm_year=100; t.tm_mon=0; t.tm_mday=1;
    t.tm_hour=0;   t.tm_min=0; t.tm_sec=61;
    result = timegm(&t);
    check("timegm: sec=61 normalise = 61", cmpi32(result, i32_from_int(61)) == 0);
}

static void test_gmtime(void)
{
    static struct tm t;
    struct tm *out;
    time_t ts;

    t.tm_year=100; t.tm_mon=0; t.tm_mday=1;
    t.tm_hour=0;   t.tm_min=0; t.tm_sec=0;
    ts = timegm(&t);
    out = gmtime(&ts);
    check("gmtime: epoch year=100", out->tm_year == 100);
    check("gmtime: epoch mon=0",    out->tm_mon  == 0);
    check("gmtime: epoch mday=1",   out->tm_mday == 1);
    check("gmtime: epoch hour=0",   out->tm_hour == 0);
    check("gmtime: epoch wday=6",   out->tm_wday == 6); /* Saturday */
    check("gmtime: epoch yday=0",   out->tm_yday == 0);

    t.tm_year=124; t.tm_mon=6; t.tm_mday=4;
    t.tm_hour=12;  t.tm_min=0; t.tm_sec=0;
    ts = timegm(&t);
    out = gmtime(&ts);
    check("gmtime: 2024-07-04 year=124", out->tm_year == 124);
    check("gmtime: 2024-07-04 mon=6",    out->tm_mon  == 6);
    check("gmtime: 2024-07-04 mday=4",   out->tm_mday == 4);
    check("gmtime: 2024-07-04 hour=12",  out->tm_hour == 12);
    check("gmtime: 2024-07-04 wday=4",   out->tm_wday == 4); /* Thursday */

    t.tm_year=99; t.tm_mon=5; t.tm_mday=15;
    t.tm_hour=0;  t.tm_min=0; t.tm_sec=0;
    ts = timegm(&t);
    out = gmtime(&ts);
    check("gmtime: 1999-06-15 year=99",  out->tm_year == 99);
    check("gmtime: 1999-06-15 mon=5",    out->tm_mon  == 5);
    check("gmtime: 1999-06-15 mday=15",  out->tm_mday == 15);
}

static void test_mktime_localtime(void)
{
    static struct tm t;
    struct tm *out;
    time_t ts;

    /* UTC+5:30 */
    _tz_hr=5; _tz_min=30; _tz_dst=0;

    t.tm_year=100; t.tm_mon=0; t.tm_mday=1;
    t.tm_hour=5;   t.tm_min=30; t.tm_sec=0;
    ts = mktime(&t);
    check("mktime: UTC+5:30 epoch", cmpi32(ts, i32_from_int(0)) == 0);

    ts.low=0; ts.high=0;
    out = localtime(&ts);
    check("localtime: UTC+5:30 hour=5",  out->tm_hour == 5);
    check("localtime: UTC+5:30 min=30",  out->tm_min  == 30);
    check("localtime: UTC+5:30 mday=1",  out->tm_mday == 1);

    /* UTC-8 */
    _tz_hr=-8; _tz_min=0; _tz_dst=0;

    t.tm_year=99;  t.tm_mon=11; t.tm_mday=31;
    t.tm_hour=16;  t.tm_min=0;  t.tm_sec=0;
    ts = mktime(&t);
    check("mktime: UTC-8 epoch", cmpi32(ts, i32_from_int(0)) == 0);

    ts.low=0; ts.high=0;
    out = localtime(&ts);
    check("localtime: UTC-8 year=99",  out->tm_year == 99);
    check("localtime: UTC-8 mon=11",   out->tm_mon  == 11);
    check("localtime: UTC-8 mday=31",  out->tm_mday == 31);
    check("localtime: UTC-8 hour=16",  out->tm_hour == 16);

    _tz_hr=0; _tz_min=0;
}

static void test_ctime(void)
{
    static struct tm t;
    time_t ts;
    char *s;

    _tz_hr=0; _tz_min=0; _tz_dst=0;

    t.tm_year=100; t.tm_mon=0; t.tm_mday=1;
    t.tm_hour=0;   t.tm_min=0; t.tm_sec=0;
    ts = timegm(&t);
    s = ctime(&ts);
    check("ctime: not NULL", s != NULL);
    check("ctime: epoch string",
          strcmp(s, "Sat Jan  1 00:00:00 2000\n") == 0);
    if (strcmp(s, "Sat Jan  1 00:00:00 2000\n") != 0)
        printf("  got: %s", s);

    t.tm_year=124; t.tm_mon=2; t.tm_mday=15;
    t.tm_hour=14;  t.tm_min=30; t.tm_sec=0;
    ts = timegm(&t);
    s = ctime(&ts);
    check("ctime: 2024-03-15",
          strcmp(s, "Fri Mar 15 14:30:00 2024\n") == 0);
    if (strcmp(s, "Fri Mar 15 14:30:00 2024\n") != 0)
        printf("  got: %s", s);
}

static void test_time(void)
{
    time_t ts;
    time_t ts2;
    struct tm *out;

    /* systime returns 2024-03-15 14:30:00 local, UTC+5:30 */
    _tz_hr=5; _tz_min=30; _tz_dst=0;

    ts = time(NULL);
    ts2.low=0; ts2.high=0;
    time(&ts2);
    check("time: NULL and ptr agree", cmpi32(ts, ts2) == 0);

    out = gmtime(&ts);
    check("time: UTC hour=9",   out->tm_hour == 9);
    check("time: UTC min=0",    out->tm_min  == 0);
    check("time: UTC mday=15",  out->tm_mday == 15);
    check("time: UTC mon=2",    out->tm_mon  == 2);
    check("time: UTC year=124", out->tm_year == 124);

    _tz_hr=0; _tz_min=0;
}

/* ── main ───────────────────────────────────────────────────────────────── */

int main(void)
{
    printf("=== Time Function Tests ===\n\n");

    printf("--- timegm ---\n");
    test_timegm();

    printf("\n--- gmtime ---\n");
    test_gmtime();

    printf("\n--- mktime / localtime ---\n");
    test_mktime_localtime();

    printf("\n--- ctime ---\n");
    test_ctime();

    printf("\n--- time ---\n");
    test_time();

    printf("\n=== %d/%d tests passed ===\n", tests_pass, tests_run);
    return (tests_pass == tests_run) ? 0 : 1;
}
