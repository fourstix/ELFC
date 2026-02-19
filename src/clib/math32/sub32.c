#define _ELFCLIB_
#include <math32.h>

/* 32-bit subtraction: result = a - b */
int32_t sub32(int32_t *a, int32_t *b) {
    int32_t result;

    if (a->low < b->low) {
        a->high--;
    }
    
    result.low = a->low - b->low;
    result.high = a->high - b->high;

    return result;
}
