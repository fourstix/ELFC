#define _ELFCLIB_
#include <stdlib.h>
#include "kdir.h"

/*
 * Look up a file or directory with K_STAT, filling buf with the
 * kernel's 139 byte directory entry.  Returns 0, or -1 if not found.
 */
int _kstat(char *path, char *buf) {
  int result;

  asm("         gosub s_lget16  ; get the buf argument ");
  asm("           dw 2          ; from argument stack");
  asm("         copy ra, rd     ; copy buffer to entry pointer");
  asm("         gosub s_lget16  ; get the path argument ");
  asm("           dw 0          ; from argument stack");
  asm("         copy ra, rf     ; copy path string to buffer pointer");
  _KSAVE
  asm("         call K_STAT     ; look up the path");
  _KRESTORE
  _KRESULT
  asm("         gosub s_lset16  ; set the result variable ");
  asm("           dw -2         ; in the local variable on the stack");

  return result;
}
