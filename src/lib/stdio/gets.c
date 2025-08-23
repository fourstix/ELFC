#define _ELFCLIB_
#include <stdio.h>

char* gets(char *s) {
  char* p;
  p = s;
  if (p != NULL) {
    asm("         call  lget16      ; get pointer from local variable");
    asm("           dw  -2          ; put buffer pointer in ra");
    asm("         copy  ra, rf      ; set buffer pointer");
    asm("         call  O_INPUT     ; read a string into the buffer");
  }
  return p;
}
