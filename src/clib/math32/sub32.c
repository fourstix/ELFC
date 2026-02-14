#include <math32.h>

/* 32-bit subtraction: result = a - b */
int32 sub32(int32 *a, int32 *b) {
    int32 result;
    unsigned int borrow;

    /* Subtract low words */
    result.low = a->low - b->low;

    /* Check for borrow (underflow in low word) */
    borrow = (result.low > a->low) ? 1 : 0;

    /* Subtract high words with borrow */
    result.high = a->high - b->high - borrow;

    return result;
}
