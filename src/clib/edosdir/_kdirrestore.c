#define _ELFCLIB_
#include <stdlib.h>
#include "kdir.h"

/*
 * Restore a directory scan position saved by _kdirsave, on the drive
 * that is selected.  Returns 0, or -1 if the disk could not be read.
 */
int _kdirrestore(char *state) {
  int result;

  asm("         gosub s_lget16  ; get the state argument ");
  asm("           dw 0          ; from argument stack");
  asm("         copy ra, rf     ; copy state buffer pointer");
  _KSAVE
  asm("         call K_DIR_RESTORE_STATE ; restore the scan position");
  _KRESTORE
  _KRESULT
  asm("         gosub s_lset16  ; set the result variable ");
  asm("           dw -2         ; in the local variable on the stack");

  return result;
}
