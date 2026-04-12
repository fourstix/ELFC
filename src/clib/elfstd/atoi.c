#define _ELFCLIB_
#include <stdlib.h>
#include <ctype.h>

#pragma             extrn Cisspace

#pragma .link .library ctype.lib

/* define bios API used */
#pragma #define f_atoi 0ff5dh

int atoi(const char *s) {
  int i;

  if (s == NULL) return 0;

  /* skip over any leading whitespace */
  while(isspace(*s)) s++;

  /* skip over leading plus */
  if(*s == '+') s++;

  asm("           gosub s_lget16     ; get the buffer pointer for string");
  asm("             dw 0             ; get pointer from argument stack");
  asm("           copy ra, rf        ; copy pointer for function call");
  asm("           sex     r2         ; make sure X = SP");
  asm("           call    f_atoi     ; call BIOS routine");
  asm("           copy    rd, ra     ; copy result into accumulator");
  asm("           gosub   s_lset16   ; set integer value for return");
  asm("             dw -2            ; set local variable on stack");

	return i;
}
