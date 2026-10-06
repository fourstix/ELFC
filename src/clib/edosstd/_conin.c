#define _ELFCLIB_
#include <stdlib.h>
#include "edos.h"

/*
 * Read a character from the console without echoing it.  The kernel
 * reads from a file instead when input is redirected, and returns 0
 * once the end of that file is reached.
 */
int _conin(void) {
  int ch;

  _KSAVE
  asm("         call K_READ         ; read a character from input");
  asm("         plo  rc             ; hold character while restoring");
  _KRESTORE
  asm("         glo  rc             ; get the character read");
  asm("         plo  ra             ; save in return register");
  asm("         ldi  0              ; pad register with zero");
  asm("         phi  ra              ");
  asm("         gosub s_lset16      ; set the local variable");
  asm("           dw -2             ; with the return value");

  return ch;
}
