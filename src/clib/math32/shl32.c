#define _ELFCLIB_
#include <math32.h>

/* Shift left by 1 bit */
int32 shl32(int32 *a) {
    int32 result;
    unsigned int carry;

    result.low = a->low;
    result.high = a->high;

    result.high <<= 1;
    if (result.low & 0x8000) {
        result.high |= 0x0001; // Carry into the low bit of high
    }
    result.low <<= 1;

    return result;
}
