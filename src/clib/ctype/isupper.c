#define _ELFCLIB_
#include <ctype.h>


int isupper(int c) {
  /* casting to unsigned turns negatives into large postives */
  return ((unsigned)(c -'A') < 26);
}
