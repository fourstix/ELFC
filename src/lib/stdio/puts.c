#include "_stdio.h"

int puts(char* s) {  
  if (s == NULL) return EOF;
  asm("         call  lget16      ; put buffer pointer variable");
  asm("           dw  0           ; offset for arg 1 ");         
  asm("         copy  ra, rf      ; ra holds result of assigning pointer");
  asm("         call  o_msg       ; output string to elf/os"); 
  asm("         call  o_inmsg     ; output newline after string");
  asm("           db 10,0");  
  return 1;
}
