/*
 *	NMH's Simple C Compiler, 2011,2012,2014
 *	sprintf()
 */

#define _ELFCLIB_
#include <stdio.h>

#pragma             extrn C_vformat

extern int _vformat(int mode, int max, void *dest, char *fmt, void **varg);

int sprintf(char *buf, const char *fmt, ...) {
	return _vformat(0, 0, buf, fmt, (void **) &fmt + 1);
}
