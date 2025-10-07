/*
 *	NMH's Simple C Compiler, 2012,2014
 *	fseek()
 */
#define _ELFCLIB_
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#pragma             extrn Cerrno
#pragma             extrn Clseek

int fseek(FILE *f, int offset, int how) {
	int hi;
  int lo;
  lo = offset;

  /* check for invalid file ptr (can't seek on system io streams) */
  if (f == NULL || f->mode == _IOSYS) {
    errno = EBADF;
		return -1;    
  }
  /* check for valid arguments */
	if (how < SEEK_SET || how > SEEK_END) {
		errno = EINVAL;
		return -1;
	}
	
	
	/* don't seek before start of file */
	if ((how == SEEK_SET) && offset < 0) {
		errno = EINVAL;
		return -1;		
	}
	
	/* don't seek past the end of the file */
	if ((how == SEEK_END) && offset > 0) {
		errno = EINVAL;
		return -1;		
	}
  
  /* adjust offset for a character in ugetc buffer */
  if (how == SEEK_CUR && _FREAD == f->last) {
    if (f->ch != EOF) lo--;
   }
  /* seeking wipes out character push-back buffer and clears EOF */
  f->ch = EOF;
	f->iom &= ~_FEOF;
  
  /* sign extend lo word offset into hi word */
  if (lo < 0) {
    hi = -1;
  } else {
    hi = 0;
  }
  
  if ((lseek(f->fd, hi, lo, how)) < 0) {
    errno = EIO;
    return -1;
  }
  return 0; 
}
