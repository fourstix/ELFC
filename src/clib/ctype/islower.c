#define _ELFCLIB_
#include <ctype.h>


int islower(int c) {
  /* casting to unsigned turns negatives into large postives */
  return ((unsigned)(c -'a') < 26);
}
