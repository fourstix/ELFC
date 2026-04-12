/*
 *	NMH's Simple C Compiler, 2012
 *	tmpfile()
 */
#define _ELFCLIB_
#include <stdio.h>

#pragma             extrn C_tmpid
#pragma             extrn Ctmpnam
#pragma             extrn Cfopen

extern int	_tmpid;

FILE *tmpfile(void) {
	FILE	*f;
	char	s[L_tmpnam];
	
	if (tmpnam(s) == NULL) return NULL;
	/* create file for read/write */
	if ((f = fopen(s, "w+")) == NULL) return NULL;
	/* Elf/OS doesn't allow the unix trick to pre-delete an open file */
	/*	remove(s); */
	/* Instead we store information to delete in fclose */
	f->mode = _IOTMP;
	f->tmpid = _tmpid-1;
	
	return f;
}
