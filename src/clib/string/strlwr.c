#define _ELFCLIB_
#include <string.h>
#include <ctype.h>

#pragma           extrn Ctolower

char * strlwr(char *str) {
  char *p = str;

  while (*p) {
     *p = tolower(*p);
      p++;
  }

  return str;
}
