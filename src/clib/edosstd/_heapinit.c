#define _ELFCLIB_
#include <stdlib.h>
#include "edos.h"

#pragma             extrn heap_init

/* the sdk keeps its data in a separate procedure, which the linker */
/* only takes from a library when it is named as required */
#pragma           .link .requires _heap_malloc_data

/*
 *  ELF-DOS has no kernel memory allocator, so the heap is kept by the
 *  heap_malloc module of the ELF-DOS SDK, which is part of this library.
 *  The kernel loader publishes the memory a program may use as two
 *  words at LOADER_ARGS: mem_base, the first byte after the program,
 *  and mem_top, the last usable byte.
 *
 *  Heap Block Layout
 * --------------------------------
 *  Byte : Description       : Length
 * --------------------------------
 *   0-1 : Size of data      :  2
 *   2-3 : Next free block   :  2   (free blocks only)
 * --------------------------------
 *  The pointer returned by malloc is the address of byte 2.
 */

int _hinit = 0;

void _heapinit(void) {
  asm("         load rf, LOADER_ARGS    ; point to loader memory values");
  asm("         lda  rf         ; get the mem_base hi byte (MSB)");
  asm("         phi  rd         ; rd holds the heap base");
  asm("         lda  rf         ; get the mem_base lo byte (LSB)");
  asm("         plo  rd");
  asm("         lda  rf         ; get the mem_top hi byte (MSB)");
  asm("         phi  ra");
  asm("         ldn  rf         ; get the mem_top lo byte (LSB)");
  asm("         plo  ra");
  asm("         copy ra, rf     ; rf holds the heap top");
  _KSAVE
  asm("         call heap_init  ; make the heap one free block");
  _KRESTORE

  _hinit = 1;
}
