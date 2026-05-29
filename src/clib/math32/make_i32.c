#define _ELFCLIB_
#include <math32.h>

int32_t make_i32(uint16_t high, uint16_t low)
{
    int32_t r;
    r.high = high;
    r.low = low;
    return r;
}
