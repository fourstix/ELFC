#define _ELFCLIB_
#include <math32.h>

/* 32-bit addition: result = a + b */
int32 add32(int32 *a, int32 *b) {
    int32 result;

    result.low = a->low + b->low;

    if (result.low < a->low) {
        a->high++;
    }

    result.high = a->high + b->high;

    return result;
}
