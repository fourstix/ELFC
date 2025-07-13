#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>

#pragma             extrn Cerrno

int read(int fd, void *buf, int n) {
  int n_read;
  
  /* if fd is invalid, return with error */
  if (fd == EOF) {
    errno = EBADF;      
    return EOF;
   }
     
  asm("         call lget16     ; get the fd argument ");
  asm("           dw 0          ; get from argument stack");           
  asm("         copy ra, rd     ; copy fd pointer to buffer pointer");
  asm("         call lget16     ; get the buffer argument ");
  asm("           dw 2          ; get from argument stack");           
  asm("         copy ra, rf     ; copy argument pointer to buffer pointer");
  asm("         call lget16     ; get the byte count argument ");
  asm("           dw 4          ; get from argument stack");           
  asm("         copy ra, rc     ; copy argument value to counter");
  asm("         call o_read     ; attempt to close the file");
  asm("         lbnf rd_ok      ; On success rc holds the number read");
  asm("         ldi  $ff        ; otherwise set count for error");
  asm("         phi  rc         ; set count to -1 ");
  asm("         plo  rc         ; in rc for return value ");
  asm("rd_ok:   copy rc, ra     ; set count as return value ");
  asm("         call lset16     ; set the local variable to the count ");
  asm("           dw -2         ; on the argument stack");           

  if (n_read == EOF) {
    errno = EIO;
  }  
  
  return n_read;
}
