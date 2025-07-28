/*
 *	NMH's Simple C Compiler, 2012
 *	rewind()
 */
#define _ELFCLIB_
#include <stdio.h>

/* define only extern procedures required */
#pragma           extrn Cfseek
#pragma           extrn Cclrerror

void rewind(FILE *f) {
	fseek(f, 0, SEEK_SET);
	clrerror(f);
}
