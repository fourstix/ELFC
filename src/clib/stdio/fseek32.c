/*
 *	NMH's Simple C Compiler, 2012,2014
 *	fseek()
 */
#define _ELFCLIB_
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#pragma             extrn Cerrno
#pragma             extrn Clseek32
#pragma             extrn Cto_int32
#pragma             extrn Ccmp32

int fseek32(FILE *f, off_t *offset, int whence) {
  int hi;
  off_t pos;
  off_t error;

  /* check for invalid file ptr (can't seek on system io streams) */
  if (f == NULL || f->mode == _IOSYS) {
    errno = EBADF;
    return -1;    
  }
  
  /* check for valid arguments */
  if (whence < SEEK_SET || whence > SEEK_END) {
    errno = EINVAL;
    return -1;
  }
	
  /* don't seek before start of file */
  if ((whence == SEEK_SET) && ((offset->high & 0x8000) != 0)) {
    errno = EINVAL;
    return -1;		
  }

  /* don't seek past the end of the file */
  if ((whence == SEEK_END) && ((offset->high != 0) || (offset->low != 0))) {
    errno = EINVAL;
    return -1;		
  }
  
  /* adjust offset for a character in ugetc buffer */
  if (whence == SEEK_CUR && _FREAD == f->last) {
    if (f->ch != EOF) offset->low--;
  }

  /* seeking wipes out character push-back buffer and clears EOF */
  f->ch = EOF;
  f->iom &= ~_FEOF;
  
  pos = lseek32(f->fd, offset, whence);

  error = to_int32(-1);
  if (cmp32(&pos, &error) == 0) {
    errno = EIO;
    return -1;
  }

  return 0; 
}
