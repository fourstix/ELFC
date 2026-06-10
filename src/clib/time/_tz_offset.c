#define _ELFCLIB_

#include <math32.h>
#include <time.h>

/* define only extern procedures required */
#pragma           extrn Cmuli32x16
#pragma           extrn Ci32_from_int
#pragma           extrn Caddi32
#pragma           extrn C_tz_hr
#pragma           extrn C_tz_min
#pragma           extrn C_tz_dst

#define SECS_PER_MIN    60
#define SECS_PER_HOUR   3600

int32_t _tz_offset(void)
{
    int32_t off;
    off = muli32x16(i32_from_int(_tz_hr),  SECS_PER_HOUR);
    off = addi32(off, muli32x16(i32_from_int(_tz_min), SECS_PER_MIN));
    if (_tz_dst == 1) {
        off = addi32(off, i32_from_int(SECS_PER_HOUR));
    }
    return off;
}
