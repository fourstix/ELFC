#define _ELFCLIB_
#include <stdlib.h>
#include "edos.h"

#pragma             extrn C_putch

/*
 * Echo a character that was read from the console.  ELF-DOS turns off
 * the echo in the BIOS, so a program has to show what is typed itself.
 * Nothing is shown when either input or output is redirected, so the
 * contents of an input file are not echoed, and an echo is not written
 * into an output file.
 *
 * The kernel points the K_READ and K_TYPE jump table entries at a file
 * routine while a command is redirected, and the words at IO_READ_TARGET
 * and IO_TYPE_TARGET always name the console routines, so the console
 * is in use when they are the same.
 * Returns 1 if the character was shown, 0 if not.
 */
int _conecho(int ch) {
  int live;

  asm("         sex  r2         ; make sure X points to stack");
  asm("         load rf, K_READ+1       ; address in the jump table entry");
  asm("         load rd, IO_READ_TARGET ; address of the console routine");
  asm("         lda  rf         ; compare the hi bytes");
  asm("         str  r2");
  asm("         lda  rd");
  asm("         xor");
  asm("         lbnz ce_no      ; input is redirected");
  asm("         ldn  rf         ; compare the lo bytes");
  asm("         str  r2");
  asm("         ldn  rd");
  asm("         xor");
  asm("         lbnz ce_no      ; input is redirected");
  asm("         load rf, K_TYPE+1       ; address in the jump table entry");
  asm("         load rd, IO_TYPE_TARGET ; address of the console routine");
  asm("         lda  rf         ; compare the hi bytes");
  asm("         str  r2");
  asm("         lda  rd");
  asm("         xor");
  asm("         lbnz ce_no      ; output is redirected");
  asm("         ldn  rf         ; compare the lo bytes");
  asm("         str  r2");
  asm("         ldn  rd");
  asm("         xor");
  asm("         lbnz ce_no      ; output is redirected");
  asm("         load ra, 1      ; the console is in use");
  asm("         lbr  ce_set");
  asm("ce_no:   load ra, 0      ; redirected, so no echo");
  asm("ce_set:  gosub s_lset16  ; set the local variable");
  asm("           dw -2         ; with the result");

  if (live)
    _putch(ch);

  return live;
}
