#define _ELFCLIB_
#include <stdlib.h>
#include "edos.h"

int _putch(int ch) {
  asm("         gosub s_lget16    ; get character to send");
  asm("           dw  0           ; from for arg 1 ");
  _KSAVE
  asm("         glo  ra           ; ra holds character to send");
  asm("         call K_TYPE       ; send character to the terminal");
  _KRESTORE
  return ch;
}
