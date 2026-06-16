#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

#pragma             extrn _atof

/*
 * Convert an Ascii string to a floating point number
 */
float32_t atof(char *s) {
  char r_bytes[4] = {0, 0, 0, 0};

  static float32_t result;

  /* set RF and RD to str pointer and destination pointer */
  asm("            sex     r2           ; make sure x = SP");
  asm("            copy    rb, r8       ; first argument is string pointer");
  asm("            inc     r8           ; set r8 to point to pointer argument");
  asm("            lda     r8           ; get LSB of buffer address");
  asm("            plo     rf           ; set LSB of buffer pointer");
  asm("            ldn     r8           ; get MSB of buffer address");
  asm("            phi     rf           ; rf points to string buffer");

  asm("            copy    rb, rd       ; get address of floating data buffer");
  asm("            dec     rd           ; move pointer down to local data");
  asm("            dec     rd           ; data variables -4 bytes on stack frame");
  asm("            dec     rd           ; rd points to local data variables");
  /* Save Registers Used by ElfC */
  asm("            push    r9           ; save c registers");
  asm("            push    rb           ; save c registers");

  /* call function in library */
  asm("            call    _atof        ; call floating point library routine");
  /* restore ElfC registers */
  asm("            pop     rb           ; restore C registers");
  asm("            pop     r9           ; restore C registers");

  /* assign local variables to static result for return */
  result.high = 0;
  result.low  = 0;
  result.high = (result.high | r_bytes[0]) << 8;
  result.high = result.high | r_bytes[1];
  result.low = (result.low | r_bytes[2]) << 8;
  result.low = result.low | r_bytes[3];

  return result;
}
