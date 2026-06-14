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

#define FP_NAN     0xFFFF
#define FP_POSINF  0x7F80
#define FP_NEGINF  0xFF80
#define FP_SIGN    0x8000


/* 32-bit signed number represented as two 16-bit values */
struct float32 {
    unsigned int low;   /* Lower 16 bits */
    unsigned int high;  /* Upper 16 bits */
};

typedef struct float32 float32_t;


float32_t absf(float32_t a);
float32_t addf(float32_t a, float32_t b);
float32_t atof(char *s);
float32_t divf(float32_t a, float32_t b);
int eqf(float32_t a, float32_t b);
int gtf(float32_t a, float32_t b);
int gtef(float32_t a, float32_t b);
int ltf(float32_t a, float32_t b);
int ltef(float32_t a, float32_t b);
float32_t mulf(float32_t a, float32_t b);
int nef(float32_t a, float32_t b);
float32_t subf(float32_t a, float32_t b);
void ftoa(float32_t fp1, char *s);




#endif
