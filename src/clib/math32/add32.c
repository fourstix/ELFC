#define _ELFCLIB_
#include <math32.h>

/* 32-bit addition: result = a + b */
int32_t add32(int32_t *a, int32_t *b) {
    int32_t result;

    result.low = a->low + b->low;

    if (result.low < a->low) {
        a->high++;
    }

    result.high = a->high + b->high;

    return result;
}
