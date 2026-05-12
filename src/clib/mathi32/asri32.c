#define _ELFCLIB_
#include <mathi32.h>

int32_t asri32(int32_t a, int n)
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
    asm("asr_test:                ;");
    asm("        ghi  rc          ; exit loop when rc = 0");
    asm("        lbnz asr_loop    ;");
    asm("        glo  rc          ;");
    asm("        lbz  asr_done    ;");
    asm("asr_loop:                ;");
    asm("        ldn  ra          ; artihmetic shift a right 1 bit");
    asm("        shl              ; sign bit => DF");
    asm("        ldn  ra          ;");
    asm("        shrc             ;");
    asm("        str  ra          ;");
    asm("        dec  ra          ;");
    asm("        ldn  ra          ;");
    asm("        shrc             ;");
    asm("        str  ra          ;");
    asm("        dec  ra          ;");
    asm("        ldn  ra          ;");
    asm("        shrc             ;");
    asm("        str  ra          ;");
    asm("        dec  ra          ;");
    asm("        ldn  ra          ;");
    asm("        shrc             ;");
    asm("        str  ra          ;");
    asm("        inc  ra          ;");
    asm("        inc  ra          ;");
    asm("        inc  ra          ; ra => MSB of a");
    asm("        dec  rc          ;");
    asm("        lbr  asr_test    ;");
    asm("asr_done:                ;");

    return a;
}
