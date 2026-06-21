#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

#pragma             extrn _absfp
#pragma             extrn Cerrno

/*
 * Return: negate a, -a
 *         NaN for NaN
 *         +Inf for -Inf,  -Inf for +Inf
 *         0 for +0 or -0
 */
 float32_t negf(float32_t a) {
   int r_high = 0;
   int r_low = 0;
   static float32_t result = {0, 0};

   if (isNaN(a)) {
     errno = EDOM;
     return a;
   } else if (isZero(a)) {
     /* zero is negative of itself (ignore -0) */
     result.high = 0;
     result.low = 0;
     return result;
   }

   /* toggle sign bit */
   /* assign local variables to static result for return */
   result.high = a.high ^ FP_SIGN;
   result.low = a.low;

   /* set error if overflow occurred */
   if (isInf(result))
     errno = ERANGE;

   return result;
}
