/*
 *	NMH's Simple C Compiler, 2014
 *	vfprintf()
 */
 #define _ELFCLIB_
 #include <stdio.h>
 
 #pragma             extrn C_vformat

extern int _vformat(int mode, int max, void *dest, char *fmt, void **varg);

int vfprintf(FILE *f, char *fmt, void **args) {
	return _vformat(1, 0, f, fmt, args);
}
