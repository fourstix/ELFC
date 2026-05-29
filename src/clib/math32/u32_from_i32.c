#define _ELFCLIB_
#include <math32.h>

uint32_t u32_from_i32(int32_t n)
{
    uint32_t r;
  
    asm("        inc  r7          ; r7 => LSB of result");
    asm("        inc  rb          ; rb => LSB of n");
    asm("        lda  rb");
    asm("        str  r7          ; copy LSB");
    asm("        inc  r7");
    asm("        lda  rb");
    asm("        str  r7          ; copy byte 1");
    asm("        inc  r7");
    asm("        lda  rb");
    asm("        str  r7          ; copy byte 2");
    asm("        inc  r7");
    asm("        ldn  rb");
    asm("        str  r7          ; copy byte MSB");
    asm("        dec  r7");
    asm("        dec  r7");
    asm("        dec  r7");
    asm("        dec  r7          ; restore r7");
    asm("        dec  rb");
    asm("        dec  rb");
    asm("        dec  rb");
    asm("        dec  rb          ; restore rb");
  
    return r;
}
