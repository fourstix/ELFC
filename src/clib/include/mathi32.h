#ifndef _MATHI32_H_
#define _MATHI32_H_

/* include stdlib if not included already */
#ifndef _STDLIB_
#include <stdlib.h>
#endif

#ifndef _ELFCLIB_
#pragma .link .library mathi32.lib
#endif

#ifndef int32
/* 32-bit number represented as two 16-bit values */
struct int32 {
    unsigned int low;   /* Lower 16 bits */
    unsigned int high;  /* Upper 16 bits */
};

typedef struct int32 int32_t;

#define int32
#endif

/* 32-bit addition: result = a + b */
int32_t addi32(int32_t a, int32_t b);

/* 32-bit subtraction: result = a - b */
int32_t subi32(int32_t a, int32_t b);

/* 32-bit multiplication: result = a * b */
int32_t muli32(int32_t a, int32_t b);

/* 2 x 16-bit multiplication: result = a * b */
int32_t muli32x16(int32_t a, int b);

/* Compare two 32-bit numbers */
/* Returns: -1 if a < b, 0 if a == b, 1 if a > b */
int cmpi32(int32_t a, int32_t b);

/* Shift left by n bits */
int32_t shli32(int32_t a, int n);

/* Shift right by n bits */
int32_t shri32(int32_t a, int n);

/* Arithmetic shift right by n bits */
int32_t asri32(int32_t a, int n);

/* 32-bit division: result = a / b, optional remainder in *rem */
int32_t divi32(int32_t a, int32_t b, int32_t *rem);

/* Convert 16-bit integer to 32-bit integer with sign extension */
int32_t toi32(int n);

/* Negate a 32-bit number: result = -a */
int32_t negi32(int32_t n);

/* Absolute value of a 32-bit integer: result = |a| */
int32_t absi32(int32_t a);

/* Convert decimal string to 32-bit integer */
int32_t atoi32(const char *str);

/* Convert string in base to 32-bit integer */
/* When base = 0:
 *  0x prefix is hex
 *  0 prefix is octal
 *  otherwise decimal */
int32_t strtoi32(const char *nptr, char **endptr, int base);

/* Convert 32-bit integer to string */
/* Returns: pointer to beginning of string */
char *i32toa(int32_t n, char *str);

#endif
