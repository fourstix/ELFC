#define _ELFCLIB_
#include <stdlib.h>
#include "kdir.h"

/*
 * Resolve a path with K_PATH_RESOLVE.  On success it sets the cluster
 * of the parent directory, a pointer to the final path component (in
 * kernel memory, valid until the next resolve) and the drive index,
 * 0 to 3 for C: to F:, and returns 0.  Returns -1 when a directory in
 * the path is not found or the drive is not mounted.
 *
 * Resolving a path also makes its drive the one the kernel's
 * directory scan uses, without changing the active drive.
 */
int _kpathres(char *path, unsigned int *clust, char **name, int *drive) {
  int result;
  unsigned int c;
  char *n;
  int d;

  asm("         gosub s_lget16  ; get the path argument ");
  asm("           dw 0          ; from argument stack");
  asm("         copy ra, rf     ; copy path string to buffer pointer");
  _KSAVE
  asm("         call K_PATH_RESOLVE ; resolve the path");
  _KRESTORE
  _KRESULT
  asm("         gosub s_lset16  ; set the result variable ");
  asm("           dw -2         ; in the local variable on the stack");
  asm("         copy rd, ra     ; parent directory cluster");
  asm("         gosub s_lset16  ; set the cluster variable ");
  asm("           dw -4         ; in the local variable on the stack");
  asm("         copy rf, ra     ; final path component");
  asm("         gosub s_lset16  ; set the name variable ");
  asm("           dw -6         ; in the local variable on the stack");
  asm("         copy rc, ra     ; drive index in rc.0");
  asm("         gosub s_lset16  ; set the drive variable ");
  asm("           dw -8         ; in the local variable on the stack");

  if (result != EOF) {
    *clust = c;
    *name = n;
    *drive = d & 0xFF;
  }

  return result;
}
