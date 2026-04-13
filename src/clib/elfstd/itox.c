#define _ELFCLIB_
#include <stdlib.h>

/* define BIOS API used */
#pragma #define f_hexout4 0ff4bh

void itox(int n, char *s) {
  if (s == NULL) return;

  asm("         gosub s_lget16  ; get the unsigned integer value to convert");
  asm("           dw 0          ; from the argument stack");
  asm("         copy  ra, rd    ; copy integer for bios call");
  asm("         gosub s_lget16  ; get the destination pointer for string");
  asm("           dw 2          ; get pointer from argument stack");
  asm("         copy  ra, rf    ; set buffer pointer for bios call");
  asm("         sex   r2        ; make sure X points to stack");
  asm("         call f_hexout4  ; call elf bios function");
  asm("         ldi  0          ; terminate hex string");
  asm("         str  rf         ; rf points to one past hex digits");
  return;
}
