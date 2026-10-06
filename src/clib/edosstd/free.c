#define _ELFCLIB_
#include <stdlib.h>
#include "edos.h"

#pragma             extrn heap_free

/* the sdk keeps its data in a separate procedure, which the linker */
/* only takes from a library when it is named as required */
#pragma           .link .requires _heap_malloc_data

void free(void* p) {
  if (p == NULL) return;
  asm("         gosub s_lget16  ; set the pointer value to free");
  asm("           dw 0          ; from argument stack");
  asm("         copy ra, rf     ; put pointer into rf");
  _KSAVE
  asm("         call heap_free  ; call sdk free function");
  _KRESTORE
  return;
}
