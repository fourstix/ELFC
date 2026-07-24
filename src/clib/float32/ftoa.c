#define _ELFCLIB_
#include <float32.h>

extern  float32_t _fp_round;

#pragma             extrn Cftosci
#pragma             extrn Cnegf
#pragma             extrn Caddf
#pragma             extrn Cshri32
#pragma             extrn Cshli32
#pragma             extrn Ci32_from_int
#pragma             extrn Ci32toa
#pragma             extrn Cmuli32



/* constant value used in routine */
#pragma .link .requires C_fp_const
#pragma             extrn C_fp_round

void ftoa(float32_t f, char *p) {
  //static float32_t round = {0xb717, 0x3851};
  static int32_t digit = {10, 0};
  int32_t mantissa;
  int32_t int_part = {0,0};
  int32_t frac_part = {0,0};
  int exp;
  int m;
  int bcd;

  /* if null buffer just return */
  if (!p)
    return;

  /* handle special cases first */
  if (isNaN(f)) {
    p[0] = 'N';
    p[1] = 'a';
    p[2] = 'N';
    p[3] = 0;
    return;
  } else if (isZero(f))  {
    p[0] = '0';
    p[1] = '.';
    p[2] = '0';
    p[3] = 0;
    return ;
  } else if (isInf(f)) {
    /* set sign of infinity */
    if (isNeg(f)) {
      p[0] = '-';
    } else {
      p[0] = '+';
    }
    p[1] = 'I';
    p[2] = 'n';
    p[3] = 'f';
    p[4] = 0;
    return;
  }
  /* get exponent from floating point numbr */
  exp = (f.high & FP_EXP) >> 7;

  /*
   * Check biased exponent for values greater than one millon
   * or less than 0.00001 and use scientific notation
   * instead for these values.
   */
  if ((exp < 110) || (exp >= 147)) {
      ftosci(f, p);
      return;
  }
/*
 * this case won't happen because of above logic
 * else if (exp >= 23)
 *    int_part = mantissa << (exp - 23);
 */


  if (isNeg(f)) {
    f = negf(f);
    *p++ = '-';
  }
  /* round to 4 decimal places */
  f = addf(f, _fp_round);

  /* get exponent from floating point numbr */
  exp = (f.high & FP_EXP) >> 7;
  /* remove bias from exponent */
  exp -= 127;

  mantissa.low = f.low;
  /* set implied 1 bit in mantissa */
  mantissa.high = (f.high & 0x007f) | 0x0080;

  if (exp >= 0) {
    int_part = shri32(mantissa, (23 - exp));
    frac_part = shli32(mantissa, (exp + 1));

    /* clip fraction to 24 bits */
    frac_part.high &= 0x00FF;
  } else {
    /* if (exp < 0) */
    int_part  = i32_from_int(0);
    frac_part = shri32(mantissa, -(exp + 1));
    /* clip fraction to 24 bits */
    frac_part.high &= 0x00FF;
  }

  if (int_part.high == 0 && int_part.low == 0) {
    *p++ = '0';
  } else {
    i32toa(int_part, p);
    /* skip over number and place decimal point */
    while (*p) {
      p++;
    }
  }
  *p++ = '.';

  if (frac_part.high == 0 && frac_part.low == 0) {
    *p++ = '0';
  } else {
    /* precision is four */
    for (m = 0; m < 4; m++) {
      /* print BCD */
      frac_part = muli32(frac_part, digit);
      bcd = (frac_part.high & 0xFF00) >> 8;
      *p++ = bcd + '0';
      frac_part.high &= 0x00FF;
    }
    /* delete ending zeroes */
    for (--p; p[0] == '0' && p[-1] != '.'; --p)
        ;
    ++p;
  }
  *p = 0;
}
