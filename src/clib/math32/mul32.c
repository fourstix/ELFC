#include <math32.h>

/* 32-bit multiplication: result = a * b */
int32 mul32(int32 *a, int32 *b) {
    int32 result;
    unsigned int al, ah, bl, bh;
    unsigned int p0, p1, p2, p3;
    unsigned int carry;

    /* Extract words */
    al = a->low;
    ah = a->high;
    bl = b->low;
    bh = b->high;

    /* Calculate partial products */
    p0 = al * bl;           /* Low * Low */
    p1 = al * bh;           /* Low * High */
    p2 = ah * bl;           /* High * Low */
    p3 = ah * bh;           /* High * High (ignored, would be bits 32-63) */

    /* Result low word is just p0 low word */
    result.low = p0;

    /* Result high word is p0 high + p1 low + p2 low */
    result.high = (p0 >> 16);  /* High word of p0 */

    /* Add p1 low word */
    result.high = result.high + (p1 & 0xFFFF);

    /* Add p2 low word */
    carry = result.high;
    result.high = result.high + (p2 & 0xFFFF);

    /* Note: We ignore upper bits as they would exceed 32 bits */

    return result;
}
