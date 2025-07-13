#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>

#pragma             extrn Cerrno

int rename(char *old, char *new) {
	int result;
	/* nulls are invalid */
	if(old == NULL || new == NULL) {
		errno = EINVAL;
		return EOF;
	}
	
	asm("         call lget16     ; get the old name argument ");
	asm("           dw 0          ; get from argument stack");           
	asm("         copy ra, rf     ; copy path string to buffer pointer");
	asm("         call lget16     ; get the new name argument ");
	asm("           dw 2          ; get from argument stack");           
	asm("         copy ra, rc     ; copy path string to buffer pointer");
	asm("         call o_rename   ; attempt to rename the file");
	asm("         ldi  0          ; set default value for success");
	asm("         lsnf            ; DF = 0, means success");
	asm("         ldi  $Ff        ; otherwise set result for error");
	asm("         phi  ra         ; set result for 0 or -1 ");
	asm("         plo  ra         ; set result in ra ");
	asm("         call lset16     ; set the result argument ");
	asm("           dw -2         ; in the local variable on the stack");           
	
	if (result == EOF)
		errno = EIO;

	return result;
}
