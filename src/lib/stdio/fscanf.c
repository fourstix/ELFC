/*
 *	NMH's Simple C Compiler, 2012,2014
 *	fscanf()
 */

 #define _ELFCLIB_
 #include <stdio.h>
 
 #pragma             extrn C_vscan
 
extern int _vscan(int mode, void *src, char *fmt, void **varg);

int fscanf(FILE *f, char *fmt, ...) {
	return _vscan(1, f, fmt, (void **) &fmt + 1);
}
