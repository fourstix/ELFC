#define _ELFCLIB_
#include <ctype.h>

#pragma           extrn Cisupper

int tolower(int c) {
  return (isupper(c) ?  (c | 32) : c);
}
