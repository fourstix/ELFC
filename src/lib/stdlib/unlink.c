#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>

#pragma             extrn Cerrno

int	unlink(char* path) {
  int result;
  
  /* don't delete invalid path */
  if(path == NULL) {
    errno = EINVAL;
    return EOF;
  }
  
  asm("         call lget16     ; get the path argument ");
  asm("           dw 0          ; get from argument stack");           
  asm("         copy ra, rf     ; copy path string to buffer pointer");
  
  asm("         push rb         ; save stack frame base pointer on the stack"); 
  asm("         call O_DELETE   ; attempt to delete the file");
  asm("         pop rb          ; restore stack frame base pointer from the stack"); 
  
  asm("         ldi  0          ; set default value for success");
  asm("         lsnf            ; DF = 0, means success");
  asm("         ldi  $Ff        ; otherwise set result for error");
  asm("         phi  ra         ; set result for 0 or -1 ");
  asm("         plo  ra         ; set result in ra ");
  asm("         call lset16     ; set the fd argument ");
  asm("           dw -2         ; in the local variable on the stack");           
  
  /* if error, set errno */
  if (result == EOF)
    errno = EIO;

  return result;
}
