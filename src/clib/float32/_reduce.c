#define _ELFCLIB_
#include <float32.h>

#pragma             extrn Cgtf
#pragma             extrn Cgtef
#pragma             extrn Csubf

static float32_t fp_pi  = {0x0fdb, 0x4049};
static float32_t fp_2pi = {0x0fdb, 0x40c9};

/*
 * Reduce an angle to the principle range of
 * trig functions, (-pi, pi)
 */
float32_t _reduce(float32_t angle) {
  /* remove rotations */
  /* angle = modf(angle, fp_2pi); */
  /* FAKE IT for now, replace this with modf when availale */
  if (gtef(angle, fp_2pi)) {
    angle = subf(angle, fp_2pi);
  }
  /* convert 3rd and 4th quardrant values to negative values*/
  if (gtf(angle, fp_pi)) {
      angle = subf(angle, fp_2pi);
  }
  return angle;
}
