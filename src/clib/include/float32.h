#ifndef _FLOAT32_
#define _FLOAT32_

/* include stdlib if not included already */
#ifndef _STDLIB_
#include <stdlib.h>
#endif

/* include math32 for int32_t type */
#ifndef _MATH32_H_
#include <math32.h>
#endif

#ifndef _ELFCLIB_
#pragma .link .library float32.lib
#endif

#define FLT_RADIX      2
#define FLT_ROUNDS    -1
#define FLT_DIG        6
#define FLT_EPSILON    1.19E-7
#define FLT_MANT_DIG   24
#define FLT_MAX        3.40E+38
#define FLT_MAX_EXP    127
#define FLT_MAX_10_EXP 38
#define FLT_MIN        1.18E-38
#define FLT_MIN_EXP    -126
#define FLT_MIN_10_EXP -38
#define FLT_HAS_SUBNORM 0

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
/* mask for exponent bits */
#define FP_EXP     0x7F80

/* buffer size for float32 number string with null */
#define FP_BUF_SZ  15

/* Float values used with trig functions */
#define FP_ONE_HI    0x3F80
#define FP_ONE_LO    0x0000
#define FP_HALFPI_HI 0x3FC9
#define FP_HALFPI_LO 0x0FDA
#define FP_PI_HI     0x4049
#define FP_PI_LO     0x0FDB
#define FP_2PI_HI    0x40C9
#define FP_2PI_LO    0x0FDB
#define FP_4THPI_HI  0x3F49
#define FP_4THPI_LO  0x0FDB

/* Round to zero value (0.000001) for sin and tangent */
#define FP_RND_0_HI 0x3586
#define FP_RND_0_L0 0x37BD


/* Exponential Limit is ln(FLT_MAX) rounded to 86 */
#define FP_E_MAX_HI  0x42ac
#define FP_E_MAX_LO  0x0000

/* ArcTan domain limit is -38.871475 to +38.871475 */
#define FP_AT_MAX_HI  0x421B
#define FP_AT_MAX_LO  0x7c64

/* Conversion Factors */
/* Natural to common (base 10) logarithm */
#define FP_LN_10_HI   0x4013
#define FP_LN_10_LO   0x5D8E

/* Natural to base 2 logarithm */
#define FP_LN_2_HI    0x3F31
#define FP_LN_2_LO    0x7218

/* Degrees to Radians */
#define FP_DEG_RAD_HI 0x3C8E
#define FP_DEG_RAD_LO 0xFA35

/* Radians to Degrees */
#define FP_RAD_DEG_HI 0x4265
#define FP_RAD_DEG_LO 0x2EE1

/* Precision Constants */
#define FP_DOT5_HI    0x3f00
#define FP_DOT5_LO    0x0000

/* Float to string conversion */
#define FP_TWO_HI     0x4000
#define FP_TWO_LO     0x0000
#define FP_TEN_HI     0x4120
#define FP_TEN_LO     0x0000
#define FP_10P5_HI    0x47c3
#define FP_10P5_LO    0x5000
#define FP_10N5_HI    0x3727
#define FP_10N5_LO    0xc5ac
#define FP_RND45_HI   0x3851
#define FP_RND45_LO   0xb717

/* 32-bit signed number represented as two 16-bit values */
struct float32 {
    unsigned int low;   /* Lower 16 bits */
    unsigned int high;  /* Upper 16 bits */
};

typedef struct float32 float32_t;

/* arthimetic functions */
float32_t absf(float32_t a);
float32_t addf(float32_t a, float32_t b);
float32_t divf(float32_t a, float32_t b);
float32_t mulf(float32_t a, float32_t b);
float32_t subf(float32_t a, float32_t b);
float32_t negf(float32_t a);
float32_t invf(float32_t a);
float32_t fmodf(float32_t a, float32_t b);

/* comparison functions */
int gtf(float32_t a, float32_t b);
int gtef(float32_t a, float32_t b);
int ltf(float32_t a, float32_t b);
int ltef(float32_t a, float32_t b);
/* strictly equal */
int eqf(float32_t a, float32_t b);
/* not equal */
int nef(float32_t a, float32_t b);
/* approximately equal */
int samef(float32_t a, float32_t b);

/* Conversion functions */
void ftoa(float32_t fp1, char *s);
void ftosci(float32_t fp1, char *s);
int32_t ftoi32(float32_t a);
int ftoi(float32_t a);
float32_t atof(char *s);
float32_t itof(int i);
float32_t i32tof(int32_t i);
int fstrf (char* buf, float32_t val, int prec, char fmt);
float32_t makef(unsigned int hi, unsigned int lo);


/* Trig functions */
float32_t sinf(float32_t a);
float32_t cosf(float32_t a);
float32_t tanf(float32_t a);
float32_t asinf(float32_t a);
float32_t acosf(float32_t a);
float32_t atanf(float32_t a);
float32_t atan2f(float32_t y, float32_t x);

/* Reduce angle to range of (-pi, pi) */
float32_t areducef(float32_t a);

/* Angle conversion functions */
float32_t rad2degf(float32_t a);
float32_t deg2radf(float32_t a);

/* Rounding functions */
float32_t truncf(float32_t a);
float32_t modf(float32_t a, float32_t *ip);
float32_t fracf(float32_t a);
float32_t ceilf(float32_t a);
float32_t floorf(float32_t a);
float32_t roundf(float32_t a);
float32_t frexpf(float32_t a, int *exp);
float32_t ldexpf(float32_t a, int n);
float32_t zflushf(float32_t a, float32_t eps);

/* Logarithmic and Power Functins */
float32_t expf(float32_t a);
float32_t logf(float32_t a);
float32_t log2f(float32_t a);
float32_t log10f(float32_t a);
float32_t sqrtf(float32_t a);
float32_t powf(float32_t b, float32_t p);
float32_t hypotf(float32_t a, float32_t b);
float32_t sinhf(float32_t a);
float32_t coshf(float32_t a);
float32_t tanhf(float32_t a);
#endif
