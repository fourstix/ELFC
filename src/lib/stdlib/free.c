#define _ELFCLIB_
#include <stdlib.h>


void free(void* p) {
  if (p == NULL) return;
  asm("         call lget16     ; set the pointer value to free");
  asm("           dw 0          ; from argument stack");             
  asm("         copy ra, rf     ; put pointer into rf"); 
  asm("         call o_dealloc  ; call kernel dealloc function");
  return;
}
