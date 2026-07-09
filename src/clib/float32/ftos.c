#define _ELFCLIB_
#include <float32.h>

#pragma             extrn _ftos

/*
 * Convert a floating point number into an ASCII string
 */
void ftos(float32_t fp1, char *s) {
  if (NULL == s)
    return;

  /* Process NaN */
  if (isNaN(fp1)) {
    /* write "NaN" to buffer */
    s[0] = 'N';
    s[1] = 'a';
    s[2] = 'N';
    s[3] = '\0';
    return;
  } else if (isInf(fp1)) {
    /* set sign of infinity */
    if (isNeg(fp1)) {
      s[0] = '-';
    } else {
      s[0] = '+';
    }
    s[1] = 'I';
    s[2] = 'n';
    s[3] = 'f';
    s[4] = 0;
    return;
  }

  asm("            copy    rb, rf       ; first argument is float value");
  asm("            inc     rf           ; set rf to point to float value");
  asm("            copy    rf, r8       ; second argument is buffer pointer");
  asm("            inc     r8           ; buffer argument +4 bytes into stack frame");
  asm("            inc     r8");
  asm("            inc     r8");
  asm("            inc     r8           ; copy buffer pointer into rd");
  asm("            lda     r8           ; get low byte of char pointer ");
  asm("            plo     rd           ; set rd to point to output buffer");
  asm("            ldn     r8           ; get high byte of char pointer ");
  asm("            phi     rd           ; rd now points to output buffer");

  /* Save Registers Used by ElfC */
  asm("            sex     r2           ; make sure x = SP");
  asm("            push    r9           ; save c registers");
  asm("            push    rb           ; save c registers");

  /* call function in library */
  asm("            call    _ftos        ; call function in library");
  /* restore ElfC registers */
  asm("            pop     rb           ; restore C registers");
  asm("            pop     r9           ; restore C registers");
  return;
}
