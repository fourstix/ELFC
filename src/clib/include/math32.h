#ifndef _MATH32_H_
#define _MATH32_H_

#ifndef _ELFCLIB_
#pragma .link .library math32.lib
#endif

/* 32-bit number represented as two 16-bit values */
typedef struct int32 {
    unsigned int low;   /* Lower 16 bits */
    unsigned int high;  /* Upper 16 bits */
} int32;

/* 32-bit addition: result = a + b */
int32 add32(int32 *a, int32 *b);

/* 32-bit subtraction: result = a - b */
int32 sub32(int32 *a, int32 *b);

/* 32-bit multiplication: result = a * b */
int32 mul32(int32 *a, int32 *b);

/* Compare two 32-bit numbers */
/* Returns: -1 if a < b, 0 if a == b, 1 if a > b */
int cmp32(int32 *a, int32 *b);

/* Shift left by 1 bit */
int32 shl32(int32 *a);

/* Shift right by 1 bit */
int32 shr32(int32 *a);

/* 32-bit division: returns quotient, remainder in *rem */
int32 div32(int32 *dividend, int32 *divisor, int32 *remainder);

/* Convert 16-bit number to 32-bit number with sign extension */
int32 to_int32(int n);

/* Negate a 32-bit number */
int32 neg32(int32 *n);

/* Convert string to 32-bit integer */
int32 atoi32(const char *str);

/* Convert 32-bit integer to string */
/* Returns: pointer to beginning of string */
char *itoa32(int32 *n, char *str);

#endif
