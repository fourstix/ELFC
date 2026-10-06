#define _ELFCLIB_
#include <stdlib.h>
#include "edos.h"

#pragma             extrn C_hinit
#pragma             extrn C_heapinit
#pragma             extrn heap_alloc

/* the sdk keeps its data in a separate procedure, which the linker */
/* only takes from a library when it is named as required */
#pragma           .link .requires _heap_malloc_data

void* malloc(size_t size) {
  void *p;

  /* set up the heap the first time it is used */
  if (!_hinit)
    _heapinit();

  asm("         gosub s_lget16  ; set the size value to allocate");
  asm("           dw 0          ; get size from argument stack");
  asm("         copy ra, rc     ; set size for heap function");
  _KSAVE
  asm("         call heap_alloc ; call sdk alloc function");
  _KRESTORE
  asm("         copy rf, ra     ; pointer is NULL if not allocated");
  asm("         gosub s_lset16  ; set pointer value for return");
  asm("           dw -2         ; set local variable on stack");
  return p;
}
