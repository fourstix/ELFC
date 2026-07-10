#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

extern float32_t _fp_one;
extern float32_t _fp_two;
extern float32_t _fp_ten;
extern float32_t _fp_10p5;
extern float32_t _fp_10n5;

#pragma             extrn Cgtef
#pragma             extrn Cdivf
#pragma             extrn Cltf
#pragma             extrn Cmulf
#pragma             extrn Csamef
#pragma             extrn Cnegf
#pragma             extrn Caddf
#pragma             extrn Ctruncf
#pragma             extrn Cftoi
#pragma             extrn Csubf

/* constant value used in routine */
#pragma .link .requires C_fp_const
#pragma             extrn C_fp_one
#pragma             extrn C_fp_two
#pragma             extrn C_fp_ten
#pragma             extrn C_fp_10p5
#pragma             extrn C_fp_10n5

/* Calculate log10(n) in integer output */
static int ilog10 (float32_t n)	{
	int rv = 0;

  /*
	 * Since this function is used for determining the
	 * number of digits in a number, treat zero as (single digit)
	 * and return zero instead of minus infinity
	 */
	if (isZero(n))
	 return rv;

	while (gtef(n, _fp_ten)) {	/* Decimate digit in right shift */
		if (gtef(n, _fp_10p5)) {
			//n /= 100000; rv += 5;
			n = divf(n, _fp_10p5);
			rv += 5;
		} else {
			n = divf(n, _fp_ten);
			rv++;
		}
	}
	while (ltf(n, _fp_one)) {		/* Decimate digit in left shift */
		if (ltf(n, _fp_10n5)) {
			//n *= 100000; rv -= 5;
			n = mulf(n, _fp_10p5);
			rv -=5;
		} else {
			//n *= 10; rv--;
			n = mulf(n, _fp_ten);
			rv--;
		}
		/* Largest value first */
		if (samef(_fp_one, n)) {
			break;
	  }
	}
	return rv;
}

/* Calculate 10^n as float */
static float32_t f10x (int n) {
	static float32_t rv;
	rv = _fp_one;

	while (n > 0) {		/* Left shift */
		if (n >= 5) {
			//rv *= 100000; n -= 5;
			rv = mulf(rv, _fp_10p5);
			n -= 5;
		} else {
			//rv *= 10; n--;
			rv = mulf(rv, _fp_ten);
			n--;
		}
	}
	while (n < 0) {		/* Right shift */
		if (n <= -5) {
			//rv /= 100000; n += 5;
			rv = divf(rv, _fp_10p5);
			n += 5;
		} else {
			//rv /= 10; n++;
			rv = divf(rv, _fp_ten);
			n++;
		}
	}
	return rv;
}

/*
 * Buffer to output the generated string
 * float32_t number to output
 * prec - Number of fractinal digits
 * fmt - 'f', 'e', 'E', 'g' or 'G' (C format style)
 */
int fstrf (char* buf, float32_t val, int prec, char fmt) {
	int d;
	int e = 0, m = 0;
	char sign = 0;
	float32_t w, tmp;
  char *er = 0;
	int strip = 0;
	int x = 0;
	char* start = buf;

	/* Handle special values first (Zero handled by format)*/
	if (isNaN(val)) {
		/* Not a number */
		er = "NaN";
		/* No sign for not a number */
		sign = 0;
	} else if (isInf(val)) {
		/* Infinite */
		er = "Inf";
		/* show sign for infinity */
		if (isNeg(val)) {
			sign = '-';
		} else {
			sign = '+';
		}
	} else {
		strip = 0;
		/* negative precision means always show sign */
		if (prec < 0) {
			prec = -prec;
			sign = '+';
		}
		/* Handle negative value */
		if (isNeg(val)) {
			val = negf(val);
			sign = '-';
		}
		/* check exponent size for g and f formats */
		e = ilog10(val);

		if (fmt == 'g' || fmt == 'G') {
			if (isZero(val)) {
				/* print 0 as a single '0' */
				*buf++ = '0';
				*buf = 0;
				return 1;
				/* check for e between -4 and precision, treating 0 as 1 */
			}
			/* g format strips zeros from end */
			if (prec > 0)
			  strip = 1;

      if ((e >= -4) && (e < (prec ? prec : 1))) {
				fmt = 'f';
		  } else {
			  /* Otherwise g format prints exponent */
			  if (fmt == 'g') {
					fmt = 'e';
			  } else {
					fmt = 'E';
			  }
		  }
	  }

		if (fmt == 'f') {
			if (e < 0) {
				e = 0;
			}
		  /* if precision out of range of buffer, use E format */
		  if (e + prec + 3 >= FP_BUF_SZ) {
				fmt = 'E';
			}	/* Buffer overflow? */
		}

		if (fmt == 'f') {	/* Decimal notation? */
			//val += f10x(-prec) / 2;
			/* Round (nearest) */
			tmp = f10x(-prec);
			tmp = divf(tmp, _fp_two);
			val = addf(val, tmp);
			m = ilog10(val);
			if (m < 0) m = 0;
			/* If overflow buffer, switch to E format */
		} else {
			/* E notation */
			if (!isZero(val)) {		/* Not a true zero? */
				/*if precision too high set to max */
				if (prec > 7) {
					/*
					* format size is 8 chars for 1 sign, 1 digit, one decimal,
					*    four exponent chars and one null
					* FP_BUF_SZ - format size = 15 - 8 = 7 precision digits max
					*/
					prec = 7;
				}
				/* Round (nearest) */
				tmp = f10x(ilog10(val) - prec);
				tmp = divf(tmp, _fp_two);
				val = addf(val, tmp);
				e = ilog10(val);
				/* Normalize */
				tmp = f10x(e);
				val = divf(val, tmp);
			}
	  }
  }
	if (!er) {
		/* Not error condition */
		if (sign) *buf++ = sign;	/* Add a - if negative value */
		do {
			/* Put decimal number */
			w = f10x(m);				/* Snip the highest digit d */
			/* debugging, print m and w */
			tmp = divf(val, w);
			/*	d = val / w truncates float to int */
			tmp = truncf(tmp);
			d = ftoi(tmp);

			//val -= d * w;
			tmp = mulf(tmp, w);
			val = subf(val, tmp);

			if (m == -1) *buf++ = '.';	/* Insert a decimal separarot if get into fractional part */
			*buf++ = '0' + d;			/* Put the digit */
		} while (--m >= -prec);			/* Output all digits specified by prec */

		/* if this was 'g' or 'G' strip off zeros */
		if (strip) {
			buf--;
			while (*buf == '0')
				buf--;
			// If all decimals were zeros, remove "." as well .
			if (*buf != '.') {
				buf++;
			 }
		}

		if (fmt != 'f') {	/* Put exponent if needed */
			*buf++ = fmt;
			if (e < 0) {
				e = -e; *buf++ = '-';
			} else {
				*buf++ = '+';
			}
			*buf++ = '0' + e / 10;
			*buf++ = '0' + e % 10;
		}
	} else {
		/* Error condition: NaN, +Inf or -Inf */
		if (sign) *buf++ = sign;		/* Add sign if needed */
		do *buf++ = *er++; while (*er);	/* Put error symbol */
	}
	*buf = 0;
	/* return number of characters written */
	return (buf - start);
}
