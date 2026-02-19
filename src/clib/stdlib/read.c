#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>

#pragma             extrn Cerrno
#pragma             extrn C_fildes

int read(int fd, void *buf, size_t n) {
  int fildes;
  int n_read;
  
  /* get system file descriptor */
  fildes = _fildes(fd);
  
  /* if fildes is invalid, return with error */
  if (fildes == EOF) {
    errno = EBADF;      
    return EOF;
   }
     
  asm("         gosub s_lget16  ; get the flldes variable ");
  asm("           dw -2         ; from local variable stack");           
  asm("         copy ra, rd     ; copy fd pointer to buffer pointer");
  asm("         gosub s_lget16  ; get the buffer argument ");
  asm("           dw 2          ; get from argument stack");           
  asm("         copy ra, rf     ; copy argument pointer to buffer pointer");
  asm("         gosub s_lget16  ; get the byte count argument ");
  asm("           dw 4          ; get from argument stack");           
  asm("         copy ra, rc     ; copy argument value to counter");
  asm("         call O_READ     ; attempt to read the data");
  asm("         lbnf rd_ok      ; On success rc holds the number read");
  asm("         ldi  $ff        ; otherwise set count for error");
  asm("         phi  rc         ; set count to -1 ");
  asm("         plo  rc         ; in rc for return value ");
  asm("rd_ok:   copy rc, ra     ; set count as return value ");
  asm("         gosub s_lset16  ; set the local variable to the count ");
  asm("           dw -4         ; on the argument stack");           

  if (n_read == EOF) {
    errno = EIO;
  }  
  
  return n_read;
}
