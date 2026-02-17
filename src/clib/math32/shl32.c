#define _ELFCLIB_
#include <math32.h>

/* Shift left by 1 bit */
int32 shl32(int32 *a) {
    int32 result;

    result.high = (a->high << 1) | (a->low >> 15);
    result.low = a->low << 1;

    return result;
}
