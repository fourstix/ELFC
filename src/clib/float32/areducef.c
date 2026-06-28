#define _ELFCLIB_
#include <float32.h>

extern float32_t _fp_2pi;
extern float32_t _fp_pi;
extern float32_t _fp_negpi;


#pragma             extrn Cgtf
#pragma             extrn Cltf
#pragma             extrn Cfmodf
#pragma             extrn Caddf
#pragma             extrn Csubf

/* constant values used in routine */
#pragma .link .requires C_fp_const
#pragma             extrn C_fp_pi
#pragma             extrn C_fp_negpi
#pragma             extrn C_fp_2pi

/*
 * Reduce an angle to the principle range of
 * trig functions, (-pi, pi)
 */
float32_t areducef(float32_t angle) {
  /* remove rotations */
  angle = fmodf(angle, _fp_2pi);

  /* Adjust so that angle is always between -pi and +pi */
  if (isNeg(angle)) {
    if (ltf(angle, _fp_negpi)) {
      /* convert negative 1st and 2nd quadrant values into positive values*/
      angle = addf(angle, _fp_2pi);
    }
  } else if (gtf(angle, _fp_pi)) {
      /* convert positive 3rd and 4th quardrant values into negative values*/
      angle = subf(angle, _fp_2pi);
  }
  return angle;
}
