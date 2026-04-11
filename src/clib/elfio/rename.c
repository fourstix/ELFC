#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>

#pragma             extrn Cerrno

int rename(const char *old, const char *new) {
	int result;
	/* nulls are invalid */
	if(old == NULL || new == NULL) {
		errno = EINVAL;
		return EOF;
	}

	asm("         gosub s_lget16  ; get the old name argument ");
	asm("           dw 0          ; get from argument stack");
	asm("         copy ra, rf     ; copy path string to buffer pointer");
	asm("         gosub s_lget16  ; get the new name argument ");
	asm("           dw 2          ; get from argument stack");
	asm("         copy ra, rc     ; copy path string to buffer pointer");

	asm("         push rb         ; save stack frame base pointer on the stack");
	asm("         call O_RENAME   ; attempt to rename the file");
	asm("         pop rb          ; restore stack frame base pointer from the stack");

	asm("         ldi  0          ; set default value for success");
	asm("         lsnf            ; DF = 0, means success");
	asm("         ldi  $Ff        ; otherwise set result for error");
	asm("         phi  ra         ; set result for 0 or -1 ");
	asm("         plo  ra         ; set result in ra ");
	asm("         gosub s_lset16  ; set the result argument ");
	asm("           dw -2         ; in the local variable on the stack");

	if (result == EOF)
		errno = EIO;

	return result;
}
