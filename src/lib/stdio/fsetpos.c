#define _ELFCLIB_
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#pragma             extrn Cerrno
#pragma             extrn Clseek

int fsetpos(FILE *f, pos_t *pos) {
	
	if (f == NULL || pos == NULL) {
		errno = EINVAL;
		return -1;
	}
	
	/* can't set position of an system IO stream */
	if (f->mode == _IOSYS) {
		errno = EBADF;
		return -1;
	}
	
	/* setting poistion wipes out character push-back buffer and clears EOF */
	f->ch = EOF;
	f->iom &= ~_FEOF;
	
	return lseek(f->fd, pos->hi, pos->lo, SEEK_SET);
}
