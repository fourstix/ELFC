#define _ELFCLIB_
#include <stdio.h>
#include <errno.h>


#pragma             extrn Cerrno
#pragma             extrn Clseek32

int fgetpos(FILE *f, pos_t *pos) {
  int   hi;
  int   lo;
  off_t offset;

  if (f == NULL || pos == NULL) {
    errno = EINVAL;
    return -1;
  }

  /* can't get position of an system IO stream */
  if (f->mode == _IOSYS) {
    errno = EBADF;
    return -1;
  }

  /* set offset to 0 */
  offset.low = 0;
  offset.high = 0;

  /* get the current file position */
  offset = lseek32(f->fd, offset, SEEK_CUR);

  /* set initial values for local variables */
  hi = offset.high;
  lo = offset.low;

  /* adjust for any character in pushback buffer from previous read*/
  if (_FREAD == f->last) {
    if (f->ch != EOF) {
      lo--;
      /* adjust double word (32-bit) value */
      /* if lo was zero before, then decrement hi byte */
      if (-1 == lo)
        hi--;
    }
  }

  pos->high = hi;
  pos->low = lo;

  return 0;
}
