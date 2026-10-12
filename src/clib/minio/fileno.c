/*
 *	NMH's Simple C Compiler, 2012
 *	fileno()
 */
#define _ELFCLIB_
#include <stdio.h>

int fileno(FILE *f) {
	return f->fd;
}
