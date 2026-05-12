#define _ELFCLIB_
#include <mathi32.h>

int32_t absi32(int32_t a)
{
    asm("        copy rb, ra      ;");
    asm("        inc  ra          ;");
    asm("        inc  ra          ;");
    asm("        inc  ra          ;");
    asm("        inc  ra          ; ra => MSB of a");
    asm("        ldn  ra          ;");
    asm("        ani  $80         ; check sign");
    asm("        lbz  abs_done    ; no change if positive");
    asm("        dec  ra          ;");
    asm("        dec  ra          ;");
    asm("        dec  ra          ; ra => LSB of a");
    asm("        ldn  ra          ; negate in place");
    asm("        xri  $ff         ;");
    asm("        adi  1           ;");
    asm("        str  ra          ;");
    asm("        inc  ra          ;");
    asm("        ldn  ra          ; negate in place");
    asm("        xri  $ff         ;");
    asm("        adci 0           ;");
    asm("        str  ra          ;");
    asm("        inc  ra          ;");
    asm("        ldn  ra          ; negate in place");
    asm("        xri  $ff         ;");
    asm("        adci 0           ;");
    asm("        str  ra          ;");
    asm("        inc  ra          ;");
    asm("        ldn  ra          ; negate in place");
    asm("        xri  $ff         ;");
    asm("        adci 0           ;");
    asm("        str  ra          ;");
    asm("abs_done:                ;");
    
    return a;
}
