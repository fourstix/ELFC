#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>

#pragma             extrn Cerrno
#pragma             extrn C_fdcnt
#pragma             extrn Cfree
#pragma             extrn C_fdvalid


extern int _fdcnt;    


int	close(int fd) {
  int result;
  
  /* don't close an invalid fd */
  if(!_fdvalid(fd)) {
    errno = EBADF;
    return EOF;
  }
  
  asm("         call lget16     ; get the fd argument ");
  asm("           dw 0          ; get from argument stack");           
  asm("         copy ra, rd     ; copy fd pointer to buffer pointer");
  asm("         call O_CLOSE    ; attempt to close the file");
  asm("         ldi  0          ; set default value for success");
  asm("         lsnf            ; DF = 0, means success");
  asm("         ldi  $Ff        ; otherwise set result for error");
  asm("         phi  ra         ; set result for 0 or -1 ");
  asm("         plo  ra         ; set result in ra ");
  asm("         call lset16     ; set the fd argument ");
  asm("           dw -2         ; in the local variable on the stack");           

  /* if close failed, set errno */
  if (result == EOF) {
    errno = EIO;
  } 
  
  /* decrement count */
  if (_fdcnt > 0) {  
    _fdcnt--;    
  } 
  /* release the file descriptor */
  free((void *)fd);
  
  return result;
}
