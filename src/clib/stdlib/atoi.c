#define _ELFCLIB_
#include <stdlib.h>
#include <ctype.h>

/* define only extern procedures required */
#pragma           extrn Cisspace

int atoi(const char *s) {
  int i;

  if (s == NULL) return 0;

  /* skip over any leading whitespace */
  while(isspace(*s)) s++;

  /* skip over leading plus */
  if(*s == '+') s++;


  asm(";----------------------------------------------");
  asm(";      Convert ASCII string to integer");
  asm("; registers used:");
  asm(";  RF - Pointer to Buffer with ASCII number string");
  asm(";  RD - Sign flag for negative values");
  asm(";  R8 - Temporary value");
  asm(";  RC - Converted 16-bit integer value");
  asm(";----------------------------------------------");


  asm("           gosub s_lget16  ; get the buffer pointer for string");
  asm("             dw 0          ; get pointer from argument stack");
  asm("           copy ra, rf     ; copy pointer for function call");
  asm("           sex     r2              ; make sure X = SP");
  asm("           ldi     0               ; zero result");
  asm("           plo     rc");
  asm("           phi     rc");
  asm("           plo     rd               ; and negative flag");
  asm("           ldn     rf               ; get first byte");
  asm("           smi     '-'              ; is it negative sign");
  asm("           lbnz    atoi_0_1         ; jump if not");
  asm("           inc     rf               ; move past negative");
  asm("           inc     rd               ; set flag for negative number");
  asm("atoi_0_1:  lda     rf               ; get next byte of input");
  asm("           plo     re               ; set aside");
  asm("           smi     '0'              ; see if below below numbers");
  asm("           lbnf    atoi_no          ; done if so");
  asm("           smi     10               ; see if character is above numbers");
  asm("           lbnf    atoi_0_2         ; jump if actual numeral");
  asm("atoi_no:   glo     rd               ; recover sign flag");
  asm("           shr                      ; shift it into DF");
  asm("           lbnf    atoi_rt          ; jump if number is positive");
  asm("           glo     rc               ; 2's comp. the number");
  asm("           xri     0ffh");
  asm("           adi     1");
  asm("           plo     rc");
  asm("           ghi     rc");
  asm("           xri     0ffh");
  asm("           adci    0");
  asm("           phi     rc");
  asm("atoi_rt:   lbr     atoi_done        ; return from subroutine");
  asm("atoi_0_2:  glo     re               ; retrieve character");
  asm("           smi     '0'              ; convert to binary number");
  asm("           plo     re               ; set it aside");
  asm("           glo     rc               ; multiply result by 2");
  asm("           shl");
  asm("           plo     rc");
  asm("           plo     r8               ; keep a copy in R8");
  asm("           ghi     rc");
  asm("           shlc");
  asm("           phi     rc");
  asm("           phi     r8");
  asm("           glo     r8               ; multiply R8 by 2 (original by 4)");
  asm("           shl");
  asm("           plo     r8");
  asm("           ghi     r8");
  asm("           shlc");
  asm("           phi     r8");
  asm("           glo     r8               ; multiply R8 by 4 (original by 8)");
  asm("           shl");
  asm("           plo     r8");
  asm("           ghi     r8");
  asm("           shlc");
  asm("           phi     r8");
  asm("           glo     r8               ; now add x8 with x2 to get x10");
  asm("           str     r2");
  asm("           glo     rc");
  asm("           add");
  asm("           plo     rc");
  asm("           ghi     r8");
  asm("           str     r2");
  asm("           ghi     rc");
  asm("           adc");
  asm("           phi     rc");
  asm("           glo     re               ; retrieve new value");
  asm("           str     r2               ; and add it into result");
  asm("           glo     rc");
  asm("           add");
  asm("           plo     rc");
  asm("           ghi     rc");
  asm("           adci    0");
  asm("           phi     rc");
  asm("           lbr     atoi_0_1   ; loop back for more digits");
  asm("atoi_done: copy    rc, ra     ; copy result to accumulator");
  asm("           gosub   s_lset16   ; set integer value for return");
  asm("             dw -2            ; set local variable on stack");

	return i;
}
