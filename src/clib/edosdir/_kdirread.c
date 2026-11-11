#define _ELFCLIB_
#include <stdlib.h>
#include "kdir.h"

/*
 * Read the next entry of the kernel's directory scan into buf, which
 * holds the kernel's 139 byte directory entry.  Returns 0, or -1 at
 * the end of the directory or on a disk error.
 *
 * The SDK guide says K_DIR_READ takes the buffer in RD, but the kernel
 * and the SDK's own file_glob take it in RF.
 */
int _kdirread(char *buf) {
  int result;

  asm("         gosub s_lget16  ; get the buf argument ");
  asm("           dw 0          ; from argument stack");
  asm("         copy ra, rf     ; copy buffer to result pointer");
  _KSAVE
  asm("         call K_DIR_READ ; read the next entry");
  _KRESTORE
  _KRESULT
  asm("         gosub s_lset16  ; set the result variable ");
  asm("           dw -2         ; in the local variable on the stack");

  return result;
}
