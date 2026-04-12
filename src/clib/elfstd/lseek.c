#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>

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
  asm("         copy ra, rd     ; copy fd to fildes register");
  asm("         gosub s_lget16  ; get the how to seek argument ");
  asm("           dw 4          ; from argument stack");           
  asm("         copy ra, rc     ; copy how to seek value to register");
  asm("         push r7         ; save stack pointer before setting low offset");
  asm("         gosub s_lget16  ; get the low offset value");
  asm("           dw 2          ; from the argument stack");           
  asm("         copy ra, r7     ; copy to low offset register");
  asm("         ldi  0          ; sign extend low offset register");
  asm("         plo  r8         ; into high offset register");
  asm("         phi  r8         ; initialize r8 to 0");
  asm("         ghi  r7         ; get high byte of low offset");
  asm("         shl             ; move sign bit to df");
  asm("         lsnf            ; skip if sign bit is zero (positive)");
  asm("         dec  r8         ; r8 = ffff if sign bit is one (negative)");
  asm("         nop             ; needed because of long skip");
  asm("         call O_SEEK     ; attempt to seek within file");
  asm("         copy r7, ra     ; save low offset return value");
  asm("         pop  r7         ; restore stack pointer");
  asm("         ldi  $ff        ; load -1");
  asm("         lsnf            ; DF = 0, means success");
  asm("         phi  ra         ; set result to -1");
  asm("         plo  ra         ; on error");
  asm("         gosub s_lset16  ; set the result ");
  asm("           dw -4         ; in the local variable");           
 
  /* if error, set errno */
  if (result == -1)
    errno = EIO;
  
  return result;
}
