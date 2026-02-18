#define _ELFCLIB_
#include <stdlib.h>
#include <math32.h>
#include <stdbool.h>

#pragma             extrn Cneg32

/* 32-bit division: returns quotient, remainder in *rem */
int32 div32(int32 *a, int32 *b, int32 *rem) {
    int32 quotient;
    int32 dividend;
    int32 divisor;
    int32 remainder;
    int i;
    bool sign_dividend;
    bool sign_divisor;
    bool ge;

    if (a->high & 0x8000) {
        dividend = neg32(a);
        sign_dividend = true;
    }
    else {
        dividend.high = a->high;
        dividend.low = a->low;
        sign_dividend = false;
    }

    if (b->high & 0x8000) {
        divisor = neg32(b);
        sign_divisor = true;
    }
    else {
        divisor.high = b->high;
        divisor.low = b->low;
        sign_divisor = false;
    }

    remainder.high = 0;
    remainder.low = 0;

    // Check for division by zero
    if (divisor.high == 0 && divisor.low == 0) {
        // Handle error: division by zero
        // Currently we return 0 and set the remainder to dividend
        if (rem != NULL) {
            rem->high = a->high;
            rem->low = a->low;
        }
        return divisor;
    }

    // Binary long division algorithm (32 iterations for 32 bits)
    for (i = 0; i < 32; i++) {
        remainder.high = (remainder.high << 1) | (remainder.low >> 15);
        remainder.low = (remainder.low << 1) | (dividend.high >> 15);
        dividend.high = (dividend.high << 1) | (dividend.low >> 15);
        dividend.low <<= 1;

        ge = false;
        if (remainder.high > divisor.high) {
            ge = true;
        }
        else if (remainder.high == divisor.high) {
            if (remainder.low >= divisor.low) {
                ge = true;
            }
        }

        if (ge) {
            if (remainder.low  < divisor.low) {
                remainder.high--;
            }
            remainder.low -= divisor.low;
            remainder.high -= divisor.high;

            dividend.low |= 1;
        }
    }

    // Dividend contains the quotient

    if (sign_dividend != sign_divisor) {
        dividend = neg32(&dividend);
    }

    if (rem != NULL) {
        if (sign_dividend) {
            remainder = neg32(&remainder);
        }

        rem->high = remainder.high;
        rem->low = remainder.low;
    }
  
    return dividend;
}
