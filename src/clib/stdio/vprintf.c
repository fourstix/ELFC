/*
 *	NMH's Simple C Compiler, 2014
 *	vprintf()
 */
 #define _ELFCLIB_
 #include <stdio.h>
 
 #pragma             extrn C_vformat
 #pragma             extrn Cstdout

extern int _vformat(int mode, int max, void *dest, char *fmt, void **varg);

int vprintf(char *fmt, void **args) {
	return _vformat(1, 0, stdout, fmt, args);
}
