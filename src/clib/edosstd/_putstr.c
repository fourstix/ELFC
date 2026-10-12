#define _ELFCLIB_
#include <stdlib.h>
#include "edos.h"

int _putstr(const char* s) {
  if (s == NULL) return EOF;

  asm("         gosub s_lget16    ; put buffer pointer variable");
  asm("           dw  0           ; offset for arg 1 ");
  asm("         copy  ra, rf      ; ra holds result of assigning pointer");
  _KSAVE
  asm("         call K_MSG        ; output string to elf-dos");
  _KRESTORE

  return 1;
}
