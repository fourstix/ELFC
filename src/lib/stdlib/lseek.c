#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>

#pragma             extrn Cerrno

int  lseek(int fd, int hi_off, int lo_off, int how) {
  int result;
  
  /* don't seek invalid fd */
  if(fd == EOF) {
    errno = EBADF;
    return EOF;
  }
  
  asm("         call lget16     ; get the fd argument ");
  asm("           dw 0          ; from argument stack");           
  asm("         copy ra, rd     ; copy fd to fildes register");
  asm("         call lget16     ; get the how to seek argument ");
  asm("           dw 6          ; from argument stack");           
  asm("         copy ra, rc     ; copy how to seek to register");
  asm("         call lget16     ; get the high offset value ");
  asm("           dw 2          ; from the argument stack");           
  asm("         copy ra, r8     ; copy to high offset register");
  asm("         push r7         ; save stack pointer");
  asm("         call lget16     ; get the low offset value ");
  asm("           dw 4          ; from the argument stack");           
  asm("         copy ra, r7     ; copy to low position register");
  asm("         call O_SEEK     ; attempt to seek within file");
  asm("         pop  r7         ; restore stack pointer");
  asm("         ldi  0          ; set default value for success");
  asm("         lsnf            ; DF = 0, means success");
  asm("         ldi  $Ff        ; otherwise set result for error");
  asm("         phi  ra         ; set result for 0 or -1 ");
  asm("         plo  ra         ; set result in ra ");
  asm("         call lset16     ; set the result ");
  asm("           dw -2         ; in the local variable");           
  
  /* if error, set errno */
  if (result == EOF)
    errno = EIO;
  
  return result;
}
