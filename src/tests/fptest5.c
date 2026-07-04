#include <stdio.h>
#include <float32.h>
/*
 * Test for trig functions
 *
 */

/*
 * floating point constants.
 */
float32_t Zero  = {0, 0};
float32_t Half  = {0x0000, 0x3f00};
float32_t One   = {FP_ONE_LO, FP_ONE_HI};
float32_t Two   = {0x00000, 0x4000};
float32_t Three = {0x0000, 0x4040};
float32_t Four  = {0x0000, 0x4080};
float32_t Five  = {0x0000, 0x40a0};
float32_t Six   = {0x0000, 0x40c0};
float32_t Pi       = {0x0fdb, 0x4049};
float32_t NegOne = {FP_ONE_LO, FP_ONE_HI | FP_SIGN};

float32_t X, Y, Z;

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

int main() {
  printf("Testing: trig functions()\n");
  Y = sqrtf(Two);
  Y = invf(Y);

  X = divf(Pi, Four);
  Z = sinf(X);
  TstCond(samef(Z, Y), "sin(pi/4) != 1/sqrt(2)");

  Z = cosf(X);
  TstCond(samef(Z, Y), "cos(pi/4) != 1/sqrt(2)");

  Z = tanf(X);
  TstCond(samef(Z, One), "tan(pi/4) != 1");

  X = divf(Pi, Three);
  Z = cosf(X);
  TstCond(samef(Z, Half), "cos(pi/3) != 1/2");

  Y = asinf(Half);
  TstCond(samef(Y, X), "acos(1/2) != pi/3");

  X = divf(Pi, Six);
  Z = sinf(X);
  TstCond(samef(Z, Half), "sin(pi/6) != 1/2");

  Y = asinf(Half);
  TstCond(samef(Y, X), "asin(1/2) != pi/6");

  X = divf(Pi, Four);
  Y = atanf(One);
  TstCond(samef(Y, X), "atan(1) != pi/4");

  X = NegOne;
  Y = One;
  /* this will result in 2nd quadrant value  pi - pi/4 or 3pi/4 */
  Z = atan2f(Y, X);
  //ftoa(Z, buf);
  //printf("Z = %s, ", buf);
  X = divf(Pi, Four);
  Y = subf(Pi, X);
  //ftoa(Y, buf);
  //printf("Y = %s\n", buf);
  TstCond(samef(Z, Y), "atan2(1,-1) != 3pi/4");

  X = Three;
  Y = Four;
  Z = hypotf(X, Y);
  TstCond(samef(Z, Five), "hypotf(3, 4) != 5");

  if (!ErrCnt) {
    printf("All Tests Passed.");
  }
}
