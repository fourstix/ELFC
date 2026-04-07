#define _ELFCLIB_
#include <ctype.h>


int isdigit(int c) {
  /* casting to unsigned turns negatives into large postives */
  return ((unsigned)(c -'0') < 10);
}
