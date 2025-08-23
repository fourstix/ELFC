#define _ELFCLIB_
#include <stdio.h>

int putstr(char* s) {  
  if (s == NULL) return EOF;
  
  asm("         call  lget16      ; put buffer pointer variable");
  asm("           dw  0           ; offset for arg 1 ");         
  asm("         copy  ra, rf      ; ra holds result of assigning pointer");
  asm("         call  O_MSG       ; output string to elf/os"); 
  
  return 1;
}
