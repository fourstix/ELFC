/*
 *	NMH's Simple C Compiler, 2012,2014
 *	sscanf()
 */

 #define _ELFCLIB_
 #include <stdio.h>

 #pragma             extrn C_vscan

extern int _vscan(int mode, void *src, char *fmt, void **varg);

int sscanf(char *src, const char *fmt, ...) {
	return _vscan(0, src, fmt, (void **) &fmt + 1);
}
