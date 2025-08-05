#define _ELFCLIB_
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#pragma             extrn Cputch
#pragma             extrn Cwrite
#pragma             extrn Cerrno

int fputc(int c, FILE *f) {
	char	b[1];
  
  if (f == NULL) 
    return EOF;
    
  if ((f->iom & _FWRITE) == 0)
    return EOF;
    
  if (f->iom & _FERROR)
    return EOF;
    
  f->last = _FWRITE;
  
  if (f->mode == _IONBF || f->mode == _IOTMP) {
    /* non-buffered file io */
    *b = c;
    if (write(f->fd, b, 1) == 1)
      return c;
    else {
      /* set error bit on io flag */
      f->iom |= _FERROR;
      errno = EIO;
      return EOF;
    }
  } else if (f->mode == _IOSYS) {   
    /* elfos system io */
    return putch(c);
  } else {
    /* set error for Unknown io type*/
    f->iom |= _FERROR;
    errno = EINVAL;
    return EOF;
  }
}
    
