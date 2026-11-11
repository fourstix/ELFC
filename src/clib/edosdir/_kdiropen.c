#define _ELFCLIB_
#include <stdlib.h>
#include "kdir.h"

/*
 * Start the kernel's directory scan at the beginning of the directory
 * that starts at clust (0 for the root) on the selected drive.
 */
void _kdiropen(unsigned int clust) {
  asm("         gosub s_lget16  ; get the cluster argument ");
  asm("           dw 0          ; from argument stack");
  asm("         copy ra, rd     ; copy cluster to rd");
  _KSAVE
  asm("         call K_DIR_OPEN ; start the directory scan");
  _KRESTORE
}
