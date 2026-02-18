#define _ELFCLIB_
#include <math32.h>

#pragma             extrn Cneg32
#pragma             extrn Cadd32

/* 32-bit subtraction: result = a - b */
int32 sub32(int32 *a, int32 *b) {
    int32 result;
    int32 neg_b;

    neg_b = neg32(b);

    result = add32(a, &neg_b);

    return result;
}
