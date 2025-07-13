/*
 *	NMH's Simple C Compiler, 2011,2012
 *	fdopen()
 */
#define _ELFCLIB_
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#pragma .link .requires C_fdinit
#pragma             extrn C_files
#pragma             extrn Cfclose
#pragma             extrn Cerrno
#pragma             extrn Cmalloc

extern FILE	*_files[];

FILE *fdopen(int fd, int iomode) {
	int	i;
	FILE	*f;

	for (i = 0; i < FOPEN_MAX; i++) {
		if (NULL == _files[i])
			break;
	}		
	if (i >= FOPEN_MAX) {
		errno = ENFILE;
		return NULL;
	}
	
	if ((f = malloc(sizeof(FILE))) == NULL)
		return NULL;
	
	_files[i] = f;
	f->fd   = fd;
	f->iom  = iomode;
	f->last = _FCLOSED;
	f->mode = _IONBF;
	f->ch   = EOF;
	
	//grw - if mode was invalid, close and return error
	if (_FERROR == f->iom) {
		fclose(f);
		errno = EINVAL;
		return NULL;
	}
  //grw - no buffers since Elf/OS file I/O is already buffered
	return f;
}
