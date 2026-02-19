#define _ELFCLIB_
#include <math32.h>

/* Shift right by 1 bit */
int32_t shr32(int32_t *a) {
    int32_t result;

    result.low = a->low;
    result.high = a->high;

    result.low >>= 1;
    if (result.high & 0x0001) {
        result.low |= 0x8000;
    }
    result.high >>= 1;

    return result;
}
