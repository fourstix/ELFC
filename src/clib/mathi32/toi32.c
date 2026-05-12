#define _ELFCLIB_
#include <mathi32.h>

int32_t toi32(int n)
{
    int32_t r;
  
    asm("        inc  r7          ; r7 => LSB of result");
    asm("        inc  rb          ; rb => LSB of n");
    asm("        ldi  00");
    asm("        plo  rc          ; init rc.0 = 0");
    asm("        lda  rb");
    asm("        str  r7          ; copy LSB");
    asm("        inc  r7");
    asm("        ldn  rb");
    asm("        str  r7          ; copy byte1");
    asm("        inc  r7");
    asm("        ani  $80");
    asm("        lsz              ; skip if n is not negative");
    asm("        dec  rc          ; rc = 0xff");
    asm("        nop");
    asm("        glo  rc");
    asm("        str  r7          ; copy sign extension to byte2");
    asm("        inc  r7");
    asm("        str  r7          ; and byte3");
    asm("        dec  r7");
    asm("        dec  r7");
    asm("        dec  r7");
    asm("        dec  r7          ; restore r7");
    asm("        dec  rb");
    asm("        dec  rb          ; restore rb");
  
    return r;
}
