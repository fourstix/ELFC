#define _ELFCLIB_
#include <string.h>
#include <ctype.h>

#pragma           extrn Ctoupper

char * strupr(char *str) {
  char *p = str;

  while (*p) {
     *p = toupper(*p);
      p++;
  }

  return str;
}
