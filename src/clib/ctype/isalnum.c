#define _ELFCLIB_
#include <ctype.h>

#pragma           extrn Cisalpha
#pragma           extrn Cisdigit

int isalnum(int c) {
  return (isalpha(c) || isdigit(c));
}
