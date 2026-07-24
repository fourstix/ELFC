#define _ELFCLIB_
#include <float32.h>

/*
 * Return 32-bit float value created
 * from two unsigned int values.
 */
float32_t makef(unsigned int hi, unsigned int lo) {
  static float32_t result;

  result.high = hi;
  result.low = lo;

  return result;
}
