#define _ELFCLIB_
#include <ctype.h>

#pragma           extrn Cisdigit

int isxdigit(int c) {
  /* casting to unsigned turns negatives into large postives */
  return (isdigit(c) || ((unsigned)((c|32) - 'a') < 6));
}
