#define _ELFCLIB_
#include <ctype.h>

int isgraph(int c) {
  /* casting to unsigned turns negatives into large postives */
  return ((unsigned)(c - 0x21) < 0x5e);
  }
