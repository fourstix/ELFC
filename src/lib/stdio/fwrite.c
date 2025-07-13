#define _ELFCLIB_
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#pragma             extrn Cputch
#pragma             extrn Cwrite
#pragma             extrn Cerrno

int _fwrite(void *p, int size, FILE *f) {
	int	k, len, total;
	char *s;

	if ((f->iom & _FWRITE) == 0) return 0;
	if (f->iom & _FERROR) return 0;
	f->last = _FWRITE;
	
	if (f->mode == _IONBF) {
		if ((k = write(f->fd, p, size)) != size) {
			f->iom |= _FERROR;
			errno = EIO;
		}
	} else if (f->mode == _IOSYS) {
		total = 0;
		/* for stdout or stderr, treat as character string */
		s = p;
		/* output up to size characters from string */
		while(*s && (total < size)) {
			putch(*s);
			s++;
			total++;
		}//while
		k = total;
	}	else {
		/* set error for Unknown io type*/
		f->iom &= _FERROR;
		errno = EINVAL;
		k = -1;
		}
  return k;
}


int fwrite(void *p, int size, int count, FILE *f) {
	int	k;

	if ((k = _fwrite(p, size * count, f)) < 0)
		return -1;
	return k / size;
}
