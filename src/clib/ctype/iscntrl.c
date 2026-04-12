#define _ELFCLIB_
#include <ctype.h>


int iscntrl(int c) {
  /* casting to unsigned turns negatives into large postives */
  return ((unsigned)c < 0x20 || c == 0x7f);
}
