#define _ELFCLIB_
#include <math32.h>

/* Shift right by 1 bit */
int32 shr32(int32 *a) {
    int32 result;

    result.low = a->low;
    result.high = a->high;

    result.low >>= 1;
    if (result.high & 0x0001) {
        result.low |= 0x8000;
    }
    result.high >>= 1;

    return result;
}
