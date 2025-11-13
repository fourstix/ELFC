/*
 *	NMH's Simple C Compiler, 2014
 *	vsprintf()
 */
 #define _ELFCLIB_
 #include <stdio.h>

 #pragma             extrn C_vformat

extern int _vformat(int mode, int max, void *dest, char *fmt, void **varg);

int vsprintf(char *buf, const char *fmt, void **args) {
	return _vformat(0, 0, buf, fmt, args);
}
