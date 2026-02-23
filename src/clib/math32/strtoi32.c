#define _ELFCLIB_
#include <ctype.h>
#include <errno.h>
#include <math32.h>

#pragma             extrn Cisspace
#pragma             extrn Cisdigit
#pragma             extrn Cisalpha
#pragma             extrn Cisupper
#pragma             extrn Ccmp32
#pragma             extrn Csub32
#pragma             extrn Cadd32
#pragma             extrn Cneg32
#pragma             extrn Cmul32
#pragma             extrn Cdiv32
#pragma             extrn Cerrno

int32_t strtoi32(const char *nptr, char **endptr, int base)
{
	const char *s;
	int32_t acc, cutoff;
	int c;
	int neg, any;
	int32_t cutlim;
    int32_t int32_max;
	int32_t int32_min;
	int32_t base_int;
	int32_t one;
	int32_t c_int;
	int cmp;

	/*
	 * Skip white space and pick up leading +/- sign if any.
	 * If base is 0, allow 0x for hex and 0 for octal, else
	 * assume decimal; if base is already 16, allow 0x.
	 */
	s = nptr;
	do {
		c = (unsigned char) *s++;
	} while (isspace(c));
	if (c == '-') {
		neg = 1;
		c = *s++;
	} else {
		neg = 0;
		if (c == '+')
			c = *s++;
	}
	if ((base == 0 || base == 16) &&
	    c == '0' && (*s == 'x' || *s == 'X')) {
		c = s[1];
		s += 2;
		base = 16;
	}
	if (base == 0)
		base = c == '0' ? 8 : 10;
	/*
	 * Compute the cutoff value between legal numbers and illegal
	 * numbers.  That is the largest legal value, divided by the
	 * base.  An input number that is greater than this value, if
	 * followed by a legal input character, is too big.  One that
	 * is equal to this value may be valid or not; the limit
	 * between valid and invalid numbers is then based on the last
	 * digit.  For instance, if the range for longs is
	 * [-2147483648..2147483647] and the input base is 10,
	 * cutoff will be set to 214748364 and cutlim to either
	 * 7 (neg==0) or 8 (neg==1), meaning that if we have accumulated
	 * a value > 214748364, or equal but the next digit is > 7 (or 8),
	 * the number is too big, and we will return a range error.
	 *
	 * Set any if any `digits' consumed; make it negative to indicate
	 * overflow.
	 */
	int32_min.high = 0x8000;
	int32_min.low = 0x0000;
	int32_max.high = 0x7fff;
	int32_max.low = 0xffff;
	base_int.high = 0;
	base_int.low = base;
	one.high = 0;
	one.low = 1;

	cutoff = neg ? int32_min : int32_max;
	/* cutlim = cutoff % base; */
	div32(&cutoff, &base_int, &cutlim);

	/* cutoff /= base; */
	cutoff = div32(&cutoff, &base_int, NULL);
	if (neg) {
		/* if (cutlim > 0) */
		if ((cutlim.high & 0x8000) == 0) {
			/* cutlim -= base; */
			cutlim = sub32(&cutlim, &base_int);
			/* cutoff += 1; */
			cutoff = add32(&cutoff, &one);
		}
		/* cutlim = -cutlim; */
		cutlim = neg32(&cutlim);
	}
	acc.high = 0;
	acc.low = 0;
	for (any = 0;; c = (unsigned char) *s++) {
		if (isdigit(c))
			c -= '0';
		else if (isalpha(c))
			c -= isupper(c) ? 'A' - 10 : 'a' - 10;
		else
			break;
		if (c >= base)
			break;
		if (any < 0)
			continue;
		if (neg) {
			/* if (acc < cutoff || (acc == cutoff && c > cutlim)) { */
			cmp = cmp32(&acc, &cutoff);
			if (cmp < 0 || (cmp == 0 && c > cutlim.low)) {
				any = -1;
				acc = int32_min;
				errno = ERANGE;
			} else {
				any = 1;
				/* acc *= base; */
				acc = mul32(&acc, &base_int);
				/* acc -= c; */
				c_int.high = 0;
				c_int.low = c;
				acc = sub32(&acc, &c_int);
			}
		} else {
			/* if (acc > cutoff || (acc == cutoff && c > cutlim)) { */
			cmp = cmp32(&acc, &cutoff);
			if (cmp > 0 || (cmp == 0 && c > cutlim.low)) {
				any = -1;
				acc = int32_max;
				errno = ERANGE;
			} else {
				any = 1;
				/* acc *= base; */
				acc = mul32(&acc, &base_int);
				/* acc += c; */
				c_int.high = 0;
				c_int.low = c;
				acc = add32(&acc, &c_int);
			}
		}
	}

	if (endptr != NULL) {
		/* endptr = (char *) (any ? s - 1 : nptr); */
		if (any) {
			*endptr = (char *)(s - 1);
		}
		else {
			*endptr = (char *)nptr;
		}
	}

	return (acc);
}
