#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>
#include "edos.h"

#pragma             extrn Cerrno

int	unlink(char* path) {
  int result;

  /* don't delete invalid path */
  if(path == NULL) {
    errno = EINVAL;
    return EOF;
  }

  asm("         gosub s_lget16  ; get the path argument ");
  asm("           dw 0          ; get from argument stack");
  asm("         copy ra, rf     ; copy path string to buffer pointer");
  _KSAVE
  asm("         call K_FILE_DELETE ; attempt to delete the file");
  _KRESTORE
  _KRESULT
  asm("         gosub s_lset16  ; set the fd argument ");
  asm("           dw -2         ; in the local variable on the stack");

  /* if error, set errno */
  if (result == EOF)
    errno = EIO;

  return result;
}
