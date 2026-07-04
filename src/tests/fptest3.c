#include <stdio.h>
#include <float32.h>
/*
 * Test for subtraction, division and multiplication
 *
 * Some of these floating point tests are based on
 * W.M Kahan's Floating Point Test program "Paranoia"
 * Copyright (c) 1983
 */

/*
 * floating point constants.
 */
float32_t Zero = {0, 0};
float32_t Half = {0x0000, 0x3f00};
float32_t One = {FP_ONE_LO, FP_ONE_HI};
float32_t Two = {0x00000, 0x4000};
float32_t Three = {0x0000, 0x4040};
//float32_t Four = {0x0000, 0x4080};
//float32_t Five = {0x0000, 0x40a0};
//float32_t Eight = {0x0000, 0x4100};
float32_t Nine =  {0x0000, 0x4110};
float32_t TwentySeven = {0x0000, 0x41d8};
//float32_t ThirtyTwo = {0x0000, 0x4200};
//float32_t TwoForty = {0x0000, 0x4370};
//float32_t MinusOne = {FP_ONE_LO, FP_ONE_HI | FP_SIGN};
//float32_t OneAndHalf = {0x0000, 0x3fc0};


float32_t fp_NaN = {FP_NAN, FP_NAN};
float32_t fp_inf = {0x0000, FP_POSINF};
float32_t fp_neginf = {0x0000, FP_NEGINF};

/* Values calculated previously */
float32_t Radix = {0x0000, 0x4000};
float32_t U1 = {0x0000, 0x3380};
float32_t U2 = {0x0000, 0x3400};
float32_t F9 = {0xffff, 0x3f7f};

float32_t T;
float32_t W, X, Y, Z;

int ErrCnt = 0;

/* character buffer for printing */
char buf[20];


/*
 *  TstCond checks whether an error has occurred.
 */
void TstCond(int Valid, char * T) {
  if (! Valid) {
    printf("Error:  %s\n",T);
    ErrCnt++;
  }
  return;
}

/*
 * Generate a random floating point number
 * Does not generate +Inf, -Inf or NaN
 */
float32_t RandFloat(void) {
  static float32_t fn;
  int a, b;
  do {
    a = rand();
    /* redo if exponent if FF (Inf or NaN) */
  } while ((a & FP_POSINF) == FP_POSINF);
  /* if a is zero, then b must be zero */
  if (a == 0) {
    b = 0;
  } else {
    b = rand();
  }
  fn.high = a;
  fn.low = b;
  return fn;
}

int main() {
  float32_t tmp;
  float32_t tmp2;
  int idx;

  printf("Testing subtraction\n");
  /* Validate normalization for subtraction */
  tmp = mulf(Radix, Radix);
  X = divf(W, tmp);
  Y = addf(X, One);
  Z = subf(Y, X);
  T = addf(Z, U2);
  X = subf(T, Z);
  TstCond (eqf(X, U2), "Subtraction is not normalized X=Y,X+Z != Y+Z!");

  /* Test subtraction underflow */
  tmp = subf(F9, One);
  TstCond(ltf(tmp, Zero), "subtraction yields (1-U1) - 1 >= 0)");

  /* Test subtraction (X - Y) + (Y - X) = 0 */
  tmp = addf(One, Half);
  tmp = mulf(tmp, Half);
  X = addf(One, tmp);
  tmp = addf(One, U2);
  Y = mulf(tmp, Half);
  Z = subf(X, Y);
  T = subf(Y, X);
  W = addf(Z, T);

  TstCond(eqf(W, Zero), "(X - Y) + (Y - X) is non zero!");

  printf("Testing for division errors\n");
  /* Validate division guard digit */
  X = divf(One, Three);
  Z = divf(Three, Nine);
  X = subf(X, Z);
  T = divf(Nine, TwentySeven);
  Z = subf(Z, T);
  TstCond(eqf(X, Zero) && eqf(Z, Zero),
    "Division error: 1/3  and  3/9  and  9/27 disagree");

  Y = divf(F9, One);
  X = subf(F9, Half);
  tmp = subf(Y, Half);
  Y = subf(tmp, X);
  X = addf(One, U2);
  T = divf(X, One);
  X = subf(T, X);
  TstCond (eqf(X, Zero) && eqf(Y, Zero) && eqf(Z, Zero),
        "Division error: X/1 != X");

  tmp = addf(One, U2);
  X = divf(One, tmp);
  tmp = subf(X, Half);
  Y = subf(tmp, Half);
  TstCond (ltf(Y, Zero), "Computed value of 1/1.000001 >= 1");

  //BInvrse = One / Radix;
  //TstCond (Failure, (BInvrse * Radix - Half == Half), "Radix * ( 1 / Radix ) differs from 1");
  tmp = divf(One, Radix);
  tmp = mulf(tmp, Radix);
  tmp = subf(tmp, Half);
  TstCond(eqf(tmp, Half), "Radix * (1 / Radix) differs from 1");


  printf("Testing +Inf, -Inf and NaN\n");
  X = subf(Two, fp_inf);
  Y = addf(Three, fp_inf);
  Z = subf(fp_inf, fp_inf);
  TstCond((isInf(X) && isNeg(X)), "2 - +Inf != -Inf");
  TstCond((isInf(Y) && !isNeg(Y)), "3 + +Inf != +Inf");
  TstCond(isNaN(Z), "+Inf - +Inf != NaN");
  Z = divf(Two, fp_inf);
  TstCond(isZero(Z), "2 / +Inf != 0");

  printf("Testing multiplication commutes (X*Y = Y*X)\n");
  for (idx = 0; idx < 10; idx++) {
    X = RandFloat();
    Y = RandFloat();
    T = mulf(X, Y);
    Z = mulf(Y, X);
    if (nef(T, Z)) {
      TstCond(0, "X * Y  != Y * X");
      ftoa(X, buf);
      printf("Error: Multiplication did not commute for X = %s ", buf);
      ftoa(Y, buf);
      printf("times Y = %s\n", buf);
      printf("X => 0x%04x:0x%04x\n", X.high, X.low);
      printf("Y => 0x%04x:0x%04x\n", Y.high, Y.low);
      /* end test with failure */
      break;
    }
  }

  if (!ErrCnt) {
    printf("All Tests Passed.");
  }
}
