/*
 *	NMH's Simple C Compiler, 2012,2014
 *	scanf()
 */

 #define _ELFCLIB_
 #include <stdio.h>
 
 #pragma             extrn C_vscan
 #pragma             extrn Cstdin

extern int _vscan(int mode, void *dest, char *fmt, void **varg);

int scanf(char *fmt, ...) {
	return _vscan(1, stdin, fmt, (void **) &fmt + 1);
}
