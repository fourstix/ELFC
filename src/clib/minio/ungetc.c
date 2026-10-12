/*
 *	NMH's Simple C Compiler, 2012
 *	ungetc()
 */
#define _ELFCLIB_
#include <stdio.h>
#include <errno.h>

#pragma             extrn Cerrno

int ungetc(int c, FILE *f) {
	if (f == NULL || c == EOF) {
		errno = EINVAL;
		return EOF;
	}
	/* only one character allowed in buffer */
	if (f->ch != EOF) return EOF;
	/* ungetting a character removes EOF */
	f->iom &= ~_FEOF;
	return f->ch = c;
}
