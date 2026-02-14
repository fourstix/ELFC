#include <math32.h>

/* Shift right by 1 bit */
int32 shr32(int32 *a) {
    int32 result;

    result.low = (a->low >> 1) | (a->high << 15);
    result.high = a->high >> 1;

    return result;
}
