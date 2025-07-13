#define _ELFCLIB_
#include <stdio.h>

#pragma             extrn Cstdout
#pragma             extrn Cfputc

extern FILE	*stdout;

int putchar(int c) {
  return fputc(c, stdout);
}
