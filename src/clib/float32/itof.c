#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

#pragma             extrn Ci32tof
#pragma             extrn Cerrno

/*
 * Return: i as a 32-bit float value
 */
float32_t itof(int i) {
  int32_t a;
  static float32_t result = {0, 0};

  /* sign-extend 16-bit value into 32-bit value */
  if (i < 0) {
    a.high = 0xFFFF;
  } else {
    a.high = 0;
  }
  a.low = i;

  result = i32tof(a);

  return result;
}
