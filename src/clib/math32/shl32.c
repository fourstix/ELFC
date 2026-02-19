#define _ELFCLIB_
#include <math32.h>

/* Shift left by 1 bit */
int32_t shl32(int32_t *a) {
    int32_t result;
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
