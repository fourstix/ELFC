#ifndef _MATHU32_H_
#define _MATHU32_H_

/* include stdlib if not included already */
#ifndef _STDLIB_
#include <stdlib.h>
#endif

#ifndef _ELFCLIB_
#pragma .link .library mathu32.lib
#endif

#ifndef uint32
/* 32-bit number represented as two 16-bit values */
struct uint32 {
    unsigned int low;   /* Lower 16 bits */
    unsigned int high;  /* Upper 16 bits */
};

typedef struct uint32 uint32_t;

#define uint32
#endif

/* 32-bit addition: result = a + b */
uint32_t addu32(uint32_t a, uint32_t b);

/* 32-bit subtraction: result = a - b */
uint32_t subu32(uint32_t a, uint32_t b);

/* 32-bit multiplication: result = a * b */
uint32_t mulu32(uint32_t a, uint32_t b);

/* 2 x 16-bit multiplication: result = a * b */
uint32_t mulu32x16(uint32_t a, unsigned int b);

/* Compare two 32-bit numbers */
/* Returns: -1 if a < b, 0 if a == b, 1 if a > b */
int cmpu32(uint32_t a, uint32_t b);

/* Shift left by n bits */
uint32_t shlu32(uint32_t a, int n);

/* Shift right by n bits */
uint32_t shru32(uint32_t a, int n);

/* 32-bit division: result = a / b, optional remainder in *rem */
uint32_t divu32(uint32_t a, uint32_t b, uint32_t *rem);

/* Convert 16-bit integer to 32-bit integer with sign extension */
uint32_t tou32(unsigned int n);

/* Convert decimal string to 32-bit integer */
uint32_t atou32(const char *str);

/* Convert string in base to 32-bit integer */
/* When base = 0:
 *  0x prefix is hex
 *  0 prefix is octal
 *  otherwise decimal */
uint32_t strtou32(const char *nptr, char **endptr, int base);

/* Convert 32-bit integer to string */
/* Returns: pointer to beginning of string */
char *u32toa(uint32_t n, char *str);

#endif
