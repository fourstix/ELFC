#define _ELFCLIB_
#include <math32.h>

int int_from_i32(int32_t v)
{
    return (int)(v.low);
}
