#define _ELFCLIB_
#include <stdio.h>

int puts(char* s) {  
  if (s == NULL) return EOF;
  asm("         gosub s_lget16      ; put buffer pointer variable");
  asm("           dw  0           ; offset for arg 1 ");         
  asm("         copy  ra, rf      ; ra holds result of assigning pointer");
  asm("         call  O_MSG       ; output string to elf/os"); 
  asm("         call  O_INMSG     ; output newline after string");
  asm("           db 10,0");
  return 1;
}
