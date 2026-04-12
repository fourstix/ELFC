#define _ELFCLIB_
#include <string.h>
#include <ctype.h>

#pragma             extrn Ctolower

#pragma .link .library ctype.lib

char * strlwr(char *str) {
  char *p = str;

  while (*p) {
     *p = tolower(*p);
      p++;
  }

  return str;
}
