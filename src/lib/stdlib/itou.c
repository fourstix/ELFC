#define _ELFCLIB_
#include <stdlib.h>

void itou(int n, char *s) {
  if (s == NULL) return;

  asm("         call lget16     ; get the unsigned integer value to convert");
  asm("           dw 0          ; from the argument stack");           
  asm("         copy ra, rd     ; copy integer for bios call");
  asm("         call lget16     ; get the destination pointer for string");
  asm("           dw 2          ; get pointer from argument stack");           
  asm("         copy ra, rf     ; set buffer pointer for bios call");
  asm("         call f_uintout  ; call elf bios function");
  asm("         ldi  0          ; terminate unsigned int string"); 
  asm("         str  rf         ; rf points to one past digits");
}
