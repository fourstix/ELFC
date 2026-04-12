#define _ELFCLIB_
#include <ctype.h>


int isprint(int c) {
  /* casting to unsigned turns negatives into large postives */
  return ((unsigned)(c - 0x20) < 0x5f);
}
