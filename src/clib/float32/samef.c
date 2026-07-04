#define _ELFCLIB_
#include <float32.h>
#include <errno.h>
#include <stdbool.h>

extern float32_t _fp_epsilon;

#pragma             extrn Cerrno
#pragma             extrn Csubf
#pragma             extrn Cabsf
#pragma             extrn Cmulf
#pragma             extrn Cltf
#pragma             extrn Cltef

/* constant value used in routine */
#pragma .link .requires C_fp_const
#pragma             extrn C_fp_epsilon

/*
 * Check to see if two numbers are apporixmately
 * equal using Knuth's algorithm:
 * |a - b| <= ((|a| < |(b|) ? |b| : |a| * epsilon)
 * from The Art of Computer Programming, Vol. 1, page 218.
 *
 * Returns true if numbers are approximately the same,
 * using a value of epsilon of 0.000001.
 */
int samef(float32_t a, float32_t b) {
  float32_t diff, limit;
  /* handle special cases first */
  if (isNaN(a) || isNaN(b) ) {
    /* NaN != NaN per IEEE 754 */
    errno = EDOM;
    return false;
  } else if (isInf(a) || isInf(b)) {
     /* +inf == +inf and -inf == -inf per IEEE 754 */
     return (a.high == b.high);
  } else if (isZero(a) && isZero(b)) {
    /* IEEE 754 specifies equals comparison done without sign bit */
    return true;
  }
  diff = subf(a, b);
  diff = absf(diff);
  a = absf(a);
  b = absf(b);

  if (ltf(a, b)) {
    limit = b;
  } else {
    limit = mulf(a, _fp_epsilon);
  }
  return ltef(diff, limit);
}
