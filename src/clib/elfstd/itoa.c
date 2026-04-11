#define _ELFCLIB_
#include <stdlib.h>

#pragma             extrn Citou

void itoa(int n, char *s) {
  if (s == NULL) return;

  /* if negative, print sign and convert absolute value */
  if (n < 0) {
    n = -n;
    *s++ = '-';
  }
  itou(n, s);
  return;
}
