#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>

#pragma             extrn Cerrno
#pragma             extrn C_fdinit

int	open(char *path, int flags) {
  int fd;
  int  result;
  
  fd = _fdinit();
  
  if (fd == EOF) 
    return EOF;
  
  asm("         call lget16     ; get the fd argument ");
  asm("           dw -2         ; get from the local variable");           
  asm("         copy ra, rd     ; copy fd pointer to buffer pointer");
  asm("         call lget16     ; get the fd argument ");
  asm("           dw 0          ; get from argument stack");
  asm("         copy ra, rf     ; copy path argument as name buffer");
  asm("         call lget16     ; get the flags argument ");
  asm("           dw 2          ; get from argument stack");           
  asm("         push r7         ; save ESP before using r7 for flags");
  asm("         copy ra, r7     ; set flags for open");
  asm("         call O_OPEN     ; attempt to close the file");
  asm("         pop r7          ; restore ESP r7");
  asm("         ldi  0          ; set default value for success");
  asm("         lsnf            ; DF = 0, means success");
  asm("         ldi  $Ff        ; otherwise set result for error");
  asm("         phi  ra         ; set result to 0 or -1 ");
  asm("         plo  ra         ; set result in ra ");
  asm("         call lset16     ; set result argument ");
  asm("           dw -4         ; get from argument stack");           

  if (result == EOF) {
    errno = EIO;  
    return EOF;
  }
  return fd;
}
