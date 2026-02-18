#define _ELFCLIB_
#include <math32.h>

#pragma             extrn Csub32
#pragma             extrn Cdiv32

/* Convert 32-bit integer to string (like itoa) */
/* Returns pointer to the beginning of the string */
char *itoa32(int32 *n, char *str) {
    char temp[12];  /* Max 10 digits + sign + null */
    int i = 0;
    int j = 0;
    int negative = 0;
    int32 zero, ten, remainder;

    /* Initialize constants */
    zero.low = 0;
    zero.high = 0;
    ten.low = 10;
    ten.high = 0;

    /* Handle negative numbers (check if high bit is set) */
    if (n->high & 0x8000) {
        negative = 1;
        *n = sub32(&zero, n);
    }

    /* Handle zero specially */
    if (n->low == 0 && n->high == 0) {
        str[0] = '0';
        str[1] = '\0';
        return str;
    }

    /* Extract digits in reverse order */
    while (n->low != 0 || n->high != 0) {
        *n = div32(n, &ten, &remainder);
        temp[i++] = '0' + remainder.low;
    }

    /* Add negative sign if needed */
    if (negative) {
        temp[i++] = '-';
    }

    /* Reverse the string */
    while (i > 0) {
        str[j++] = temp[--i];
    }
    str[j] = '\0';

    return str;
}
