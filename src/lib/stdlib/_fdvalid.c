#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>

/* define only extern procedures required */
#pragma           extrn Cerrno
#pragma           extrn C_fdcnt


extern int _fdcnt; 

int _fdvalid(int fd) {
  int size = 0;
  
  /* if no fd's in use, fd is invalid */
  if (_fdcnt == 0) {  
    errno = EBADF;
    return 0;    
  } 

  /* fd is invalid handle, give up */
  if (fd == EOF) {
    errno = EBADF;
    return 0;
  }
  
  /* get the memory block size directly from the heap */
  asm("         call lget16     ; get the fd value to test");
  asm("           dw 0          ; from argument stack");             
  asm("         copy ra, rf     ; put pointer into rf"); 
  asm("         dec rf          ; walk back 3 bytes before memory block");
  asm("         dec rf          ; to get the memory block size");
  asm("         dec rf          ; and the block flags");
  asm("         lda rf          ; get the block flag byte");
  asm("         ani 2           ; test for block allocated bit");
  asm("         lbz fdtst       ; don't bother with size, if block not in use");
  asm("         lda rf          ; get the size hi byte (MSB)");
  asm("         phi ra          ; set high byte to store ");
  asm("         lda rf          ; get the size lo byte (LSB)");
  asm("         plo ra          ; set lo byte to store ");
  asm("         call lset16    ; set the old size value");
  asm("           dw -2         ; in the local argument stack");  
  asm("fdtst:                   ; exit point" );  
  
  /* make sure size matches fd*/
  if (size != FD_SIZE) {
    errno = EBADF;
    return 0;    
  }
  
  /* if we made it to here, the fd is valid */
  return 1;
}
