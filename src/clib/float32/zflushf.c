#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

#pragma             extrn Cerrno
#pragma             extrn Cabsf
#pragma             extrn Cltef

/*
 * Flush small values to zero
 *
 * Return zero, if |a| <= epsilon
 *   else return a
 */
float32_t zflushf(float32_t a, float32_t eps) {
   float32_t val;
   static float32_t result = {0, 0};

   /* return a for NaN or +/-Inf */
   if (isNaN(a)) {
     errno = EDOM;
     result = a;
     return result;
   } else if (isInf(a)) {
     errno = ERANGE;
     result = a;
     return result;
   } else if (isZero(a)) {
     /* if already zero, don't do anything */
     result = a;
     return result;
   }

   /* get the absolute value */
   val = absf(a);

   /* if |a| <= epsilon, then set to zero */
   if (ltef(val, eps)) {
     result.high = 0;
     result.low  = 0;
   } else {
     result = a;
   }

   return result;
 }
