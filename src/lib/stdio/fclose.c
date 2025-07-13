/*
 *	NMH's Simple C Compiler, 2012
 *	fclose()
 */
#define _ELFCLIB_
#include <stdlib.h>
#include <stdio.h>

#pragma .link .requires C_fdinit
#pragma             extrn Cclose
#pragma             extrn Cfree
#pragma             extrn Cerrno
#pragma             extrn C_files

extern FILE	*_files[];

int fclose(FILE *f) {
	int	i;

	if (NULL == f) return _FCLOSED;
	//grw - don't close stdin, stdout or stderr, but return success
	if (_IOSYS == f->mode) return _FCLOSED;
	
	close(f->fd);
	
	for (i=3; i<FOPEN_MAX; i++) {
		if (f == _files[i]) {
			_files[i] = NULL;
			break;
		}
	}	
	free(f);
	return _FCLOSED;
}
