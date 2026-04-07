#define _ELFCLIB_
#include <ctype.h>


int isspace(int c) {
  /* casting to unsigned turns negatives into large postives */
  return (c == ' ' || ((unsigned)(c - '\t') < 5));
  }
