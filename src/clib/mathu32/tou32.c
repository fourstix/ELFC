#define _ELFCLIB_
#include <mathu32.h>

uint32_t tou32(unsigned int n)
{
    uint32_t r;
  
    asm("        inc  r7          ; r7 => LSB of result");
    asm("        inc  rb          ; rb => LSB of n");
    asm("        lda  rb");
    asm("        str  r7          ; copy LSB");
    asm("        inc  r7");
    asm("        ldn  rb");
    asm("        str  r7          ; copy byte1");
    asm("        inc  r7");
    asm("        ldi  0");
    asm("        str  r7          ; copy 0 to byte2");
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
