#define _ELFCLIB_
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* define only extern procedures required */
#pragma           extrn Cfprintf
#pragma           extrn Cabort
#pragma           extrn Cstderr  

void assert(int a, char *file, int line) {
/* if NDEBUG is defined don't assemble code */
  asm("#ifndef NDEBUG\n");
  if (!a) {
    fprintf(stderr, "Assertion failed: File %s Line %d\n", file, line);
    abort();
  }
  asm("#endif\n");
 
  return;
}
