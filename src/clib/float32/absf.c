#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

#pragma             extrn _absfp
#pragma             extrn Cerrno

/*
 * Return: abs(x)
 *         NaN for NaN
 *         +inf for -inf or +inf
 */
 float32_t absf(float32_t a) {
   int r_high = 0;
   int r_low = 0;
   static float32_t result = {0, 0};

   if (isNaN(a)) {
     errno = EDOM;
     return a;
   }
   /* clear sign bit, if set */
   /* assign local variables to static result for return */
   result.high = a.high & ~FP_SIGN;
   result.low = a.low;

   /* set error if overflow occurred */
   if (isInf(result))
     errno = ERANGE;

   return result;
}
