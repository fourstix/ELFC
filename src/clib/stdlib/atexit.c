/*
 *	NMH's Simple C Compiler, 2012
 *	atexit()
 */
#define _ELFCLIB_
#include <errno.h>

#pragma             extrn Cerrno

int	(*_exitfn)() = 0;

int atexit(int (*fn)()) {
	if (_exitfn) {
		errno = ENOMEM;
		return -1;
	}
	_exitfn = fn;
	return 0;
}
