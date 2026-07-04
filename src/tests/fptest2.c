#include <stdio.h>
#include <float32.h>
/*
* Validate the radix, precision and epsilon meets the
* ANSI C89/C90 values.
*
* These floating point calculations are based on
* W.M Kahan's Floating Point Test program "Paranoia"
* Copyright (c) 1983
*/

float32_t Radix;
float32_t Precision;

float32_t Third;
float32_t E0, E1;
float32_t F6, F9;
float32_t U1, U2;
float32_t W;
float32_t X;
float32_t Y;
float32_t Z;

int ErrCnt = 0;
/*
 Small floating point constants.
*/
float32_t Zero = {0, 0};
float32_t Half = {0x0000, 0x3f00};
float32_t One = {FP_ONE_LO, FP_ONE_HI};
float32_t Two = {0x00000, 0x4000};
float32_t Three = {0x0000, 0x4040};
float32_t Four = {0x0000, 0x4080};
float32_t Five = {0x0000, 0x40a0};
float32_t Eight = {0x0000, 0x4100};
float32_t Nine =  {0x0000, 0x4110};
//float32_t TwentySeven;
float32_t ThirtyTwo = {0x0000, 0x4200};
float32_t TwoForty = {0x0000, 0x4370};
float32_t MinusOne = {FP_ONE_LO, FP_ONE_HI | FP_SIGN};
float32_t OneAndHalf = {0x0000, 0x3fc0};
float32_t Dot01 = {0xd70a, 0x3c23};
float32_t TwentyFour = {0x0000, 0x41c0};

/* Expectd Values */
//float32_t Radix = {0x0000, 0x4000};
//float32_t U1 = {0x0000, 0x3380};
//float32_t U2 = {0x0000, 0x3400};
//float32_t F9 = {0xffff, 0x3f7f};

/* ANSI C specification is FLT_EPS < 1E-5 */
float32_t C_Epsilon = {0xc5ac, 0x3727};

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
  float32_t tmp2;
  int bits;
  int err = 0;

  /* Clear error counts */
  ErrCnt = 0;

  printf ("Searching for Radix and Precision.\n" );
  W = One;

  do {
    W = addf(W, W);
    Y = addf(W, One);
    Z = subf(Y, W);
    Y = subf(Z, One);
    tmp = absf(Y);
    tmp = addf(MinusOne, tmp);
  } while (ltf(tmp, Zero));

  /*
  Now W is just big enough that |((W+1)-W)-1| >= 1.
  */
  Precision = Zero;
  Y = One;
  do {
   Radix = addf(W, Y);
   Y = addf(Y, Y);
   Radix = subf(Radix, W);
 } while (eqf(Radix, Zero));

  if ( ltf(Radix, Two))   {
   Radix = One;
  }
  ftoa(Radix, buf);
  printf ("Radix = %s\n", buf);

  TstCond(eqf(Radix, Two), "Radix != 2");

  if (nef(Radix, One)) {
   W = One;
   do {
     Precision = addf(Precision, One);
     W = mulf(W, Radix);
     Y = addf(W, One);
     tmp = subf(Y, W);
   } while (eqf(tmp, One));
  }
  /*
  Now W == Radix^Precision is barely too big to satisfy (W+1)-W == 1
  */
  U1 = divf(One, W);
  U2 = mulf(Radix, U1);
  ftoa(U1, buf);
  printf ("Closest relative separation found is U1 = %s\n", buf);
  printf ("\n" );
  ftoa(U2, buf);
  printf ("FLT_EPSION found is U2 = %s\n", buf);
  printf ("Recalculating radix and precision\n" );
  /*
  save old values and recalculate
  */
  E0 = Radix;
  E1 = U1;
  //E9 = U2;
  //E3 = Precision;

  X = divf(Four, Three);
  Third = subf(X, One);
  F6 = subf(Half, Third);
  X = addf(F6, F6);
  tmp = subf(X, Third);
  X = absf(tmp);

  if (ltf(X, U2))
    X = U2;
  /*
  now X = (unknown no.) ulps of 1+
  */
  do  {
   U2 = X;
   /* Y = Half * U2 + ThirtyTwo * U2 * U2; */
   tmp = mulf(Half, U2);
   tmp2 = mulf(ThirtyTwo, U2);
   tmp2 = mulf(tmp2, U2);
   Y = addf(tmp, tmp2);
   Y = addf(One, Y);
   X = subf(Y, One);
   /* while ( ! ((U2 <= X) || (X <= Zero))) */
 } while (!(ltef(U2, X) || ltef(X, Zero)));

  /*
  now U2 == 1 ulp of 1 +
  */
  X = divf(Two, Three);
  F6 = subf(X, Half);
  Third = addf(F6, F6);
  X = subf(Third, Half);
  tmp = addf(X, F6);
  X = absf(tmp);

  if (ltf(X, U1) ) {
   X = U1;
  }
  /*
  now  X == (unknown no.) ulps of 1 -
  */
  do {
   U1 = X;
   /* Y = Half * U1 + ThirtyTwo * U1 * U1; */
   tmp = mulf(Half, U1);
   tmp2 = mulf(ThirtyTwo, U1);
   tmp2 = mulf(tmp2, U1);
   Y = addf(tmp, tmp2);
   Y = subf(Half, Y);
   X = addf(Half, Y);
   Y = subf(Half, X);
   X = addf(Half, Y);
   /* while ( ! ((U1 <= X) || (X <= Zero))) */
 } while ( !(ltef(U1, X) || ltef(X, Zero)) );
  /*
  now U1 == 1 ulp of 1 -
  */
  if (eqf(U1, E1)) {
    ftoa(U1, buf);
    printf ( "confirmed closest relative separation U1 = %s.\n", buf);
  } else {
    ftoa(U1, buf);
    printf ( "different closest relative separation U1 = %s.\n", buf );
  }

  W = divf(One, U1);
  tmp = subf(Half, U1);
  F9 = addf(tmp, Half);
  tmp = divf(U2, U1);
  tmp = addf(Dot01, tmp);
  //Radix = floorf(0.01 + U2 / U1);
  Radix = floorf(tmp);

  TstCond(eqf(Radix, E0), "Radix not confirmed.");

  TstCond(eqf(Radix, Two), "Radix is not 2");

  tmp = subf(F9, Half);

  TstCond (ltf(tmp, Half), "(1-U1)-1/2 < 1/2 is FALSE");
  X = F9;
  Y = subf(X, Half);
  Z = subf(Y, Half);
  TstCond ((nef(X, One) || eqf(Z, Zero)), "X=1 but X-1/2-1/2 != 0");
  X = addf(One, U2);

  /* Radix is Two for Float32 */
  tmp = negf(TwoForty);
  tmp2 = logf(U1);
  tmp = mulf(tmp, tmp2);
  tmp2 = logf(Radix);
  X = divf(tmp, tmp2);
  tmp = addf(Half, X);
  Y = floorf(tmp);
  /* if (absf(X - Y) * Four < One) X = Y; */
  tmp = subf(X, Y);
  tmp = mulf(tmp, Four);

  if (ltf(tmp, One)) X = Y;

  Precision = divf(X, TwoForty);
  tmp = addf(Half, Precision);
  Y = floorf(tmp);
  /* if (absf(Precision - Y) * TwoForty < Half) Precision = Y; */
  tmp = subf(Precision, Y);
  tmp = absf(tmp);
  tmp = mulf(tmp, TwoForty);
  if (ltf(tmp, Half))
    Precision = Y;

  tmp = floorf(Precision);

  TstCond (eqf(Precision, tmp),
      "Precision is not an integer value");
  bits = ftoi(Precision);
  printf("The number of significant digits of the Radix is %d\n", bits);

  TstCond (eqf(Precision, TwentyFour),
      "Number of significant digits of the Radix is not 24");

  tmp = mulf(U2, Nine);
  tmp = mulf(tmp, Nine);
  tmp = mulf(tmp, Nine);
  tmp = mulf(tmp, TwoForty);
  TstCond(ltf(tmp, One), "Precision worse than 6 decimal figures");

  if (ltf(tmp, One)) {
    printf("FLT_DIG value meets ANSI C89/C90 spec\n");
  }

  /* validate calculated values */
  TstCond((Radix.low == 0x0000 || Radix.high == 0x4000), "Error in Radix value");
  TstCond((U1.low == 0x0000 || U1.high == 0x3380), "Error in U1 (relative separation) value");
  TstCond((U2.low == 0x0000 || U2.high == 0x3400), "Error in U2 (epsilon) value");
  TstCond((F9.low == 0xFFFF || F9.high == 0x3f7f), "Error in F9 (1 - U1) value");

  TstCond(ltf(U2, C_Epsilon), "FLT_EPSION (U2) does not meet ANSI C89/C90 spec");

  if (ltf(U2, C_Epsilon)) {
    printf("FLT_EPSILON value meets ANSI C89/C90 spec.\n");
  }


  if (!ErrCnt) {
    printf("All Tests Passed.");
  }
}
