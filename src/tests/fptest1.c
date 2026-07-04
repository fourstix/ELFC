#include <stdio.h>
#include <float32.h>
/*
 * Some of these floating point tests are based on
 * W.M Kahan's Floating Point Test program "Paranoia"
 * Copyright (c) 1983
 */
/* count of different types of errors */
int ErrCnt = 0;

/*
 Small floating point constants.
*/
/* Zero and One are set directly */
float32_t Zero = {0, 0};
float32_t One = {FP_ONE_LO, FP_ONE_HI};
/* All others are set when tested */
float32_t Half;
float32_t Two;
float32_t Three;
float32_t Four;
float32_t Five;
float32_t Eight;
float32_t Nine;
float32_t TwentySeven;
float32_t ThirtyTwo;
float32_t TwoForty;
float32_t MinusOne;
float32_t OneAndHalf;
/* Negative zero is not used by Float32, but it should be handled correctly */
float32_t NegZero = {0, FP_SIGN};

/* Test variables */
float32_t Z;

/*
 * Since all test generates failures,
 * removed BadCond and simplified error logic
 */

/*
 * TstCond checks whether an error has occurred.
 */
void TstCond(int Valid, char *msg) {
  if (!Valid) {
     printf("Failure:  %s", msg);
     printf ( ".\n" );
     ErrCnt++;
   }
   return;
}


int main() {
  int   result;
  float32_t tmp, tmp2;
  printf ( "Program is now RUNNING tests on small integers:\n" );
  /* set variables to test values */
  /* Zero and One already set directly */

  /* The rest are set in terms of each other */
  Two = addf(One, One);
  Three = addf(Two, One);
  Four = addf(Three, One);
  Five = addf(Four, One);
  Eight = addf(Four, Four);
  Nine = mulf(Three, Three);
  TwentySeven = mulf(Nine, Three);
  ThirtyTwo = mulf(Four, Eight);
  /* 240 = 3 * 4 * 5 * 4 */
  tmp = mulf(Three, Four);
  tmp = mulf(Five, tmp);
  TwoForty = mulf(Four, tmp);
  MinusOne = negf(One);
  Half = divf(One, Two);
  OneAndHalf = addf(One, Half);

  /* set error count */
  ErrCnt = 0;

  /* Test values */
  tmp = addf(Zero, Zero);
  TstCond(eqf(tmp, Zero), "0+0 != 0");

  tmp = subf(One, One);
  TstCond(eqf(tmp, Zero), "1-1 != 0");

  TstCond(gtf(One, Zero), "1 <= 0");
  tmp = addf(One, One);

  TstCond(eqf(tmp, Two), "1+1 != 2");

  /* Negate zero and test */
  tmp = negf(Zero);
  TstCond(eqf(tmp, Zero), "negf(0) != 0");
  TstCond(isZero(tmp), "negf(0) not recognized as 0");

  /* Test unused negative zero */
  tmp = NegZero;
  TstCond(eqf(tmp, Zero), "-0 != 0");
  TstCond(isZero(tmp), "-0 not recognized as 0");

  tmp = addf(Two, One);
  TstCond(eqf(Three, tmp), "3 != 2+1");
  tmp = addf(Three, One);
  TstCond(eqf(Four, tmp), "4 != 3+1");

  /* test (Four + Two * (- Two) == Zero */
  tmp = negf(Two);
  tmp = mulf(Two, tmp);
  tmp = addf(Four, tmp);
  TstCond(eqf(tmp, Zero), "4+2*(-2) != 0");

  /* Four - Three - One */
  tmp = subf(Four, Three);
  tmp = subf(tmp, One);
  TstCond(eqf(tmp, Zero), "4-3-1 != 0");

  tmp = subf(Zero, One);
  TstCond(eqf(MinusOne, tmp), "-1 != (0-1)");

  tmp = addf(MinusOne, One);
  TstCond(eqf(tmp, Zero), "-1+1 != 0");

  tmp = addf(One, MinusOne);
  TstCond(eqf(tmp, Zero), "1+(-1) != 0");
  tmp = absf(One);
  tmp = addf(tmp, MinusOne);
  TstCond(eqf(tmp, Zero), "absf(1) + (-1) != 0");

  tmp = mulf(MinusOne, MinusOne);
  tmp = addf(tmp, MinusOne);
  TstCond(eqf(tmp, Zero), "-1+(-1)*(-1) != 0");

  tmp = addf(Half, MinusOne);
  tmp = addf(tmp, Half);
  TstCond(eqf(tmp, Zero), "1/2 + (-1) + 1/2 != 0");

  tmp = mulf(Three, Three);
  TstCond(eqf(tmp, Nine), "9 != 3*3");

  tmp = mulf(Nine, Three);
  TstCond(eqf(tmp, TwentySeven), "27 != 9*3");

  tmp = addf(Four, Four);
  tmp = mulf(tmp, Four);
  TstCond(eqf(tmp, ThirtyTwo), "32 != 8*4");

  tmp = subf(ThirtyTwo, TwentySeven);
  tmp = subf(tmp, Four);
  tmp = subf(tmp, One);
  TstCond(eqf(tmp, Zero), "32-27-4-1 != 0");

  tmp = addf(Four, One);
  TstCond(eqf(Five, tmp),"5 != 4+1");
  tmp = mulf(Four, Five);
  tmp = mulf(tmp, Three);
  tmp = mulf(tmp, Four);
  TstCond(eqf(TwoForty, tmp), "4*5*3*4 != 240");

  tmp = divf(TwoForty, Three);
  tmp2 = mulf(Four, Four);
  tmp2 = mulf(tmp2, Five);
  tmp = subf(tmp, tmp2);
  TstCond(eqf(tmp, Zero), "240/3 != 80");

  tmp = divf(TwoForty, Four);
  tmp2 = mulf(Five, Three);
  tmp2 = mulf(tmp2, Four);
  tmp = subf(tmp, tmp2);
  TstCond(eqf(tmp, Zero), "240/4 != 60");

  tmp = divf(TwoForty, Five);
  tmp2 = mulf(Four, Three);
  tmp2 = mulf(tmp2, Four);
  tmp = subf(tmp, tmp2);
  TstCond(eqf(tmp, Zero), "240/5 != 48");

  if (ErrCnt == 0) {
    printf ( "-1, 0, 1/2, 1, 2, 3, 4, 5, 9, 27, 32 & 240 are O.K.\n" );
    printf ( "All Tests Passed.\n");
  }
}
