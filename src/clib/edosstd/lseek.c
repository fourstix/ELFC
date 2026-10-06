#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>
#include "edos.h"

#pragma             extrn Cerrno
#pragma             extrn C_fildes

int  lseek(int fd, int offset, int whence) {
  int fildes;
  int result;

  /* get system file descriptor */
  fildes = _fildes(fd);

  /* don't seek invalid fd */
  if (fildes == EOF) {
    errno = EBADF;
    return EOF;
  }

  asm("         gosub s_lget16  ; get the fildes variable ");
  asm("           dw -2         ; from local variable stack");
  asm("         copy ra, rd     ; copy fd to fcb register");
  asm("         gosub s_lget16  ; get the how to seek argument ");
  asm("           dw 4          ; from argument stack");
  asm("         copy ra, rc     ; copy how to seek value to register");
  asm("         gosub s_lget16  ; get the low offset value");
  asm("           dw 2          ; from the argument stack");
  _KSAVE
  asm("         copy ra, r9     ; copy to low offset register");
  asm("         ldi  0          ; sign extend low offset register");
  asm("         plo  ra         ; into high offset register");
  asm("         phi  ra         ; initialize ra to 0");
  asm("         ghi  r9         ; get high byte of low offset");
  asm("         shl             ; move sign bit to df");
  asm("         lbnf lsk_pos    ; jump if sign bit is zero (positive)");
  asm("         dec  ra         ; ra = ffff if sign bit is one (negative)");
  asm("lsk_pos: call K_FILE_SEEK ; attempt to seek within file");
  _KRESTORE
  asm("         copy rd, ra     ; save low offset return value");
  asm("         lbnf lsk_ok     ; DF = 0, means success");
  asm("         ldi  $ff        ; load -1");
  asm("         phi  ra         ; set result to -1");
  asm("         plo  ra         ; on error");
  asm("lsk_ok:  gosub s_lset16  ; set the result ");
  asm("           dw -4         ; in the local variable");

  /* if error, set errno */
  if (result == -1)
    errno = EIO;

  return result;
}
