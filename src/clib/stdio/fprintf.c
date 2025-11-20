/*
 *	NMH's Simple C Compiler, 2012,2014
 *	fprintf()
 */

 #define _ELFCLIB_
 #include <stdio.h>

 #pragma             extrn C_vformat

extern int _vformat(int mode, int max, void *dest, char *fmt, void **varg);

int fprintf(FILE *f, const char *fmt, ...) {
	return _vformat(1, 0, f, fmt, (void **) &fmt + 1);
}
