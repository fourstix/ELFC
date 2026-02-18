#define _ELFCLIB_
#include <math32.h>

#pragma             extrn Cadd32

int32 neg32(int32 *n)
{
    int32 inverse;
    int32 one;

    one.high = 0;
    one.low = 1;

    inverse.high = ~n->high;
    inverse.low = ~n->low;

    return add32(&inverse, &one);
}
