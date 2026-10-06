#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>
#include <math32.h>
#include "edos.h"

#pragma             extrn Cerrno
#pragma             extrn C_fildes
#pragma             extrn Ci32_from_int
#pragma             extrn Ccmpi32
#pragma .link .library math32.lib

off_t lseek32(int fd, off_t offset, int how) {
  int fildes;
  off_t result;
  off_t eof;

  eof = i32_from_int(EOF);

  /* get system file descriptor */
  fildes = _fildes(fd);

  /* don't seek invalid fd */
  if(fildes == EOF) {
    errno = EBADF;
    return eof;
  }
  asm("         gosub s_lget16  ; get the fildes variable ");
  asm("           dw -2         ; from local variable stack");
  asm("         copy ra, rd     ; copy fd to fcb register");
  asm("         gosub s_lget16  ; get the how to seek argument ");
  asm("           dw 6          ; from argument stack");
  asm("         copy ra, rc     ; copy how to seek value to register");
  asm("         copy rb, rf     ; get pointer to stack frame into rf");
  asm("         inc  rf         ; adjust pointer");
  asm("         inc  rf         ; to point to the offset");
  asm("         inc  rf         ; on the stack");
  _KSAVE
  asm("         lda  rf         ; get low byte of low offset");
  asm("         plo  r9         ; save in r9.0");
  asm("         lda  rf         ; get high byte of low offset");
  asm("         phi  r9         ; save in r9.1");
  asm("         lda  rf         ; get low byte of high offset");
  asm("         plo  ra         ; save in ra.0");
  asm("         ldn  rf         ; get high byte of high offset");
  asm("         phi  ra         ; save in ra.1");
  asm("         call K_FILE_SEEK ; attempt to seek within file");
  _KRESTORE
  asm("         copy ra, rc     ; save high final offset");
  asm("         copy rd, ra     ; get the low final offset");
  asm("         lbdf lsk_err    ; DF = 1, means failure");
  asm("         gosub s_lset16  ; save low offset result");
  asm("           dw -6         ; in the local variabe");
  asm("         copy rc, ra     ; get the high offset");
  asm("         lbr  lsk_ex     ; continue with function");
  asm("lsk_err: ldi  $ff        ; set failure value");
  asm("         phi  ra         ; output offset = -1");
  asm("         plo  ra         ; on failure");
  asm("         gosub s_lset16  ; save low offset result");
  asm("           dw -6         ; in the local variabe");
  asm("lsk_ex:  gosub s_lset16  ; save high offset result ");
  asm("           dw -4         ; in the local variable");

  /* if error, set errno */
  if (cmpi32(result, eof) == 0) {
    errno = EIO;
  }

  return result;
}
