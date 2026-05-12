#define _ELFCLIB_
#include <mathi32.h>

int32_t negi32(int32_t a)
{
    asm("        inc  rb          ; rb => LSB of a");
    asm("        ldn  rb          ; get LSB of a");
    asm("        xri  0ffh        ; invert the bits");
    asm("        adi  1           ; and add 1");
    asm("        str  rb          ; store result");
    asm("        inc  rb          ; move to next byte");
    asm("        ldn  rb          ; get next byte of a");
    asm("        xri  0ffh        ; invert the bits");
    asm("        adci 0           ; and add 1");
    asm("        str  rb          ; store result");
    asm("        inc  rb          ; move to next byte");
    asm("        ldn  rb          ; get next byte of a");
    asm("        xri  0ffh        ; invert the bits");
    asm("        adci 0           ; and add 1");
    asm("        str  rb          ; store result");
    asm("        inc  rb          ; move to next byte");
    asm("        ldn  rb          ; get MSB of a");
    asm("        xri  0ffh        ; invert the bits");
    asm("        adci 0           ; and add 1");
    asm("        str  rb          ; store result");
    asm("        dec  rb          ; restore rb");
    asm("        dec  rb          ; restore rb");
    asm("        dec  rb          ; restore rb");
    asm("        dec  rb          ; restore rb");
  
    return a;
}
