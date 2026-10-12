#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "edos.h"

#pragma             extrn Cerrno
#pragma             extrn Cstrpbrk

#ifndef _ELFCLIB_
#pragma .link .library string.lib
#endif

int _rename(const char *old, const char *new) {
	int result;
	/* nulls are invalid, as well as new names with a drive or path delimiters */
	if(old == NULL || new == NULL || strpbrk(new, "/\\:")) {
		errno = EINVAL;
		return EOF;
	}

	asm("         gosub s_lget16  ; get the old name argument ");
	asm("           dw 0          ; get from argument stack");
	asm("         copy ra, rf     ; copy path string to buffer pointer");
	asm("         gosub s_lget16  ; get the new name argument ");
	asm("           dw 2          ; get from argument stack");
	asm("         copy ra, rd     ; copy name string to buffer pointer");
	_KSAVE
	asm("         call K_FILE_RENAME ; attempt to rename the file");
	_KRESTORE
	_KRESULT
	asm("         gosub s_lset16  ; set the result argument ");
	asm("           dw -2         ; in the local variable on the stack");

	if (result == EOF)
		errno = EIO;

	return result;
}
