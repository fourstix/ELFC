#ifndef _MATH32_H_
#define _MATH32_H_

#include <stdint.h>

#ifndef _ELFCLIB_
#pragma .link .library math32.lib
#endif

/* 32-bit signed number represented as two 16-bit values */
struct int32 {
    unsigned int low;   /* Lower 16 bits */
    unsigned int high;  /* Upper 16 bits */
};

typedef struct int32 int32_t;

/* 32-bit unsigned number represented as two 16-bit values */
struct uint32 {
    unsigned int low;   /* Lower 16 bits */
    unsigned int high;  /* Upper 16 bits */
};

typedef struct uint32 uint32_t;

/* Cast int to 32-bit number */
int32_t i32_from_int(int v);
uint32_t u32_from_uint(unsigned int v);

/* Cast 32-bit number to int */
int int_from_i32(int32_t v);
unsigned int uint_from_u32(uint32_t v);

/* Concatenate two 16-bit unsigned numbers to 32-bit */
int32_t make_i32(uint16_t high, uint16_t low);
uint32_t make_u32(uint16_t high, uint16_t low);

/* Cast between signed and unsigned */
int32_t i32_from_u32(uint32_t v);
uint32_t u32_from_i32(int32_t v);

/* 32-bit addition: result = a + b */
int32_t addi32(int32_t a, int32_t b);
uint32_t addu32(uint32_t a, uint32_t b);

/* 32-bit subtraction: result = a - b */
int32_t subi32(int32_t a, int32_t b);
uint32_t subu32(uint32_t a, uint32_t b);

/* 32-bit multiplication: result = a * b */
int32_t muli32(int32_t a, int32_t b);
uint32_t mulu32(uint32_t a, uint32_t b);

/* 2 x 16-bit multiplication: result = a * b */
int32_t muli32x16(int32_t a, int b);
uint32_t mulu32x16(uint32_t a, unsigned int b);

/* Compare two 32-bit numbers */
/* Returns: -1 if a < b, 0 if a == b, 1 if a > b */
int cmpi32(int32_t a, int32_t b);
int cmpu32(uint32_t a, uint32_t b);

/* Shift left by n bits */
int32_t shli32(int32_t a, int n);
uint32_t shlu32(uint32_t a, int n);

/* Shift right by n bits */
int32_t shri32(int32_t a, int n);
uint32_t shru32(uint32_t a, int n);

/* Arithmetic shift right by n bits */
int32_t asri32(int32_t a, int n);

/* 32-bit division: result = a / b, optional remainder in *rem */
int32_t divi32(int32_t a, int32_t b, int32_t *rem);
uint32_t divu32(uint32_t a, uint32_t b, uint32_t *rem);

/* Negate a 32-bit number: result = -a */
int32_t negi32(int32_t n);

/* Absolute value of a 32-bit integer: result = |a| */
int32_t absi32(int32_t a);

/* Convert decimal string to 32-bit integer */
int32_t atoi32(const char *str);
uint32_t atou32(const char *str);

/* Convert string in base to 32-bit integer */
/* When base = 0:
 *  0x prefix is hex
 *  0 prefix is octal
 *  otherwise decimal */
int32_t strtoi32(const char *nptr, char **endptr, int base);
uint32_t strtou32(const char *nptr, char **endptr, int base);

/* Convert 32-bit integer to string */
/* Returns: pointer to beginning of string */
char *i32toa(int32_t n, char *str);
char *u32toa(uint32_t n, char *str);

#endif
