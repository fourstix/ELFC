#define _ELFCLIB_
#include <stdlib.h>
#include "edos.h"

#pragma             extrn C_conin
#pragma             extrn C_conecho

int _getch(void) {
  int ch;

  ch = _conin();

  /* ELF-DOS does not echo input, so show the character read */
  if (ch != 0)
    _conecho(ch);

  return ch;
}
