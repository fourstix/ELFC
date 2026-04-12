#define _ELFCLIB_
#include <ctype.h>


int isalpha(int c) {
  /* casting to unsigned turns negatives into large postives */
  return ((unsigned)((c|32) - 'a') < 26);
}
