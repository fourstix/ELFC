/*
 *	NMH's Simple C Compiler, 2014
 *	vfprintf()
 */
 #define _ELFCLIB_
 #include <stdio.h>

 #pragma             extrn C_vformat

extern int _vformat(int mode, void *dest, char *fmt, void **varg);

int vfprintf(FILE *f, const char *fmt, void **args) {
	return _vformat(1, f, fmt, args);
}
