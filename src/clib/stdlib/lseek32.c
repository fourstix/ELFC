#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>
#include <math32.h>

#pragma             extrn Cerrno
#pragma             extrn C_fildes
#pragma             extrn Cto_int32
#pragma             extrn Ccmp32
#pragma .link .library math32.lib

off_t lseek32(int fd, off_t *offset, int how) {
  int fildes;
  off_t result;
  off_t eof;

  eof = to_int32(EOF);

  /* get system file descriptor */
  fildes = _fildes(fd);

  /* don't seek invalid fd */
  if(fildes == EOF) {
    errno = EBADF;
    return eof;
  }

  asm("         gosub s_lget16  ; get the fildes variable ");
  asm("           dw -2         ; from local variable stack");
  asm("         copy ra, rd     ; copy fd to fildes register");
  asm("         gosub s_lget16  ; get the how to seek argument ");
  asm("           dw 4          ; from argument stack");
  asm("         copy ra, rc     ; copy how to seek value to register");
  asm("         gosub s_lget16  ; get the pointer to the offset");
  asm("           dw 2          ; from argument stack");
  asm("         push r7         ; save stack pointer before setting low offset");
  asm("         lda  ra         ; get low byte of low offset");
  asm("         plo  r7         ; save in r7.0");
  asm("         lda  ra         ; get high byte of low offset");
  asm("         phi  r7         ; save in r7.1");
  asm("         lda  ra         ; get low byte of high offset");
  asm("         plo  r8         ; save in r8.0");
  asm("         ldn  ra         ; get high byte of high offset");
  asm("         phi  r8         ; save in r8.1");
  asm("         call O_SEEK     ; attempt to seek within file");
  asm("         copy r7, ra     ; save low final offset");
  asm("         pop  r7         ; restore stack pointer");
  asm("         copy r8, rc     ; save high final offset");
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
  if (cmp32(&result, &eof) == 0) {
    errno = EIO;
  }

  return result;
}
