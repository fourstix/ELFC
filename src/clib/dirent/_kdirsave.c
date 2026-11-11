#define _ELFCLIB_
#include <stdlib.h>
#include "kdir.h"

/* Save the kernel's directory scan position in a 9 byte state buffer */
void _kdirsave(char *state) {
  asm("         gosub s_lget16  ; get the state argument ");
  asm("           dw 0          ; from argument stack");
  asm("         copy ra, rf     ; copy state buffer pointer");
  _KSAVE
  asm("         call K_DIR_SAVE_STATE ; save the scan position");
  _KRESTORE
}
