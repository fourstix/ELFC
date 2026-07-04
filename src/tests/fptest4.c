#include <stdio.h>
#include <float32.h>
/*
 * Test for sqrt, powers and logarithms
 *
 */

/*
 * floating point constants.
 */
float32_t Zero = {0, 0};
float32_t Half = {0x0000, 0x3f00};
float32_t One = {FP_ONE_LO, FP_ONE_HI};
float32_t Two = {0x00000, 0x4000};
float32_t Three = {0x0000, 0x4040};
float32_t Four = {0x0000, 0x4080};
float32_t Five = {0x0000, 0x40a0};
float32_t SixTwoFive = {0x4000, 0x441c};
//float32_t Eight = {0x0000, 0x4100};
//float32_t Nine =  {0x0000, 0x4110};
float32_t TwentySeven = {0x0000, 0x41d8};
float32_t ThirtyTwo = {0x0000, 0x4200};
float32_t SixtyFour = {0x0000, 0x4280};
float32_t FiveEighth = {0x000, 0x3f20};
float32_t NegHalf = {0x0000, 0xBf00};
float32_t NegOne = {FP_ONE_LO, FP_ONE_HI | FP_SIGN};

float32_t LnFive = {0x0210, 0x3fce};

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
  float32_t tmp;
  int idx;

  printf("Testing: square root(x)\n");
  /* Test 10 integers */
  /* 0, 1, 3, 7, 15, 31, 63, 127, 255, 511 */
  X = Zero;
  for (idx = 0; idx < 10; idx++) {
    tmp = mulf(X, X);
    Y = sqrtf(tmp);

    TstCond(samef(X, Y), "sqrt(X*X) != X");
    /* X = X*2 + 1 */
    X = mulf(X, Two);
    X = addf(X, One);
  }

  printf("Testing: frexpf()\n");
  tmp = atof("2560");
  X = frexpf(tmp, &idx);
  TstCond(samef(X, FiveEighth), "X = frexpf(2560, &idx), X is not 0.625");
  TstCond((idx == 12), "frexpf(2560, &idx) idx is not 12" );

  tmp = atof("-4");
  X = frexpf(tmp, &idx);
  TstCond(samef(X, NegHalf), "X = frexpf(-4, &idx), X is not -0.5");
  TstCond((idx == 3), "frexpf(-4, &idx) idx is not 3");

  printf("Testing: ldexpf()\n");
  Y = ldexpf(Half, 3);
  TstCond(samef(Y, Four), "Y = ldexpf(0.5, 3), Y is not 4.0 (0.5 * 2^3)");

  Y = ldexpf(NegOne, -4);
  Z = atof("-0.0625");
  TstCond(samef(Y, Z), "Y = ldexpf(-1, -4), Y is not -0.0625 (-1.0 * 2^-4)");

  printf("Testing logf(5)\n");
  X = logf(Five);
  TstCond(samef(X, LnFive), "logf(5) != 1.6094379");

  printf("Testing: expf()\n");
  X = LnFive;
  Y = expf(X);
  TstCond(samef(Y, Five), "expf(1.6094379) != 5");


  printf("Testing log2f()\n");
  X = log2f(ThirtyTwo);
  TstCond(samef(X, Five), "log2f(32) != 5");

  printf("Testing log10f()\n");
  X = atof("100");
  Y = log10f(X);
  TstCond(samef(Y, Two), "log10f(100) != 2");

  printf("Testing powf()\n");
  X = Four;
  Y = Half;
  Z = powf(X, Y);
  TstCond(samef(Z, Two), "powf(4, 0.5) != 2");

  X = Three;
  Y = Three;
  Z = powf(X, Y);
  TstCond(samef(Z, TwentySeven), "powf(3, 3) != 27");

  X = Four;
  Y = Three;
  Z = powf(X, Y);
  TstCond(samef(Z, SixtyFour), "powf(4, 3) != 64");

  X = Five;
  Y = Four;
  Z = powf(X, Y);
  TstCond(samef(Z, SixTwoFive), "powf(5, 4) != 625");

  if (!ErrCnt) {
    printf("All Tests Passed.");
  }
}
