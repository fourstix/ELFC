#define _ELFCLIB_
#include <stdlib.h>

int atoi(char *s) {
  int i;
  
  if (s == NULL) return 0;
  
  asm("         call lget16     ; get the buffer pointer for string");
  asm("           dw 0          ; get pointer from argument stack");           
  asm("         copy ra, rf     ; copy pointer for function call");
  asm("         call atoi16     ; call elf atoi function");
  asm("         copy rc, ra     ; copy result to accumulator");
  asm("         call lset16     ; set integer value for return");
  asm("           dw -2         ; set local variable on stack");           

	return i;
}
