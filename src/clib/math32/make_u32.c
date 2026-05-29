#define _ELFCLIB_
#include <math32.h>

uint32_t make_u32(uint16_t high, uint16_t low)
{
    uint32_t r;
    r.high = high;
    r.low = low;
    return r;
}
