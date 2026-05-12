#define _ELFCLIB_
#include <mathi32.h>

int32_t shli32(int32_t a, int n)
{
    asm("        glo  rb          ;");
    asm("        adi  5           ;");
    asm("        plo  ra          ;");
    asm("        ghi  rb          ;");
    asm("        adci 0           ;");
    asm("        phi  ra          ; ra => LSB of n");
    asm("        lda  ra          ;");
    asm("        plo  rc          ; copy n to rc");
    asm("        ldn  ra          ;");
    asm("        phi  rc          ;");
    asm("        dec  ra          ;");
    asm("        dec  ra          ; ra => MSB of a");
    asm("shl_test:                ;");
    asm("        ghi  rc          ; exit loop when rc = 0");
    asm("        lbnz shl_loop    ;");
    asm("        glo  rc          ;");
    asm("        lbz  shl_done    ;");
    asm("shl_loop:                ;");
    asm("        dec  ra          ;");
    asm("        dec  ra          ;");
    asm("        dec  ra          ; ra => LSB of a");
    asm("        ldn  ra          ; shift a left 1 bit");
    asm("        shl              ;");
    asm("        str  ra          ;");
    asm("        inc  ra          ;");
    asm("        ldn  ra          ;");
    asm("        shlc             ;");
    asm("        str  ra          ;");
    asm("        inc  ra          ;");
    asm("        ldn  ra          ;");
    asm("        shlc             ;");
    asm("        str  ra          ;");
    asm("        inc  ra          ;");
    asm("        ldn  ra          ;");
    asm("        shlc             ;");
    asm("        str  ra          ;");
    asm("        dec  rc          ;");
    asm("        lbr  shl_test    ;");
    asm("shl_done:                ;");

    return a;
}
