#define _ELFCLIB_
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#pragma             extrn Cfdopen

FILE	*_files[FOPEN_MAX];

FILE	*stdin, *stdout, *stderr;


int	errno = EOK;

//extern FILE *fdopen(int fd, int iomode);

void _init(void) {
	int	i;
		
	for (i=0; i<FOPEN_MAX; i++)
		_files[i] = NULL;

	stdin = fdopen(0, _FREAD);
	stdout = fdopen(1, _FWRITE);
	stderr = fdopen(2, _FWRITE);
	stdin->mode = _IOSYS;
	stdout->mode = _IOSYS;
	stderr->mode = _IOSYS;
}
