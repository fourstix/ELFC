#define _ELFCLIB_
#include <math32.h>

#pragma             extrn Cshl32
#pragma             extrn Csub32
#pragma             extrn Ccmp32

/* 32-bit division: returns quotient, remainder in *rem */
int32 div32(int32 *dividend, int32 *divisor, int32 *remainder) {
    int32 quotient;
    int32 rem;
    int32 temp;
    int i;

    /* Initialize */
    quotient.low = 0;
    quotient.high = 0;
    rem.low = 0;
    rem.high = 0;

    /* Handle division by zero */
    if (divisor->low == 0 && divisor->high == 0) {
        if (remainder) {
            remainder->low = 0;
            remainder->high = 0;
        }
        quotient.low = 0xFFFF;
        quotient.high = 0xFFFF;
        return quotient;
    }

    /* Shift and subtract algorithm */
    for (i = 31; i >= 0; i--) {
        /* Shift remainder left by 1 */
        rem = shl32(&rem);

        /* Bring down next bit from dividend */
        if (i >= 16) {
            /* Bit is in high word */
            if (dividend->high & (1 << (i - 16))) {
                rem.low |= 1;
            }
        } else {
            /* Bit is in low word */
            if (dividend->low & (1 << i)) {
                rem.low |= 1;
            }
        }

        /* Try to subtract divisor from remainder */
        if (cmp32(&rem, divisor) >= 0) {
            rem = sub32(&rem, divisor);

            /* Set bit in quotient */
            if (i >= 16) {
                quotient.high |= (1 << (i - 16));
            } else {
                quotient.low |= (1 << i);
            }
        }
    }

    /* Store remainder if requested */
    if (remainder) {
        *remainder = rem;
    }

    return quotient;
}
