#define _ELFCLIB_
#include <ctype.h>

#pragma           extrn Cislower

int toupper(int c) {
  return (islower(c) ?  (c & 0x5f) : c);
}
