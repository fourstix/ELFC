#define _ELFCLIB_
#include <stdlib.h>

void itox(int n, char *s) {
  if (s == NULL) return;

  asm("         gosub s_lget16  ; get the unsigned integer value to convert");
  asm("           dw 0          ; from the argument stack");
  asm("         copy  ra, rd    ; copy integer for bios call");
  asm("         gosub s_lget16  ; get the destination pointer for string");
  asm("           dw 2          ; get pointer from argument stack");
  asm("         copy  ra, rf    ; set buffer pointer for bios call");
  asm("         sex   r2        ; make sure X points to stack");
  asm("         ldi   4         ; 4 nybbles to display");
  asm("hexlp:   stxd            ; save the count");
  asm("         ldi   0         ; zero the temp var");
  asm("         plo   re");
  asm("         ldi   4         ; perform 4 shift");
  asm("hexl2:   stxd            ; save count");
  asm("         glo   rd        ; perform shift");
  asm("         shl");
  asm("         plo   rd");
  asm("         ghi   rd");
  asm("         shlc");
  asm("         phi   rd");
  asm("         glo   re");
  asm("         shlc");
  asm("         plo   re");
  asm("         irx             ; point back to count");
  asm("         ldi   1         ; need to decrement it");
  asm("         sd");
  asm("         lbnz  hexl2     ; jump if more shifts needed");
  asm("         glo   re        ; get nybble");
  asm("         smi   10        ; compare to 10");
  asm("         lbdf  hexal     ; jump if alpha");
  asm("         glo   re        ; get value");
  asm("         adi   30h       ; convert to ascii");
  asm("hexl3:   str   rf        ; store value into buffer");
  asm("         inc   rf");
  asm("         irx             ; point to count");
  asm("         ldi   1         ; need to subtract 1 from it");
  asm("         sd");
  asm("         lbnz  hexlp     ; loop if not done");
  asm("         lbr   hexdone   ; hex conversion is done");
  asm("hexal:   glo   re        ; get value");
  asm("         adi   55        ; convert to ascii");
  asm("         lbr   hexl3     ; and continue");
  asm("hexdone: ldi  0          ; terminate hex string");
  asm("         str  rf         ; rf points to one past hex digits");
  return;
}
