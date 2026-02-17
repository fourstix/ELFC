#define _ELFCLIB_
#include <math32.h>

/* Convert 16-bit number to 32-bit number with sign extension */
int32 to_int32(int n) {
    int32 result;

    result.low = n;
    result.high = ((n & 0x8000) == 0) ? 0x0000 : 0xffff;

    return result;
}
