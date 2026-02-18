#define _ELFCLIB_
#include <math32.h>

/* 32-bit subtraction: result = a - b */
int32 sub32(int32 *a, int32 *b) {
    int32 result;

    if (a->low < b->low) {
        a->high--;
    }
    
    result.low = a->low - b->low;
    result.high = a->high - b->high;

    return result;
}
