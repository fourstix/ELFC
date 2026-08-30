#define _ELFCLIB_
#include <stdio.h>

#pragma             extrn C_putstr
#pragma             extrn C_putch


int puts(const char* s) {
  _putstr(s);
  _putch('\n');
  return 1;
}
