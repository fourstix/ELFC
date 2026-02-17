#define _ELFCLIB_
#include <math32.h>

#pragma             extrn Cmul32
#pragma             extrn Cadd32
#pragma             extrn Csub32

/* Convert string to 32-bit integer (like atoi) */
int32 atoi32(const char *str) {
    int32 result;
    int32 ten;
    int32 digit;
    int negative = 0;
    const char *p;
    int32 zero;

    p = str;

    /* Initialize result to zero */
    result.low = 0;
    result.high = 0;

    /* Skip leading whitespace */
    while (*p == ' ' || *p == '\t' || *p == '\n') {
        p++;
    }

    /* Check for sign */
    if (*p == '-') {
        negative = 1;
        p++;
    } else if (*p == '+') {
        p++;
    }

    /* Initialize ten constant */
    ten.low = 10;
    ten.high = 0;

    /* Process digits */
    while (*p >= '0' && *p <= '9') {
        /* result = result * 10 + digit */
        result = mul32(&result, &ten);

        digit.low = *p - '0';
        digit.high = 0;

        result = add32(&result, &digit);

        p++;
    }

    /* Apply sign if negative */
    if (negative) {
        zero.low = 0;
        zero.high = 0;
        result = sub32(&zero, &result);
    }

    return result;
}
