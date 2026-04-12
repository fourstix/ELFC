#define _ELFCLIB_
#include <ctype.h>

#pragma           extrn Cisgraph
#pragma           extrn Cisalnum


int ispunct(int c) {
  return(isgraph(c) && !isalnum(c));
}
