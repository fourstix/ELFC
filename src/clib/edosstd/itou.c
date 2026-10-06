#define _ELFCLIB_
#include <stdlib.h>

/* Convert unsigned integer number to ascii
 * RD - number to convert
 * RF - buffer to store
 */
void itou(unsigned int n, char *s) {
  if (s == NULL) return;

  asm("         gosub s_lget16      ; get the unsigned integer value to convert");
  asm("           dw 0              ; from the argument stack");
  asm("         copy  ra, rd        ; copy integer for bios call");
  asm("         gosub s_lget16      ; get the destination pointer for string");
  asm("           dw 2              ; get pointer from argument stack");
  asm("         copy  ra, rf        ; set buffer pointer for bios call");

  asm("         sex   r2            ; make sure X points to stack");
  asm("         ldi   high numbers  ; point to numbers");
  asm("         phi   rc");
  asm("         ldi   low numbers");
  asm("         plo   rc");
  asm("         lda   rc            ; get first division");
  asm("         phi   ra");
  asm("         lda   rc");
  asm("         plo   ra");
  asm("         ldi   0             ; leading zero flag");
  asm("         stxd                ; store onto stack");
  asm("nxtiter: ldi   0             ; star count at zero");
  asm("         plo   r8            ; place into low of r8");
  asm("divlp:   glo   ra            ; get low of number to subtrace");
  asm("         str   r2            ; place into memory");
  asm("         glo   rd            ; get low of number");
  asm("         sm                  ; subtract");
  asm("         phi   r8            ; place into temp space");
  asm("         ghi   ra            ; get high of subtraction");
  asm("         str   r2            ; place into memory");
  asm("         ghi   rd            ; get high of number");
  asm("         smb                 ; perform subtract");
  asm("         lbnf  nomore        ; jump if subtraction was too large");
  asm("         phi   rd            ; store result");
  asm("         ghi   r8");
  asm("         plo   rd");
  asm("         inc   r8            ; increment count");
  asm("         lbr   divlp         ; and loop back");
  asm("nomore:  irx                 ; point back to leading zero flag");
  asm("         glo   r8");
  asm("         lbnz  nonzero       ; jump if not zero");
  asm("         ldn   r2            ; get flag");
  asm("         lbnz  allow0        ; jump if no longer zero");
  asm("         dec   r2            ; keep leading zero flag");
  asm("         lbr   findnxt       ; skip output");
  asm("allow0:  ldi   0             ; recover the zero");
  asm("nonzero: adi   30h           ; convert to ascii");
  asm("         str   rf            ; store into buffer");
  asm("         inc   rf");
  asm("         ldi   1             ; need to set leading flag");
  asm("         stxd                ; store it");
  asm("findnxt: dec   ra            ; subtract 1 for zero check");
  asm("         glo   ra            ; check for end");
  asm("         lbz   intdone       ; jump if done");
  asm("         lda   rc            ; get next number");
  asm("         phi   ra");
  asm("         lda   rc");
  asm("         plo   ra");
  asm("         smi   1             ; see if at last number");
  asm("         lbnz  nxtiter       ; jump if not");
  asm("         irx                 ; set leading flag");
  asm("         ldi   1");
  asm("         stxd");
  asm("         lbr   nxtiter");
  asm("intdone: irx                 ; put x back where it belongs");
  asm("         ldi  0              ; terminate unsigned int string");
  asm("         str  rf             ; rf points to one past digits");
  return;
  asm("numbers:   db      027h,010h,3,0e8h,0,100,0,10,0,1");

/*    asm("         call f_uintout  ; call elf bios function"); */
}
