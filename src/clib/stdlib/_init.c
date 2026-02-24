#define _ELFCLIB_
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#pragma             extrn Cfdopen
#pragma             extrn Cmalloc

int   _fdtable[FD_MAX];

FILE	*_files[FOPEN_MAX];

FILE	*stdin, *stdout, *stderr;

char	*_lbuf;

int	errno = EOK;

void _init(void) {
	int	i;

/* To use breakpoints before main, we must set up handler here */
#ifdef _STGROM_
  asm("load   r1, $F000  ; set up handler for STG Breakpoint");
#endif

	/* set pre-defined file handles */

	_fdtable[0] = 0;
	_fdtable[1] = 1;
	_fdtable[2] = 2;

	/* set system handles in table as unused */

	for (i=FD_SYS; i<FD_MAX; i++)
		_fdtable[i] = EOF;

	for (i=0; i<FOPEN_MAX; i++)
		_files[i] = NULL;

	/* create pre-defined file streams */

	stdin = fdopen(0, _FREAD);
	stdout = fdopen(1, _FWRITE);
	stderr = fdopen(2, _FWRITE);
	stdin->mode = _IOSYS;
	stdout->mode = _IOSYS;
	stderr->mode = _IOSYS;


	/* set up line buffer for stdio */
	_lbuf = (char *) malloc(_BUFLEN);
}
