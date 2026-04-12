#define _ELFCLIB_
#include <string.h>
#include <ctype.h>

#pragma             extrn Ctoupper

#pragma .link .library ctype.lib

char * strupr(char *str) {
  char *p = str;

  while (*p) {
     *p = toupper(*p);
      p++;
  }

  return str;
}
