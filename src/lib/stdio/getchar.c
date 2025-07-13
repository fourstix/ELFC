#define _ELFCLIB_
#include <stdio.h>

#pragma             extrn Cstdin
#pragma             extrn Cfgetc

int getchar(void) {
  return fgetc(stdin);
}
