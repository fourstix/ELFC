#define _ELFCLIB_
#include <math32.h>

/* 32-bit addition: result = a + b */
int32 add32(int32 *a, int32 *b) {
    int32 result;
    unsigned int carry;

    /* Add low words */
    result.low = a->low + b->low;

    /* Check for carry (overflow in low word) */
    carry = (result.low < a->low) ? 1 : 0;

    /* Add high words with carry */
    result.high = a->high + b->high + carry;

    return result;
}
