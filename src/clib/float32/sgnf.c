#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

#pragma             extrn Cerrno

/*
 * Return: signum(x)
 *         1 for x > 0 or +Inf
 *        -1 for x < 0 or -Inf
 *         0 for zero
 *        NaN for NaN
 */
 float32_t sgnf(float32_t a) {
   static float32_t result = {0, 0};

   /* NaN's always propagate as NaN */
   if (isNaN(a)) {
     result.high = FP_NAN;
     result.low  = FP_NAN;
     errno = EDOM;
     return result;
   }

   /* low word is zero for all results */
   result.low = 0;
   if (isZero(a)) {
     /* set result to 0 */
     result.high = 0;
   } else if (isNeg(a)) {
     /* set result to -1 */
     result.high = 0xBF80;
   } else {
     /* set result to 1 */
     result.high = 0x3F80;
   }
   return result;
}
