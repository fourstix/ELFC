#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>

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
  asm("         copy ra, rd     ; copy fd pointer to buffer pointer");
  asm("         gosub s_lget16  ; get the buffer argument ");
  asm("           dw 2          ; get from argument stack");           
  asm("         copy ra, rf     ; copy argument pointer to buffer pointer");
  asm("         gosub s_lget16  ; get the byte count argument ");
  asm("           dw 4          ; get from argument stack");           
  asm("         copy ra, rc     ; copy argument value to counter");
  asm("         call O_WRITE    ; attempt to close the file");
  asm("         lbnf rd_ok      ; On success rc holds the number read");
  asm("         ldi  $Ff        ; otherwise set count for error");
  asm("         phi  rc         ; set count to -1 ");
  asm("         plo  rc         ; set result in ra ");
  asm("rd_ok:   copy rc, ra     ; set count as return value ");
  asm("         gosub s_lset16  ; set the local variable to the count ");
  asm("           dw -4         ; on the argument stack");           

  if (n_write == EOF) {
    errno = EIO;
  }  
  
  return n_write;
}
