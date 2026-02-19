#define _ELFCLIB_
#include <math32.h>

#pragma             extrn Cadd32

int32_t neg32(int32_t *n)
{
    int32_t inverse;
    int32_t one;

    one.high = 0;
    one.low = 1;

    inverse.high = ~n->high;
    inverse.low = ~n->low;

    return add32(&inverse, &one);
}
