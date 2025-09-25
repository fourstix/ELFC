#define _ELFCLIB_
#include <stdlib.h>


void itoa(int n, char *s) {
  if (s == NULL) return;

  asm("         gosub s_lget16  ; get the integer value to convert");
  asm("           dw 0          ; get integer from argument stack");           
  asm("         copy ra, rd     ; copy integer for conversion");
  asm("         gosub s_lget16  ; get the destination pointer for string");
  asm("           dw 2          ; get pointer from argument stack");           
  asm("         copy ra, rf     ; copy pointer for function call");
  asm("         call f_intout   ; call elf bios function");  
  asm("         ldi  0          ; terminate string"); 
  asm("         str  rf         ; rf points to one past int digits");
}
