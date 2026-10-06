#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>
#include "edos.h"

#pragma             extrn Cerrno
#pragma             extrn C_fdtable
#pragma             extrn C_fildes
#pragma             extrn Cfree

int	close(int fd) {
  int fildes;
  int result;

  /* get system file descriptor */
  fildes = _fildes(fd);

  if (fildes == EOF) {
    return EOF;
  }

  asm("         gosub s_lget16  ; get the fildes variable ");
  asm("           dw -2         ; get from local stack");
  asm("         copy ra, rd     ; copy fd pointer to fcb pointer");
  _KSAVE
  asm("         call K_FILE_CLOSE ; attempt to close the file");
  _KRESTORE
  _KRESULT
  asm("         gosub s_lset16  ; set the result value ");
  asm("           dw -4         ; in the local variable on the stack");

  /* if close failed, set errno */
  if (result == EOF) {
    errno = EIO;
  }

  /* update table to free handle */
  _fdtable[fd] = EOF;

  /* release the file descriptor */
  free((void *) _FCB_BLOCK(fildes));

  return result;
}
