/*
 *	NMH's Simple C Compiler, 2014
 *	vprintf()
 */
 #define _ELFCLIB_
 #include <stdio.h>

 #pragma             extrn C_vformat
 #pragma             extrn Cstdout

extern int _vformat(int mode, void *dest, char *fmt, void **varg);

int vprintf(const char *fmt, void **args) {
	return _vformat(1, stdout, fmt, args);
}
