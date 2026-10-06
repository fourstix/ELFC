#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>
#include "edos.h"

#pragma             extrn Cerrno
#pragma             extrn C_fildes

int write(int fd, void *buf, size_t n) {
  int fildes;
  int n_write;

  /* get system file descriptor */
  fildes = _fildes(fd);

  /* if fildes is invalid, return with error */
  if (fildes == EOF) {
    errno = EBADF;
    return EOF;
   }

  asm("         gosub s_lget16  ; get the fildes variable ");
  asm("           dw -2         ; from the local variable stack");
  asm("         copy ra, rd     ; copy fd pointer to fcb pointer");
  asm("         gosub s_lget16  ; get the buffer argument ");
  asm("           dw 2          ; get from argument stack");
  asm("         copy ra, rf     ; copy argument pointer to buffer pointer");
  asm("         gosub s_lget16  ; get the byte count argument ");
  asm("           dw 4          ; get from argument stack");
  asm("         copy ra, rc     ; copy argument value to counter");
  _KSAVE
  asm("         call K_FILE_WRITE ; attempt to write the data");
  _KRESTORE
  asm("         lbdf wr_err     ; DF = 1, means failure");
  asm("         gosub s_lget16  ; the kernel returns no count for a write");
  asm("           dw 4          ; so on success use the count requested");
  asm("         lbr  wr_ok      ; and set as return value");
  asm("wr_err:  ldi  $Ff        ; otherwise set count for error");
  asm("         phi  ra         ; set count to -1 ");
  asm("         plo  ra         ; set result in ra ");
  asm("wr_ok:   gosub s_lset16  ; set the local variable to the count ");
  asm("           dw -4         ; on the argument stack");

  if (n_write == EOF) {
    errno = EIO;
  }

  return n_write;
}
