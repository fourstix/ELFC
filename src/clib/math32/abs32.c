#define _ELFCLIB_
#include <math32.h>

#pragma             extrn Cneg32

int32_t abs32(int32_t *n) {
  return (n->high & 0x8000) ? neg32(n) : *n;
}
