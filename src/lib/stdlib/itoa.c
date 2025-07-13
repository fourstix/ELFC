#define _ELFCLIB_
#include <stdlib.h>


void itoa(int n, char *s) {
  if (s == NULL) return;

  asm("         call lget16     ; get the integer value to convert");
  asm("           dw 0          ; get integer from argument stack");           
  asm("         copy ra, rc     ; copy integer for function call");
  asm("         call lget16     ; get the destination pointer for string");
  asm("           dw 2          ; get pointer from argument stack");           
  asm("         copy ra, rd     ; copy pointer for function call");
  asm("         call itoa16     ; call elf itoa function");

}
