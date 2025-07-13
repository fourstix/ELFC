#define _ELFCLIB_
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#pragma             extrn Cgetch
#pragma             extrn Cread
#pragma             extrn Cerrno

int _fread(void *p, int size, FILE *f) {
	int	total;
	int nc;
	char ch;

	if ((f->iom & _FREAD) == 0) return 0;
	if (f->iom & _FERROR) return 0;
	if (f->iom & _FEOF) return 0;

	if ((f->last = _FREAD) && (f->ch != EOF)) {
		*(char *)p++ = f->ch;
		f->ch = EOF;
		size--;
	}
	f->last = _FREAD;
	
	if (f->mode == _IONBF) {
		if ((total = read(f->fd, p, size)) != size) {
			f->iom |= _FEOF;
			errno = EIO;
		}
		return total;
  } else if (f->mode == _IOSYS) {
		//grw - ANSI spec says to read from stdin repeatedly, until size characters
		//grw - are read into the buffer. This will block IO in Elf/OS, until
		//grw - enough characters are entered.  
		for(total = 0; total < size; total++) {
			ch = getch();
			/* check for Ctrl-C (aka ETX  or break) */
			if (ch == '\003') break;
			
			*(char *)p++ = ch;
		}//for
		return total;
	} else {
		/* set error for Unknown io type*/
		f->iom &= _FERROR;
		errno = EINVAL;
		return -1;
	}
}	

int fread(void *p, int size, int count, FILE *f) {
	int	k;

	if ((k = _fread(p, size * count, f)) < 0)
		return EOF;
	return k / size;
}
