/*
 *	NMH's Simple C Compiler, 2012,2014
 *	printf()
 */
#define _ELFCLIB_
#include <stdio.h>

#pragma             extrn C_vformat
#pragma             extrn Cstdout

extern int _vformat(int mode, void *dest, char *fmt, void **varg);

int printf(const char *fmt, ...) {
	return _vformat(1, stdout, fmt, (void **) &fmt + 1);
}
