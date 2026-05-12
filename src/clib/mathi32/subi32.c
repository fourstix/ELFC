#define _ELFCLIB_
#include <mathi32.h>

int32_t subi32(int32_t a, int32_t b)
{
    asm("        inc  rb          ; rb => LSB of a");
    asm("        copy rb, ra      ;");
    asm("        inc  ra          ;");
    asm("        inc  ra          ;");
    asm("        inc  ra          ;");
    asm("        inc  ra          ; ra => LSB of b");
    asm("        sex  ra          ; r(x) => LSB of b");
    asm("        lda  rb          ; get LSB of a");
    asm("        sm               ; sub LSB of b");
    asm("        str  ra          ; store result in LSB of b");
    asm("        inc  ra          ; move to next byte of b");
    asm("        lda  rb          ; get next byte of a");
    asm("        smb              ; sub next byte of b");
    asm("        str  ra          ; store next byte of b");
    asm("        inc  ra          ; move to next byte of b");
    asm("        lda  rb          ; get next byte of a");
    asm("        smb              ; sub next byte of b");
    asm("        str  ra          ; store next byte in b");
    asm("        inc  ra          ; move to next byte of b");
    asm("        ldn  rb          ; get MSB of a");
    asm("        smb              ; sub MSB");
    asm("        str  ra          ; store MSB");
    asm("        dec  rb          ; restore rb");
    asm("        dec  rb          ; restore rb");
    asm("        dec  rb          ; restore rb");
    asm("        dec  rb          ; restore rb");
  
    return b;
}
