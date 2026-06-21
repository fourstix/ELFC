#ifndef _FLOAT32_
#define _FLOAT32_

/* include stdlib if not included already */
#ifndef _STDLIB_
#include <stdlib.h>
#endif

#ifndef _ELFCLIB_
#pragma .link .library float32.lib
#endif

#define FLT_RADIX      2
#define FLT_ROUNDS    -1
#define FLT_DIG        7
#define FLT_EPSILON    1.19E-7
#define FLT_MANT_DIG   24
#define FLT_MAX        3.40E+38
#define FLT_MAX_EXP    127
#define FLT_MAX_10_EXP 38
#define FLT_MIN        1.18E-38
#define FLT_MIN_EXP    -126
#define FLT_MIN_10_EXP -38

#define isNaN(n)  (0xFFFF == n.high)
#define isInf(n)  (0xFF80 == (n.high | 0x8000))
#define isZero(n) (0 == (n.high & ~0x8000))
#define isNeg(n)  (n.high & 0x8000)

/* special high byte values */
#define FP_NAN     0xFFFF
#define FP_POSINF  0x7F80
#define FP_NEGINF  0xFF80
/* mask for sign bit */
#define FP_SIGN    0x8000
#define FP_EXP     0x7F80


/* Float values used with trig functions */
#define FP_ONE_HI    0x3F80
#define FP_ONE_LO    0x0000
#define FP_NEGONE_HI 0xBF80
#define FP_NEGONE_LO 0x0000
#define FP_HALFPI_HI 0x3FC9
#define FP_HALFPI_LO 0x0FDB
#define FP_PI_HI     0x4049
#define FP_PI_LO     0x0FDB




/* Conversion Factors */
#define FP_DOT5_HI   0x3f00
#define FP_DOT5_LO   0x0000

#define FP_180_HI    0x4334
#define FP_180_LO    0x0000


/* 32-bit signed number represented as two 16-bit values */
struct float32 {
    unsigned int low;   /* Lower 16 bits */
    unsigned int high;  /* Upper 16 bits */
};

typedef struct float32 float32_t;

/* define types for ftoi32 function */
#ifndef int32
struct int32 {
    unsigned int low;   /* Lower 16 bits */
    unsigned int high;  /* Upper 16 bits */
};
#endif

#ifndef int32_t
typedef struct int32 int32_t;
#endif

/* arthimetic functions */
float32_t absf(float32_t a);
float32_t addf(float32_t a, float32_t b);
float32_t divf(float32_t a, float32_t b);
float32_t mulf(float32_t a, float32_t b);
float32_t subf(float32_t a, float32_t b);
float32_t negf(float32_t a);

/* comparison functions */
int eqf(float32_t a, float32_t b);
int gtf(float32_t a, float32_t b);
int gtef(float32_t a, float32_t b);
int ltf(float32_t a, float32_t b);
int ltef(float32_t a, float32_t b);
int nef(float32_t a, float32_t b);

/* Conversion functions */
void ftoa(float32_t fp1, char *s);
int32_t ftoi32(float32_t a);
float32_t atof(char *s);


/* Trig functions */
float32_t sinf(float32_t a);
float32_t cosf(float32_t a);
float32_t tanf(float32_t a);
float32_t asinf(float32_t a);
float32_t acosf(float32_t a);
float32_t atanf(float32_t a);
/* Reduce angle to range of (-pi, pi) */
float32_t _reduce(float32_t a);

/* Math functions */
float32_t sqrtf(float32_t a);
float32_t truncf(float32_t a);
float32_t modf(float32_t a, float32_t *ip);
float32_t fracf(float32_t a);
float32_t ceilf(float32_t a);
float32_t floorf(float32_t a);
float32_t roundf(float32_t a);
float32_t frexpf(float32_t a, int *exp);
#endif
