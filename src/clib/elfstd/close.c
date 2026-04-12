#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>

#pragma             extrn Cerrno
#pragma             extrn C_fdtable
#pragma             extrn C_fildes
#pragma             extrn Cfree

int	close(int fd) {
  int fildes;
  int result;

  /* get system file descriptor */
  fildes = _fildes(fd);
  
  if (fildes == EOF) {
    return EOF;
  }
  
  asm("         gosub s_lget16  ; get the fildes variable ");
  asm("           dw -2         ; get from local stack");           
  asm("         copy ra, rd     ; copy fd pointer to buffer pointer");
  asm("         call O_CLOSE    ; attempt to close the file");
  asm("         ldi  0          ; set default value for success");
  asm("         lsnf            ; DF = 0, means success");
  asm("         ldi  $Ff        ; otherwise set result for error");
  asm("         phi  ra         ; set result for 0 or -1 ");
  asm("         plo  ra         ; set result in ra ");
  asm("         gosub s_lset16  ; set the result value ");
  asm("           dw -4         ; in the local variable on the stack");           

  /* if close failed, set errno */
  if (result == EOF) {
    errno = EIO;
  } 
  
  /* update table to free handle */
  _fdtable[fd] = EOF;
   
  /* release the file descriptor */
  free((void *)fildes);
  
  return result;
}
