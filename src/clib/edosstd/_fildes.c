#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>

#pragma             extrn Cerrno
#pragma             extrn C_fdtable   
#pragma             extrn Cmalloc    



int _fildes(int fd) {
  int fildes;
    
  /* There is no handle for an invalid fd */
  if(fd < 0 || fd >= FD_MAX) {
    errno = EBADF;
    return EOF;
  }

  fildes = _fdtable[fd]; 
  
  /* no fildes for stdin, stdout or stderr */
  if (fildes >= 0 && fildes < FD_SYS) {
    errno = EBADF;
    return EOF;
  }
  
  return fildes;
}
