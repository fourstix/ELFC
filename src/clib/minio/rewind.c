/*
 *	NMH's Simple C Compiler, 2012
 *	rewind()
 */
#define _ELFCLIB_
#include <stdio.h>

/* define only extern procedures required */
#pragma           extrn Cfseek
#pragma           extrn Cclearerr

void rewind(FILE *f) {
	fseek(f, 0, SEEK_SET);
	clearerr(f);
}
