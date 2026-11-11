#define _ELFCLIB_
#include <stdlib.h>
#include "odir.h"

/*
 * Count the allocation units after lump in its chain, with O_RDLUMP
 * ($032A, called by address since older os_api.inc files lack it).
 * drive is the device select byte for Mini/DOS, which takes it in
 * R8.1; Elf/OS ignores it.  The chain ends at $FEFE.  A free ($0000)
 * entry also stops the count, so a damaged chain cannot loop.
 */
unsigned int _olumps(unsigned int lump, int drive) {
  unsigned int next;
  unsigned int hops;

  for (hops = 0; hops != 0xFFFF; hops++) {
    asm("         gosub s_lget16  ; get the lump argument ");
    asm("           dw 0          ; from argument stack");
    asm("         copy ra, rc     ; set lump aside");
    asm("         gosub s_lget16  ; get the drive argument ");
    asm("           dw 2          ; from argument stack");
    asm("         glo  ra         ; drive select byte");
    asm("         phi  r8         ; into r8.1 for Mini/DOS");
    asm("         copy rc, ra     ; lump to read");
    asm("         push r7         ; save ESP");
    asm("         push r9         ; save subroutine pointer");
    asm("         push rb         ; save stack frame base pointer");
    asm("         call 032Ah      ; O_RDLUMP, read the next lump");
    asm("         pop  rb         ; restore stack frame base pointer");
    asm("         pop  r9         ; restore subroutine pointer");
    asm("         pop  r7         ; restore ESP");
    asm("         gosub s_lset16  ; set the next variable ");
    asm("           dw -2         ; in the local variable on the stack");
    if (next == 0xFEFE || next == 0)
      break;
    lump = next;
  }

  return hops;
}
