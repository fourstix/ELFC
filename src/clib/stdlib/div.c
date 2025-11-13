/*
 * Copyright (c) 1990 Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 */
#define _ELFCLIB_
#include <stdlib.h>

div_t div(int num, int denom) {
  static div_t rp;
	rp.quot = num / denom;
	rp.rem = num % denom;
	/*
	 *	if num >= 0, but r.rem < 0, we got the wrong answer.
	 * In that case, to get the right answer, add 1 to r.quot and
	 * subtract denom from r.rem.
	 */
	if (num >= 0 && rp.rem < 0) {
		rp.quot++;
		rp.rem -= denom;
	}
	return rp;
}
