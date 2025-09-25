#define _ELFCLIB_
#include <stdio.h>
#include <string.h>


#pragma             extrn Cputs
#pragma             extrn C_fwrite
#pragma             extrn Cstrlen
#pragma .link .requires Cfwrite
#pragma .link .library string.lib

int fputs(char *s, FILE *f) {
	int	k;
  
  k = strlen(s);
  
	/* fputs doesn't append newline at end of string */
	if (f->mode == _IOSYS) {
		asm("         gosub s_lget16    ; put buffer pointer variable");
		asm("           dw  0           ; offset for arg 1 ");         
		asm("         copy  ra, rf      ; ra holds buffer pointer to string");
		asm("         call  O_MSG       ; output string to elf/os"); 
  } else if (_fwrite(s, k, f) != k)
    return EOF;
  return k;

}
