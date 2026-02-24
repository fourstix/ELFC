#ifndef _MATH32_H_
#define _MATH32_H_

#ifndef _ELFCLIB_
#pragma .link .library math32.lib
#endif

/* 32-bit number represented as two 16-bit values */
typedef struct int32 {
    unsigned int low;   /* Lower 16 bits */
    unsigned int high;  /* Upper 16 bits */
} int32_t;

/* 32-bit addition: result = a + b */
int32_t add32(int32_t *a, int32_t *b);

/* 32-bit subtraction: result = a - b */
int32_t sub32(int32_t *a, int32_t *b);

/* 32-bit multiplication: result = a * b */
int32_t mul32(int32_t *a, int32_t *b);

/* Compare two 32-bit numbers */
/* Returns: -1 if a < b, 0 if a == b, 1 if a > b */
int cmp32(int32_t *a, int32_t *b);

/* Shift left by 1 bit */
int32_t shl32(int32_t *a);

/* Shift right by 1 bit */
int32_t shr32(int32_t *a);

/* 32-bit division: returns quotient, remainder in *rem */
int32_t div32(int32_t *a, int32_t *b, int32_t *rem);

/* Convert 16-bit number to 32-bit number with sign extension */
int32_t to_int32(int n);

/* Negate a 32-bit number */
int32_t neg32(int32_t *n);

/* Convert string to 32-bit integer */
int32_t atoi32(const char *str);

/* Convert 32-bit integer to string */
/* Returns: pointer to beginning of string */
char *itoa32(int32_t *n, char *str);

/* Convert string to 32-bit integer */
int32_t strtoi32(const char *nptr, char **endptr, int base);

#endif

