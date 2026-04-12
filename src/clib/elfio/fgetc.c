#define _ELFCLIB_
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#pragma             extrn Cgetch
#pragma             extrn Cread
#pragma             extrn Cerrno


int fgetc(FILE *f) {
	char	c, b[1];

  if (f == NULL)
    return EOF;

	if ((f->iom & _FREAD) == 0)
		return EOF;

	if (f->iom & _FERROR)
		return EOF;

  if (f->iom & _FEOF)
		return EOF;

	f->last = _FREAD;

	if (f->ch != EOF) {
		c = f->ch;
		f->ch = EOF;
		return c;
	}

	if (f->mode == _IONBF || f->mode == _IOTMP) {
		if (read(f->fd, b, 1) == 1)
			return *b;
		else {
      /* iF read failed we reached end of file */
      f->iom |= _FEOF;
			errno = EIO;
			return EOF;
		}
  } else if (f->mode == _IOSYS) {
			/* inline getch() code */
			/* return getch(); */
			asm("         call  O_READKEY     ; read a character from input");
			asm("         plo ra              ; save in return register");
			asm("         ldi 0               ; pad register with zero");
			asm("         phi ra              ");
			asm("         gosub s_lset16      ; set the local variable");
			asm("           dw -2             ; with the return value");
			return c;
  } else {
    /* set error for unknown io type*/
    f->iom |= _FERROR;
    errno = EINVAL;
    return EOF;
  }
}
