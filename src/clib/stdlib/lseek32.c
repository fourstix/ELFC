#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>

#pragma             extrn Cerrno
#pragma             extrn C_fildes

int  lseek32(int fd, int hi_off, int lo_off, int how) {
  int fildes;
  int result;
  
  /* get system file descriptor */
  fildes = _fildes(fd);
  
  /* don't seek invalid fd */
  if(fildes == EOF) {
    errno = EBADF;
    return EOF;
  }
  
  asm("         gosub s_lget16  ; get the fildes variable ");
  asm("           dw -2         ; from local variable stack");           
  asm("         copy ra, rd     ; copy fd to fildes register");
  asm("         gosub s_lget16  ; get the how to seek argument ");
  asm("           dw 6          ; from argument stack");           
  asm("         copy ra, rc     ; copy how to seek value to register");
  asm("         push r7         ; save stack pointer before setting low offset");
  asm("         gosub s_lget16  ; get the low offset value");
  asm("           dw 4          ; from the argument stack");           
  asm("         copy ra, r7     ; copy to low offset register");
  asm("         gosub s_lget16  ; get the high offset value ");
  asm("           dw 2          ; from the argument stack");           
  asm("         copy ra, r8     ; copy to high offset register");
  asm("         call O_SEEK     ; attempt to seek within file");
  asm("         pop  r7         ; restore stack pointer");
  asm("         ldi  0          ; set default value for success");
  asm("         lsnf            ; DF = 0, means success");
  asm("         ldi  $Ff        ; otherwise set result for error");
  asm("         phi  ra         ; set result for 0 or -1 ");
  asm("         plo  ra         ; set result in ra ");
  asm("         gosub s_lset16  ; set the result ");
  asm("           dw -4         ; in the local variable");           
  
  /* if error, set errno */
  if (result == EOF)
    errno = EIO;
  
  return result;
}
