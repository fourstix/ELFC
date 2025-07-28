#define _ELFCLIB_
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#pragma             extrn Cgetch
#pragma             extrn Cread
#pragma             extrn Cerrno

char *fgets(char *s, int len, FILE *f) {
	int	  k;
	char	*p;
	char  cn;

	if ((f->iom & _FREAD) == 0) return NULL;
	if (f->iom & _FERROR) return NULL;

	p = s;
	if ((f->last == _FREAD) && (f->ch != EOF)) {
		*p++ = f->ch;
		f->ch = EOF;
		len--;
	}

	f->last = _FREAD;

	if (f->mode == _IONBF || f->mode == _IOTMP) {
		while (len-- > 1) {
			if (read(f->fd, p, 1) != 1) {
				errno = EIO;
				s = NULL;
				break;
			}
			if ('\n' == *p++) 
			  break;
		}
		*p = 0;
	} else if (f->mode == _IOSYS) {
		while (len-- > 1) {
			//grw - get raw input character
			cn = getch();
			//grw - Elf/OS can terminate input with newline or carriage return
			if ('\n' == cn || '\r' == cn) {
				//grw - C always uses newline
				*p++ = '\n';
				break;
			} else if ('\003' == cn || '\0' == cn) {
				//grw - Elf/OS can also terminate input with Ctrl-C or null
				break;
			} else {
				*p++ = cn;
			} 		
		}
		*p = 0;
	} else {
		/* set error for Unknown io type*/
		f->iom &= _FERROR;
		errno = EINVAL;
		s = NULL;
	}
	return s;
}
